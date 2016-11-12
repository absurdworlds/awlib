/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "shared.h"

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

struct parser : private obj::mesh {
	parser()
	{
		new_submesh();
	}

	mesh& result()
	{
		return *this;
	}

	void parse(io::input_stream& file)
	{
		std::string tmp;
		while (read_until( file, '\n', tmp )) {
			parse_line( tmp );
		}
	}

private:
	unsigned sg = 0;
	submesh* cur_submesh;

	string_view cur_group()
	{
		return cur_submesh->group;
	}

	string_view cur_mtl()
	{
		return cur_submesh->material;
	}

	void new_submesh( )
	{
		meshes.emplace_back();
		cur_submesh = &meshes.back();
	}

	submesh* find_submesh( string_view mtl, string_view group );
	void select_submesh( string_view mtl, string_view group );
	void select_group( string_view group );
	void select_material( string_view mtl );


	void add_vert(string_view s);
	void add_face(string_view s);
	void set_group( string_view line );

	void smoothing_group( string_view line );

	void complex_command( string_view cmd, string_view line );
	void parse_line( string_view line );
};

void parser::parse_line( string_view line )
{
	if (line.find_first_not_of( ws ) == line.npos)
		return;

	switch (line[0]) {
	case '#': return;
	case 'f': return add_face( line.substr(1) );
	case 'v': return add_vert( line.substr(1) );
	case 'g': return set_group( line.substr(1) );
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
	case ' ': verts.push_back(vert);
	case 'n': normals.push_back(vert);
	case 't': texverts.push_back(vert);
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

	auto& vec = cur_submesh->faces;
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

submesh* parser::find_submesh( string_view mtl, string_view group )
{
	auto pred  = [=] (submesh& sm) {
		return sm.group == group && sm.material == mtl;
	};
	auto it = std::find_if( begin(meshes), end(meshes), pred );
	if (it == end(meshes))
		return nullptr;
	return &(*it);
}

void parser::select_submesh( string_view mtl, string_view group )
{
	if (auto* sm = find_submesh( mtl, group )) {
		cur_submesh = sm;
	} else {
		new_submesh();
		cur_submesh->material = (std::string)mtl;
		cur_submesh->group    = (std::string)group;
	}
}

void parser::select_group( string_view group )
{
	if (group == cur_group())
		select_submesh( cur_mtl(), group );
}

void parser::select_material( string_view mtl )
{
	if (mtl != cur_mtl())
		select_submesh( mtl, cur_group() );
}

void parser::set_group( string_view line )
{
	// TODO: multiple groups
	if (line.size() > 0) line.remove_prefix( 1 );
	string_view name = string::rtrim(line, ws);
	select_group( name );
}

void parser::complex_command( string_view cmd, string_view line )
{
	if (cmd == "mtllib") {
		auto argv = string::split_by(line, " \v\r\t");
		if (argv.empty()) return;
		for (auto str : argv)
			matlibs.push_back( (std::string)str );
	}

	if (cmd == "usemtl") {
		select_material( line );
	}

	if (cmd == "csh");
	// TODO: warning: disabled for safety
}
} // namespace


mesh mesh::parse( io::input_stream& file )
{
	parser obj;
	obj.parse( file );
	return obj.result();;
}
} // namespace obj
} // namespace aw

#ifdef AW_MANUAL_TEST
#include <aw/io/input_file_stream.h>
#include <iostream>

int main(int, char**argv)
{
	using namespace aw;
	io::input_file_stream file{ argv[1] ? argv[1] : "butruck.obj" };

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

	string_view cur_group;
	for (auto& sm : mesh.meshes) {
		if (!sm.group.empty() && sm.group != cur_group) {
			cur_group = sm.group;
			std::cout << "g " << sm.group << '\n';
		}
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
				obj::make_one_based( v );
				std::cout << ' ' << v.index << '/' << v.normal << '/' << v.texuv;
			}
			std::cout << "\n";
		}
	}
}
#endif
