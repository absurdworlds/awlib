/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_vertex_format_h
#define aw_graphics_gl3_vertex_format_h
#include <aw/graphics/gl/api/types.h>
#include <aw/types/array_view.h>
#include <vector>
namespace aw {
namespace gl3 {

enum class element_type {
	/* integers */
	signed_byte,
	signed_short,
	signed_int,
	unsigned_byte,
	unsigned_short,
	unsigned_int,

	/* normalized integers */
	signed_byte_norm,
	signed_short_norm,
	signed_int_norm,
	unsigned_byte_norm,
	unsigned_short_norm,
	unsigned_int_norm,

	/* floating point */
	half_float,
	single_float,
	double_float,
	fixed_16_16,

	/* packed */
	signed_int_2_10_10_10_rev,
	unsigned_int_2_10_10_10_rev,
	unsigned_int_10f_11f_11f_rev,
};

GLenum to_gl(element_type);
bool   is_normalized(element_type);

/* This is just a convention I'm using. Not required to be used. */
enum class vertex_attribute_index : size_t {
	position    = 0,
	color       = 1,
	normal      = 2,
	tex_coord_1 = 3,
	tex_coord_2 = 4,
	material_id = 5,
};

inline size_t operator+(vertex_attribute_index i)
{
	return size_t(i);
}

struct vertex_specification;

struct vertex_attribute {
	size_t index;
	element_type type;
	size_t size;
	size_t offset;
};

enum class element_layout {
	/*! (AAA)(BBB)(CCC)(DDD) */
	packed,
	/*! (ABCD)(ABCD)(ABCD)*/
	interleaved
};

struct vertex_specification {
	std::vector< vertex_attribute > attributes;
	element_layout layout;
	size_t size = 0;

	void add_attribute( vertex_attribute attrib )
	{
		attributes.push_back( attrib );
		// TODO: alignment?
		attrib.offset = size;
		// FIXME FIXME FIXME
		// replace 4 with actual size
		size += attrib.size * 4;
	}
};
struct vertex_data {
	array_view<std::byte> data;
	vertex_specification  format;
	size_t count;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_vertex_format_h
