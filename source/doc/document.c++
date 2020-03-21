/*
 * Copyright (C) 2020 absurdworlds
 * Copyright (C) 2020 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/doc/document.h>
#include <aw/utility/string/split.h>
#include <aw/utility/string/lazy_split.h>

namespace aw {
inline namespace v1 {
doc::node* document::node(string_view path)
{
	auto cmpts = aw::string::lazy::split(path, "/");

	doc::node* node = &_root;
	for (string_view name : cmpts)
	{
		if (!node)
			break;
		node = node->nodes.find(name);
	}
	return node;
}

doc::value* document::value(string_view path)
{
	auto divide = path.rfind('/');
	if (divide == path.npos)
		return _root.values.find(path);

	auto node_path = path.substr(0, divide);

	doc::value* val = nullptr;

	auto sought_node = node(node_path);
	if (!sought_node)
		return val;

	auto value_name = path.substr(divide);

	return sought_node->values.find(value_name);
}

} // inline namespace v1
} // namespace aw
