/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_model_obj_h
#define aw_graphics_model_obj_h
#include <aw/fileformat/obj/loader.h>
#include <aw/graphics/gl/model.h>
#include <aw/utility/ranges/ipairs.h>
#include <map>
#include <tuple>
namespace aw {
namespace gl3 {
model model_from_obj( obj::mesh const& data )
{
	unsigned last_index = 0;
	std::map< std::tuple<unsigned, unsigned, unsigned>, unsigned > indices;
	std::map< std::string, float > matids;
	float last_matid = 0.0;
	std::vector<unsigned> tris;
	std::vector<float> verts;
	std::vector<float> normals;
	std::vector<float> tex;
	std::vector<float> mid;

	auto push = [] (obj::vert const& v, std::vector<float>& c) {
		for (float p : v.points)
			c.push_back(p);
	};

	auto push_normal = [&] (unsigned idx) {
		if (idx == -1) {
			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(0);
		} else {
			push(data.normals[idx], normals);
		}
	};

	auto push_texcoord = [&] (unsigned idx) {
		if (idx == -1) {
			tex.push_back(0);
			tex.push_back(0);
		} else {
			tex.push_back(data.texverts[idx].points[0]);
			tex.push_back(1.0 - data.texverts[idx].points[1]);
		}
	};

	for (auto&& [i, mesh] : ipairs(data.meshes)) {
		if (matids.find(mesh.material) == end(matids)) {
			std::cout << mesh.material << ' ' << last_matid << '\n';
			matids[mesh.material] = last_matid++;
		}
		float matid = matids[mesh.material];
		for (auto j = mesh.begin; j < mesh.end; ++j) {
			auto tri = data.faces[j];
			for (auto& [v,n,t] : tri.verts) {
				if (auto p = indices.find({v,n,t}); p != end(indices)) {
					tris.push_back(p->second);
				} else {
					tris.push_back(last_index);
					indices.insert({{v,n,t}, last_index++});
					push(data.verts[v], verts);
					push_normal(n);
					push_texcoord(t);
					if (data.meshes.size() > 1)
						mid.push_back(matid);
				}
			}
		}
	}

	vertex_data vd;
	vd.format.layout = element_layout::packed;
	vd.format.add_attribute({
		+vertex_attribute_index::position,
		element_type::single_float,
		3
	});
	if (normals.size() != 0)
		vd.format.add_attribute({
			+vertex_attribute_index::normal,
			element_type::single_float,
			3
		});
	if (tex.size() != 0)
		vd.format.add_attribute({
			+vertex_attribute_index::tex_coord_1,
			element_type::single_float,
			2
		});
	if (data.meshes.size() > 1)
		vd.format.add_attribute({
			+vertex_attribute_index::material_id,
			element_type::single_float,
			1
		});

	size_t n = verts.size();
	vd.count = n / 3;

	std::vector<float> soup;
	soup.reserve(n*vd.format.attributes.size());
       	soup.insert( end(soup), begin(verts),   end(verts) );
	soup.insert( end(soup), begin(normals), end(normals) );
	soup.insert( end(soup), begin(tex),     end(tex) );
	if (data.meshes.size() > 1)
		soup.insert( end(soup), begin(mid),     end(mid) );


	vd.data = array_view<std::byte>{
		reinterpret_cast<std::byte*>( soup.data() ),
		soup.size() * sizeof(float)
	};

	mesh_data md{ tris };
	return { vd, md };
}
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_h
