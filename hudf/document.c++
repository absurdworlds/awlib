/*
 * Copyright (C) 2020 absurdworlds
 * Copyright (C) 2020 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/hudf/document.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/lazy_split.h>

namespace aw {
inline namespace v1 {
hudf::node const* document::node(string_view path) const
{
	auto cmpts = aw::string::lazy::split(path, "/");

	const hudf::node* node = &_root;
	for (string_view name : cmpts)
	{
		if (!node)
			break;
		node = node->find_child(name);
	}
	return node;
}

hudf::value const* document::value(string_view path) const
{
	hudf::value* val = nullptr;

	auto sought_node = node(path);
	if (!sought_node)
		return val;

	return &sought_node->value;
}

} // inline namespace v1
} // namespace aw
