/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/doc/parser.h>
#include <aw/doc/utility.h>
#include <aw/utility/string/split.h>
#include <cassert>
#include <fstream>
namespace aw {
namespace doc {
inline namespace v1 {
namespace {
bool find_node(parser& parser, string_view name)
{
	std::vector<string_view> str = string::split(name, "/");
	std::reverse(str.begin(), str.end());
	if (str.empty())
		return false;

	object obj;
	while (parser.read(obj)) {
		if (obj.kind != object::node)
			continue;

		if (obj.name != str.back()) {
			parser.skip_node();
			continue;
		}

		str.pop_back();
		if (str.empty())
			return true;
	}
	return false;
}
} // namespace

//------------------------------------------------------------------------
node parse_node(parser& parser)
{
	node node;
	object obj;

	while (parser.read(obj)) {
		auto const& name = obj.name;
		switch (obj.kind) {
			case object::node: {
				auto child = parse_node(parser);
				child.name = name;
				child.value = obj.val;
				node.children.add(child);
				break;
			}
			case object::value:
				node.children.add(doc::node{ name, obj.val });
				break;
			case object::null:
				// assert(false);
				continue;
			case object::end:
				return node;
		}
	}
	return node;
}

value find_value(io::input_stream& file, string_view name, log* l)
{
	doc::parser parser(file, l);

	size_t pos = name.rfind('/');
	if (pos != name.npos) {
		if (!find_node(parser, name.substr(0, pos)))
			return value();
		name = name.substr(pos + 1);
	}

	object obj;
	while (parser.read(obj)) {
		if (obj.kind == object::end)
			return value();

		if (obj.kind == object::node) {
			parser.skip_node();
			continue;
		}

		if (obj.name == name)
			return obj.val;
	}

	return {};
}

node find_node(io::input_stream& file, string_view name, log* l)
{
	doc::parser parser(file, l);
	if (find_node(parser, name))
		return parse_node(parser);
	return {};
}

document parse_file(io::input_stream& file, log* l)
{
	doc::parser parser(file, l);
	return document{ parse_node(parser) };
}
} // inline namespace v1
} // namespace doc
} // namespace aw
