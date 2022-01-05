/*
 * Copyright (C) 2020 absurdworlds
 * Copyright (C) 2020 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_doc_document_h
#define aw_doc_document_h
#include <aw/doc/node.h>
namespace aw {
inline namespace v1 {

struct document {
	explicit document(doc::node node)
		: _root(std::move(node))
	{
	}

	doc::node  const& root() const { return _root; }
	doc::node  const* node(string_view path)  const;
	doc::value const* value(string_view path) const;


	auto nodes()  const { return _root.children.view(); };

	node_list nodes()  const { return _root.children.view(); };

	bool empty() { return _root.empty(); }

	template<typename T>
	T get(string_view path, T def)
	{
		if (auto val = value(path))
			return val->try_get(def);
		return def;
	}

private:
	doc::node _root;
};

} // inline namespace v1
} // namespace aw

#endif//aw_doc_document_h
