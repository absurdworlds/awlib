/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/fileformat/obj/loader.h>

#include <aw/io/input_stream_utils.h>

#include "shared.h"

#include <cstdlib>
#include <cassert>

namespace aw {
namespace obj {
namespace {
void make_zero_based( face_vert& v )
{
	--v.index;
	--v.normal;
	--v.texuv;
}

void make_one_based( face_vert& v )
{
	++v.index;
	++v.normal;
	++v.texuv;
}

struct parser {
	obj::mesh mesh;
	unsigned sg = 0;

	submesh& get_cur_mesh()
	{
		if (mesh.meshes.empty())
			mesh.meshes.emplace_back();
		return mesh.meshes.back();
	}

	void new_submesh( string_view line )
	{
		if (line.size() > 0) line.remove_prefix( 1 );
		mesh.meshes.push_back({ (std::string)string::rtrim(line, ws) });
	}

	void add_vert(string_view s);
	void add_face(string_view s);

	void smoothing_group( string_view line );

	void complex_command( string_view cmd, string_view line );
	void parse_line( string_view line );

	void parse(io::input_stream& file)
	{
		std::string tmp;
		while (read_until( file, '\n', tmp )) {
			parse_line( tmp );
		}
	}
};

void parser::parse_line( string_view line )
{
	if (line.find_first_not_of( ws ) == line.npos)
		return;

	switch (line[0]) {
	case '#': return;
	case 'f': add_face( line.substr(1) ); return;
	case 'v': add_vert( line.substr(1) ); return;
	case 'g': new_submesh( line.substr(1) ); return;
	case 's': smoothing_group( line.substr(1) ); return;
	};

	auto pos = line.find_first_of(ws);

	string_view cmd  = line.substr(0, pos);
	string_view args;
	if ( pos < line.size() ) {
		args = string::rtrim(line, ws);
		args.remove_prefix( pos+1 );
	}

	complex_command( cmd, args );
}

void parser::add_vert(string_view line)
{
	if (line.empty()) return;
	char type = line[0];
	auto p = string::split_off( line.substr(1), ws );

	obj::vert vert;
	if (!parse3(p.second, vert[0], vert[1], vert[3]))
		return;

	switch (type) {
	case ' ': mesh.verts.push_back(vert);
	case 'n': mesh.normals.push_back(vert);
	case 't': mesh.texverts.push_back(vert);
	};
}

void parser::add_face(string_view s)
{
	std::vector< obj::face > faces;
	std::vector< obj::face_vert > verts;

	auto substrs = string::split_by(s, " \v\r\t");
	for (auto s : substrs) {
		auto vert = string::split(s, "/");

		obj::face_vert v;
		if (!parse3(s, v.index, v.normal, v.texuv, "/"))
			continue;

		make_zero_based( v );
		verts.push_back( v );
	}

	if (verts.size() > 4);
		// TODO: https://www.geometrictools.com/Documentation/TriangulationByEarClipping.pdf
	if (verts.size() == 3) {
		faces.push_back({verts[0], verts[1], verts[2], sg});
	} else if (verts.size() == 4) {
		faces.push_back({verts[0], verts[1], verts[2], sg});
		faces.push_back({verts[3], verts[2], verts[1], sg}); // winding
	}

	auto& vec = get_cur_mesh().faces;
	vec.insert( vec.end(), faces.begin(), faces.end() );
}

void parser::smoothing_group( string_view line )
{
	if (line.size() < 2) return;
	line.remove_prefix( 1 );

	if (line == "off") {
		sg = 0;
	} else {
		std::string s = (std::string)string::trim( line, ws );
		sg = std::strtoul(s.data(), nullptr, 10);
	}
}

void parser::complex_command( string_view cmd, string_view line )
{
	if (cmd == "mtllib") {
		auto argv = string::split_by(line, " \v\r\t");
		if (argv.empty()) return;
		for (auto str : argv)
			mesh.matlibs.push_back( (std::string)str );
	}

	if (cmd == "usemtl")
		get_cur_mesh().material = (std::string)line;

	if (cmd == "csh");
	// TODO: warning: disabled for safety
}
} // namespace


mesh mesh::parse( io::input_stream& file )
{
	parser model;
	model.parse( file );
	return model.mesh;
}
} // namespace obj
} // namespace aw

#ifdef AW_MANUAL_TEST
#include <aw/io/input_file_stream.h>
#include <iostream>

int main()
{
	using namespace aw;
	io::input_file_stream file{ "butruck.obj" };

	auto mesh = obj::mesh::parse( file );

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
	for (auto& sm : mesh.meshes) {
		if (!sm.name.empty())
			std::cout << "g " << sm.name << '\n';
		if (!sm.material.empty())
			std::cout << "usemtl " << sm.material << '\n';
		unsigned sg = -1;
		for (auto& f : sm.faces) {
			if (f.smooth != sg) {
				sg = f.smooth;
				std::cout << "s " << (sg ? std::to_string(sg) : "off") << '\n';
			}
			std::cout << "f";
			for (auto v : f.verts) {
				make_one_based( v );
				std::cout << ' ' << v.index << '/' << v.normal << '/' << v.texuv;
			}
			std::cout << "\n";
		}
	}
}
#endif
