/*
 * Copyright (C) 2020 absurdworlds
 * Copyright (C) 2020 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_hudf_document_h
#define aw_hudf_document_h
#include <aw/hudf/node.h>
namespace aw {
inline namespace v1 {

struct document {
	explicit document(hudf::node node)
		: _root(std::move(node))
	{
	}

	hudf::node  const& root() const { return _root; }
	hudf::node  const* node(string_view path)  const;
	hudf::value const* value(string_view path) const;

	using const_iterator = hudf::node::const_iterator;

	auto nodes()  const { return _root.children.view(); };

	const_iterator begin() const { return _root.children.cbegin(); }
	const_iterator end() const { return _root.children.cend(); }

	bool empty() { return _root.empty(); }

	template<typename T>
	T get(string_view path, T def)
	{
		if (auto val = value(path))
			return val->try_get(def);
		return def;
	}

private:
	hudf::node _root;
};

} // inline namespace v1
} // namespace aw

#endif//aw_hudf_document_h
