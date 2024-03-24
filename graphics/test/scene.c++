#include "scene.h"

#include <aw/math/transform.h>
#include <aw/math/vector3d.h>
#include <aw/math/matrix3.h>
#include <aw/hudf/utility.h>

#include <aw/log/ostream_logger.h>
#include <aw/io/input_file_stream.h>

#include <iostream>
#include <map>

namespace aw::gl3 {
void parse_shader_list(const doc::node& node, std::vector<shader_source>& out, gl::shader_type type)
{
	switch(node.value.get_type())
	{
		case doc::type::string:
		{
			auto name = node.value.try_get(std::string_view());
			if (!name.empty())
				out.push_back({ type, name });
			break;
		}

		case doc::type::string_vector:
		{
			auto* vec = node.value.get<std::vector<std::string>>();
			for (auto& path : *vec)
			{
				out.push_back({ type, path });
			}
			break;
		}

		default:
			// error: invlaid node
			break;
	}
}

std::vector<shader_source> parse_program(const doc::node& node)
{
	std::vector<shader_source> shaders;

	auto vert = node.find_child("vert");
	if (vert)
	{
		parse_shader_list(*vert, shaders, gl::shader_type::vertex);
	}

	auto frag = node.find_child("frag");
	if (frag)
	{
		parse_shader_list(*frag, shaders, gl::shader_type::fragment);
	}

	return shaders;
}

void scene::load(string_view path)
{
	ostream_logger log{std::cout};
	// open a file
	io::input_file_stream stream{path};

	auto document = doc::parse_file(stream);

	std::map<std::string, size_t> program_map;
	// TODO: inline programs
	std::map<std::string, size_t> model_map;

	for (const auto& node : document)
	{
		if (node.name == "shader")
		{
			auto shaders = parse_program(node);
			if (!shaders.empty())
			{
				const auto id = pman.create_program(shaders);
				program_map.insert({node.value.try_get(std::string()), id});
			}
		}

		if (node.name == "material")
		{
			size_t prgid = -1;
			auto shader = node.find_child("shader");
			if (!shader)
				continue;

			auto shader_name = shader->try_get(std::string());
			if (shader->children.empty())
			{
				if (auto it = program_map.find(shader_name); it != program_map.end())
				{
					prgid = it->second;
				}
			}
			else
			{
				auto shaders = parse_program(*shader);
				if (!shaders.empty())
				{
					prgid = pman.create_program(shaders);
					program_map.insert({ shader_name, prgid});
				}
			}
			if (prgid == size_t(-1))
				continue;

			auto name = node.try_get(std::string());

			auto matid = mman.add_resource(name, material{ pman[prgid] });

			auto textures = node.find_child("textures");
			if (textures)
			{
				for (const auto& texture : textures->children)
				{
					auto* texname = texture.value.get<std::string>();
					if (texname)
					{
						auto texid = tman.create_texture(*texname);
						mman[matid].get().add_texture( texture.name.data(), tman[texid] );
					}

					auto* texarray = texture.value.get<std::vector<std::string>>();
					if (texarray)
					{
						std::vector<string_view> paths;
						for (const auto& s : *texarray)
						{
							paths.push_back(s);
						}

						auto texid = tman.create_texture_array(paths);
						mman[matid].get().add_texture( texture.name.data(), tman[texid] );

						for (auto&& [i,path] : ipairs(paths))
						{
							std::cout << path << ' ' << i << '\n';
						}
					}
				}
			}
		}

		if (node.name == "object")
		{
			object obj;

			obj.scene = this;

			auto model_name = node.try_get("model", std::string());
			if (model_name.empty())
				continue;

			auto material_name = node.try_get("material", std::string());
			if (material_name.empty())
				continue;

			if (auto it = model_map.find(model_name); it != model_map.end())
			{
				obj.model_id = it->second;
			}
			else
			{
				obj.model_id = load_model( model_name );
				model_map.insert({ model_name, obj.model_id });
			}

			obj.material_id = mman.find_by_name(material_name);
			if (obj.material_id == -1)
				continue;

			vec3 pos = {};
			if (auto* pos_node = node.find_child("pos"))
			{
				doc::get_numbers(pos_node->value, pos.elems);
			}

			vec3 rot = {};
			if (auto* pos_node = node.find_child("rot"))
			{
				doc::get_numbers(pos_node->value, rot.elems);
			}

			auto deg = math::vector3d<degrees<float>>( rot );
			obj.pos = make_transform( pos, math::matrix_from_euler( deg ) );
			objects.push_back(obj);
		}
	}
}

size_t scene::load_model(string_view filename)
{
	io::input_file_stream file{ filename };
	auto data = obj::mesh::parse( file );
	models.emplace_back( model_from_obj(data) );
	return models.size() - 1;
}

} // namespace aw::gl3
