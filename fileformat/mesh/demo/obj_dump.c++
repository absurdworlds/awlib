/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/fileformat/obj/loader.h>
#include <aw/io/input_file_stream.h>
#include <aw/types/array_view.h>

#include <bit>
#include <cstdint>
#include <iomanip>
#include <iostream>

namespace aw::obj {
namespace {
std::uint64_t fingerprint( mesh const& m )
{
	std::uint64_t hash = 14695981039346656037ull;

	auto mix = [&hash] (std::uint64_t value) {
		hash = (hash ^ value) * 1099511628211ull;
	};
	auto mix_double = [&mix] (double value) {
		mix( std::bit_cast<std::uint64_t>(value) );
	};
	auto mix_string = [&mix] (std::string_view str) {
		for (char c : str)
			mix( (unsigned char)c );
	};

	for (auto const& v : m.verts)    for (double p : v.points) mix_double(p);
	for (auto const& v : m.normals)  for (double p : v.points) mix_double(p);
	for (auto const& v : m.texverts) for (double p : v.points) mix_double(p);

	for (auto const& face : m.faces) {
		for (auto const& v : face.verts) {
			mix( v.index );
			mix( v.texuv );
			mix( v.normal );
		}
		mix( face.smooth );
	}

	for (auto const& sm : m.meshes) {
		mix_string( sm.group );
		mix_string( sm.material );
		mix( sm.begin );
		mix( sm.end );
	}

	return hash;
}
} // namespace
} // namespace aw::obj

int main(int, char**argv)
{
	using namespace aw;
	io::input_file_stream file{ argv[1] ? argv[1] : "butruck.obj" };

	auto mesh = obj::mesh::parse( file );

	constexpr bool summary_only = true;
	if (summary_only) {
		std::cout << mesh.verts.size() << '\n';
		std::cout << mesh.normals.size() << '\n';
		std::cout << mesh.texverts.size() << '\n';
		std::cout << std::hex << std::setw(16) << std::setfill('0')
		          << obj::fingerprint( mesh ) << '\n';
		return 0;
	}

	if (!mesh.matlibs.empty()) {
		std::cout << "mtllib";
		for (auto& m : mesh.matlibs)
			std::cout << ' ' << m;
		std::cout << '\n';
	}
	for (auto& v : mesh.verts)
		std::cout << "v " << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
	for (auto& v : mesh.normals)
		std::cout << "vn " << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
	for (auto& v : mesh.texverts)
		std::cout << "vt " << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';

	auto face_list = array_view<obj::face>( mesh.faces );

	string_view cur_group;
	for (auto& sm : mesh.meshes) {
		if (!sm.group.empty() && sm.group != cur_group) {
			cur_group = sm.group;
			std::cout << "g " << sm.group << '\n';
		}
		if (!sm.material.empty())
			std::cout << "usemtl " << sm.material << '\n';
		unsigned sg = -1;
		auto faces = face_list.slice( sm.begin, sm.end );
		for ( auto& f : faces ) {
			if (f.smooth != sg) {
				sg = f.smooth;
				std::cout << "s " << (sg ? std::to_string(sg) : "off") << '\n';
			}
			std::cout << "f";
			for (auto v : f.verts) {
				obj::make_one_based( v );
				std::cout << ' ' << v.index << '/' << v.normal << '/' << v.texuv;
			}
			std::cout << "\n";
		}
	}
}
