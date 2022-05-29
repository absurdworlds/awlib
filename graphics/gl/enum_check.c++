#include <aw/graphics/gl/awgl/api.h>
namespace aw {
static_assert(GLenum(gl::shader_type::fragment) == GL_FRAGMENT_SHADER);
static_assert(GLenum(gl::shader_type::vertex)   == GL_VERTEX_SHADER);
static_assert(GLenum(gl::shader_type::geometry) == GL_GEOMETRY_SHADER);

static_assert(GLenum(gl::shader_param::type)            == GL_SHADER_TYPE);
static_assert(GLenum(gl::shader_param::compile_status)  == GL_COMPILE_STATUS);
static_assert(GLenum(gl::shader_param::delete_status)   == GL_DELETE_STATUS);
static_assert(GLenum(gl::shader_param::info_log_length) == GL_INFO_LOG_LENGTH);
static_assert(GLenum(gl::shader_param::source_length)   == GL_SHADER_SOURCE_LENGTH);

static_assert(GLenum(gl::program_param::link_status) == GL_LINK_STATUS);
static_assert(GLenum(gl::program_param::info_log_length) == GL_INFO_LOG_LENGTH);
} // namespace aw
