/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

/*
 * awgl reaches GL through function pointers the loader fills in at runtime,
 * so a test can fill them in itself and check what a driver cannot report:
 * which calls were made, in what order, and how often. Whether a driver would
 * have accepted any of it is what shader.c++ is for.
 *
 * TODO: create a fakegl library
 */
#include <aw/gl/api/gl_33.h>
#include <aw/gl/api/gl_46.h>
#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/log.h>

#include <aw/test/test.h>
#include <string>
#include <vector>

TestFile( "graphics::gl3 (fake GL)" );

namespace aw::gl3 {
namespace {
std::vector<std::string> calls;

GLuint next_handle       = 1;
bool   compile_succeeds  = true;

void record(std::string call) { calls.push_back(std::move(call)); }

GLuint fake_create_shader(GLenum type)
{
	record("create_shader(" + std::to_string(type) + ")");
	return next_handle++;
}

void fake_delete_shader(GLuint shader)
{
	record("delete_shader(" + std::to_string(shader) + ")");
}

void fake_shader_source(GLuint shader, GLsizei, GLchar const* const*, GLint const*)
{
	record("shader_source(" + std::to_string(shader) + ")");
}

void fake_compile_shader(GLuint shader)
{
	record("compile_shader(" + std::to_string(shader) + ")");
}

void fake_get_shader_iv(GLuint, GLenum pname, GLint* params)
{
	switch (pname) {
	case GL_COMPILE_STATUS:   *params = compile_succeeds ? GL_TRUE : GL_FALSE; break;
	case GL_INFO_LOG_LENGTH:  *params = 1; break;
	case GL_SHADER_TYPE:      *params = GL_VERTEX_SHADER; break;
	default:                  *params = 0; break;
	}
}

void fake_get_shader_info_log(GLuint, GLsizei, GLsizei*, GLchar* log)
{
	log[0] = '\0';
}

void install_fake_gl()
{
	::gl::create_shader        = fake_create_shader;
	::gl::delete_shader        = fake_delete_shader;
	::gl::shader_source        = fake_shader_source;
	::gl::compile_shader       = fake_compile_shader;
	::gl::get_shader_iv        = fake_get_shader_iv;
	::gl::get_shader_info_log  = fake_get_shader_info_log;

	calls.clear();
	next_handle      = 1;
	compile_succeeds = true;
}

size_t count_calls(std::string_view name)
{
	size_t n = 0;
	for (auto const& call : calls)
		if (call.compare(0, name.size(), name) == 0)
			++n;
	return n;
}

size_t count_exact(std::string_view call)
{
	size_t n = 0;
	for (auto const& recorded : calls)
		if (recorded == call)
			++n;
	return n;
}

/*
 * shader::cleanup() deletes unconditionally, so a moved-from shader still
 * issues delete_shader(0), which is a no-op (required by spec).
 * Counting those would say nothing about ownership, so the tests below
 * use named handles.
 */
std::string deleted(GLuint handle)
{
	return "delete_shader(" + std::to_string(handle) + ")";
}

struct capture_log : aw::log {
	struct entry {
		level       lvl;
		std::string src;
		std::string msg;
	};

	void message(level lvl, string_view src, string_view msg) override
	{
		entries.push_back({lvl, std::string(src), std::string(msg)});
	}

	std::vector<entry> entries;
};
} // namespace

Test(shader_issues_expected_gl_calls) {
	install_fake_gl();

	{
		shader shd{gl::shader_type::vertex, "irrelevant"};
		TestAssert( shd.is_compiled() );
	} // destructor runs here

	Checks {
		TestEqual( calls.size(), 4u );
		TestEqual( calls[0], std::string("create_shader(")
			+ std::to_string(GL_VERTEX_SHADER) + ")" );
		TestEqual( calls[1], std::string("shader_source(1)") );
		TestEqual( calls[2], std::string("compile_shader(1)") );
		TestEqual( calls[3], std::string("delete_shader(1)") );
	}
}

Test(shader_type_maps_to_gl_enum) {
	install_fake_gl();

	shader vertex{gl::shader_type::vertex};
	shader fragment{gl::shader_type::fragment};

	Checks {
		TestEqual( calls[0], std::string("create_shader(")
			+ std::to_string(GL_VERTEX_SHADER) + ")" );
		TestEqual( calls[1], std::string("create_shader(")
			+ std::to_string(GL_FRAGMENT_SHADER) + ")" );
	}
}

Test(failed_compile_is_reported) {
	install_fake_gl();
	compile_succeeds = false;

	capture_log captured;
	journal.set_logger(&captured);

	shader shd{gl::shader_type::vertex, "irrelevant"};

	journal.set_logger(nullptr);

	Checks {
		TestAssert( !shd.is_compiled() );

		// the failure is logged
		TestEqual( captured.entries.size(), size_t(1) );

		if (captured.entries.size() == 1) {
			TestEqual( captured.entries[0].src, std::string("shader") );
			TestAssert( captured.entries[0].lvl == log::error );
		}
	}
}

Test(nothing_is_logged_without_a_logger) {
	install_fake_gl();
	compile_succeeds = false;

	capture_log captured;

	shader shd{gl::shader_type::vertex, "irrelevant"};

	Checks {
		TestEqual( captured.entries.size(), size_t(0) );
	}
}

// A real driver would report the second delete as a vague error, if at all.
Test(move_transfers_ownership_of_handle) {
	install_fake_gl();

	{
		shader original{gl::shader_type::vertex, "irrelevant"};
		shader moved{std::move(original)};
		TestAssert( moved.is_compiled() );
	} // both destructors run here

	Checks {
		TestEqual( count_calls("create_shader"), 1u );
		TestEqual( count_exact(deleted(1)), 1u );
	}
}

Test(move_assignment_releases_old_handle) {
	install_fake_gl();

	{
		shader first{gl::shader_type::vertex, "irrelevant"};   // handle 1
		shader second{gl::shader_type::fragment, "irrelevant"}; // handle 2

		second = std::move(first);

		Checks {
			TestEqual( count_calls("create_shader"), 2u );
			TestEqual( count_exact(deleted(2)), 1u );
			TestEqual( count_exact(deleted(1)), 0u );
		}
	} // both destructors run here

	Checks {
		TestEqual( count_exact(deleted(1)), 1u );
		TestEqual( count_exact(deleted(2)), 1u );
	}
}
} // namespace aw::gl3
