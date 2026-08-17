/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

#include <aw/graphics/gl/vertex_format.h>

#include <aw/test/test.h>

TestFile( "graphics::gl3 vertex format" );

namespace aw::gl3 {
namespace {
//! position (3f), normal (3f), texture coordinate (2f)
vertex_specification interleaved_vertex()
{
	vertex_specification spec;
	spec.layout = element_layout::interleaved;
	spec.add_attribute({ +vertex_attribute_index::position,    element_type::single_float, 3 });
	spec.add_attribute({ +vertex_attribute_index::normal,      element_type::single_float, 3 });
	spec.add_attribute({ +vertex_attribute_index::tex_coord_1, element_type::single_float, 2 });
	return spec;
}

constexpr size_t interleaved_vertex_size = (3+3+2)*sizeof(f32);

//! position (3 floats), color (4 bytes), texture coordinate (2 half floats)
vertex_specification mixed_vertex()
{
	vertex_specification spec;
	spec.layout = element_layout::interleaved;
	spec.add_attribute({ +vertex_attribute_index::position,    element_type::single_float,       3 });
	spec.add_attribute({ +vertex_attribute_index::color,       element_type::unsigned_byte_norm, 4 });
	spec.add_attribute({ +vertex_attribute_index::tex_coord_1, element_type::half_float,         2 });
	return spec;
}

constexpr size_t mixed_vertex_size = 3*sizeof(f32) + 4*sizeof(u8) + 2*sizeof(u16);

//! a normal packed into a single 32-bit word
vertex_specification packed_vertex()
{
	vertex_specification spec;
	spec.layout = element_layout::interleaved;
	spec.add_attribute({ +vertex_attribute_index::position, element_type::single_float,                  3 });
	spec.add_attribute({ +vertex_attribute_index::normal,   element_type::signed_int_2_10_10_10_rev,     4 });
	return spec;
}

constexpr size_t packed_vertex_size = 3*sizeof(f32) + sizeof(u32);
} // namespace

Test(attribute_begins_where_the_previous_one_ended) {
	auto spec = interleaved_vertex();

	Preconditions {
		TestEqual( spec.attributes.size(), size_t(3) );
	}

	Checks {
		TestEqual( spec.size, interleaved_vertex_size );
		TestEqual( spec.attributes[0].offset, size_t(0)  );
		TestEqual( spec.attributes[1].offset, size_t(12) );
		TestEqual( spec.attributes[2].offset, size_t(24) );
	}
}

Test(vertex_attribute_occupies_as_many_bytes_as_its_element_type) {
	auto spec = mixed_vertex();

	Preconditions {
		TestEqual( spec.attributes.size(), size_t(3) );
	}

	Checks {
		TestEqual( spec.size, mixed_vertex_size );
		TestEqual( spec.attributes[0].offset, size_t(0)  );
		TestEqual( spec.attributes[1].offset, size_t(12) );
		TestEqual( spec.attributes[2].offset, size_t(16) );
	}
}

Test(packed_vertex_elements_share_a_single_word) {
	auto spec = packed_vertex();

	Preconditions {
		TestEqual( spec.attributes.size(), size_t(2) );
	}

	Checks {
		TestEqual( spec.size, packed_vertex_size );
		TestEqual( spec.attributes[1].offset, size_t(12) );
	}
}
} // namespace aw::gl3
