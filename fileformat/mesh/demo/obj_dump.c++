/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

/*
 * Loads an obj file and says what came out of it.
 *
 *     awmesh-demo model.obj          how many of each thing, and a fingerprint
 *     awmesh-demo model.obj --obj    the mesh written back out as obj
 *
 * The obj it writes is exact, so `--obj` piped back in reproduces the
 * fingerprint - which is what says the writer and the loader agree.
 *
 * The fingerprint covers every value the loader produced, so two builds that
 * print the same one parsed the file identically. Unit tests only reach the
 * shapes someone thought to write down; run this over a real model after
 * touching the parser and the number either moves or it does not.
 */
#include <aw/fileformat/obj/loader.h>
#include <aw/io/input_file_stream.h>
#include <aw/types/array_view.h>

#include <bit>
#include <cstdint>
#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>

namespace aw::obj {
namespace {
//! FNV-1a, so one changed value moves the whole number
struct fingerprint {
	std::uint64_t hash = 14695981039346656037ull;

	template<typename T>
		requires std::is_integral_v<T>
	void operator()(T value)
	{
		hash = (hash ^ std::uint64_t(value)) * 1099511628211ull;
	}

	void operator()(double value)
	{
		(*this)( std::bit_cast<std::uint64_t>(value) );
	}

	void operator()(std::string_view str)
	{
		for (char c : str)
			(*this)( (unsigned char)c );
	}
};

fingerprint fingerprint_of(mesh const& m)
{
	fingerprint fp;

	for (auto const& v : m.verts)    for (double p : v.points) fp(p);
	for (auto const& v : m.normals)  for (double p : v.points) fp(p);
	for (auto const& v : m.texverts) for (double p : v.points) fp(p);

	for (auto const& face : m.faces) {
		for (auto const& v : face.verts) {
			fp( v.index );
			fp( v.texuv );
			fp( v.normal );
		}
		fp( face.smooth );
	}

	for (auto const& sm : m.meshes) {
		fp( std::string_view{sm.group} );
		fp( std::string_view{sm.material} );
		fp( sm.begin );
		fp( sm.end );
	}

	return fp;
}

void print_summary(mesh const& m)
{
	std::cout
		<< "verts     " << m.verts.size()    << '\n'
		<< "normals   " << m.normals.size()  << '\n'
		<< "texverts  " << m.texverts.size() << '\n'
		<< "faces     " << m.faces.size()    << '\n'
		<< "submeshes " << m.meshes.size()   << '\n'
		<< "fingerprint " << std::hex << std::setw(16) << std::setfill('0')
		<< fingerprint_of(m).hash << '\n';
}

//! obj counts from one, and leaves out what a vertex does not have
std::string reference(face_vert v)
{
	// zero afterwards means the file never supplied that index
	make_one_based( v );

	auto field = [] (unsigned i) {
		return i == 0 ? std::string{} : std::to_string(i);
	};

	auto str = field( v.index );
	if (v.texuv == 0 && v.normal == 0)
		return str;

	str += '/' + field( v.texuv );
	if (v.normal != 0)
		str += '/' + field( v.normal );

	return str;
}

void write_obj(mesh const& m)
{
	for (auto const& lib : m.matlibs)
		std::cout << "mtllib " << lib << '\n';

	for (auto const& v : m.verts)
		std::cout << std::format("v {} {} {}\n", v.points[0], v.points[1], v.points[2]);
	for (auto const& v : m.texverts)
		// obj allows a third texture coordinate, and models in the wild use it
		std::cout << std::format("vt {} {} {}\n", v.points[0], v.points[1], v.points[2]);
	for (auto const& v : m.normals)
		std::cout << std::format("vn {} {} {}\n", v.points[0], v.points[1], v.points[2]);

	auto const faces = array_view<face const>( m.faces );

	std::string_view group;
	for (auto const& sm : m.meshes) {
		if (!sm.group.empty() && sm.group != group) {
			group = sm.group;
			std::cout << "g " << group << '\n';
		}
		if (!sm.material.empty())
			std::cout << "usemtl " << sm.material << '\n';

		unsigned smoothing = -1;
		for (auto const& f : faces.slice( sm.begin, sm.end )) {
			if (f.smooth != smoothing) {
				smoothing = f.smooth;
				std::cout << "s " << (smoothing ? std::to_string(smoothing) : "off") << '\n';
			}

			std::cout << 'f';
			for (auto const& v : f.verts)
				std::cout << ' ' << reference(v);
			std::cout << '\n';
		}
	}
}
} // namespace
} // namespace aw::obj

int main(int argc, char** argv)
{
	using namespace aw;

	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <file.obj> [--obj]\n";
		return 2;
	}

	io::input_file_stream file{ argv[1] };
	auto const mesh = obj::mesh::parse( file );

	bool const as_obj = argc > 2 && std::string_view{argv[2]} == "--obj";
	if (as_obj)
		obj::write_obj( mesh );
	else
		obj::print_summary( mesh );
}
