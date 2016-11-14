/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_obj_loader_h
#define aw_fileformat_obj_loader_h
#include <aw/io/input_stream.h>
#include <string>
#include <vector>
namespace aw {
namespace obj {

struct vert {
	double points[3];
	double& operator[](unsigned index)
	{
		return points[index];
	}
};

struct face_vert {
	unsigned index;
	unsigned normal  = 0;
	unsigned texuv   = 0;
};

struct face {
	face_vert verts[3];
	unsigned smooth  = 0;
};

struct submesh {
	std::string group;
	std::string material;
	size_t begin = 0;
	size_t end   = 0;
};

struct mesh {
	/*!
	 * Parse a mesh in .obj format.
	 *
	 * Currently does not support full spec.
	 */
	static mesh parse( io::input_stream& is );
	std::vector<std::string> matlibs;
	std::vector<vert> verts;
	std::vector<vert> normals;
	std::vector<vert> texverts;
	std::vector<face> faces;
	std::vector<submesh> meshes{ {"default"} };
};


struct material {
	std::string name;

	double ambient[3] {};  // Ka
	double diffuse[3] {};  // Kd
	double specular[3] {}; // Ks
	double specular_exponent = 0; // Ns
	double optical_density   = 0; // Ni
	double dissolve = 1; // d, 1 - Tr
	double illumination = 0;
	enum {
		regular,
		halo,  // d -halo
	} dissolve_mode;

	std::string ambient_map;  // map_Ka
	std::string diffuse_map;  // map_Kd
	std::string specular_map; // map_Ks
	std::string normal_map;   // bump
};

struct mtllib {
	static mtllib parse( io::input_stream& is );
	std::vector<material> mtls;
};

} // namespace obj
} // namespace aw
#endif//aw_fileformat_obj_loader_h
