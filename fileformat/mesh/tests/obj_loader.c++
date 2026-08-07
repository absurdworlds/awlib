#include <aw/fileformat/obj/loader.h>

#include <aw/io/input_memory_stream.h>
#include <aw/test/test.h>

#include <string>
#include <string_view>

TestFile( "obj::loader" );

namespace aw {
namespace {
obj::mesh parse(std::string_view text)
{
	io::input_memory_stream is{ text.data(), text.data() + text.size() };
	return obj::mesh::parse( is );
}

//! A cube face needs three vertices; three is the smallest useful mesh
constexpr char const* three_verts =
	"v 0 0 0\n"
	"v 1 0 0\n"
	"v 0 1 0\n";
} // namespace

Test(obj_parses_a_triangle) {
	auto const mesh = parse( std::string(three_verts) + "f 1 2 3\n" );

	Preconditions {
		TestEqual( mesh.verts.size(), size_t(3) );
	}

	Checks {
		TestEqual( mesh.faces.size(), size_t(1) );

		// the file is 1-based, the mesh is 0-based
		TestEqual( mesh.faces[0].verts[0].index, 0u );
		TestEqual( mesh.faces[0].verts[1].index, 1u );
		TestEqual( mesh.faces[0].verts[2].index, 2u );
	}
}

//! Every index in a kept face has to be in range, whatever the file said
Test(obj_out_of_range_indices_are_dropped) {
	auto const in_range = [] (obj::mesh const& mesh) {
		for (auto const& face : mesh.faces)
			for (auto const& v : face.verts)
				if (v.index >= mesh.verts.size())
					return false;
		return true;
	};

	// 0 is not a legal 1-based index; it underflows to -1
	Checks {
		auto const mesh = parse( std::string(three_verts) + "f 0/0/0 2 3\n" );
		TestAssert( in_range(mesh) );
		TestEqual( mesh.faces.size(), size_t(0) );
	}

	Checks {
		auto const mesh = parse( std::string(three_verts) + "f 1 2 999999\n" );
		TestAssert( in_range(mesh) );
		TestEqual( mesh.faces.size(), size_t(0) );
	}

	// a good face alongside a bad one survives
	Checks {
		auto const mesh = parse( std::string(three_verts) +
		                         "f 1 2 3\n"
		                         "f 1 2 999999\n" );
		TestAssert( in_range(mesh) );
		TestEqual( mesh.faces.size(), size_t(1) );
	}
}

//! A normal or texcoord the file did not supply reads back as absent
Test(obj_missing_normal_and_texcoord) {
	constexpr unsigned absent = unsigned(-1);

	Checks {
		auto const mesh = parse( std::string(three_verts) + "f 1 2 3\n" );

		TestEqual( mesh.faces[0].verts[0].normal, absent );
		TestEqual( mesh.faces[0].verts[0].texuv,  absent );
	}

	// ...and so does one it named but never declared
	Checks {
		auto const mesh = parse( std::string(three_verts) +
		                         "f 1//7 2//7 3//7\n" );

		TestEqual( mesh.faces.size(), size_t(1) );
		TestEqual( mesh.faces[0].verts[0].normal, absent );
	}
}

Test(obj_uses_declared_normals) {
	auto const mesh = parse( std::string(three_verts) +
	                         "vn 0 0 1\n"
	                         "f 1//1 2//1 3//1\n" );

	Checks {
		TestEqual( mesh.normals.size(), size_t(1) );
		TestEqual( mesh.faces.size(), size_t(1) );
		TestEqual( mesh.faces[0].verts[0].normal, 0u );
	}
}
} // namespace aw
