/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/hdf/Parser.h>

namespace aw {
namespace gui {
namespace {
void readObjects(hdf::Parser* hdf, Style& parent)
{
	while (hdf->read()) {
		hdf::Object obj = hdf->getObject();

		if (obj.type == hdf::Object::Node) {
			Style& tmp = parent.substyle(obj.name);
			readObjects(hdf, tmp);
		} else if (obj.type == hdf::Object::Value) {
			hdf::Value val;
			hdf->readValue(val);
			parent.property(obj.name) = val;
		} else if (obj.type == hdf::Object::NodeEnd) {
			return;
		}
	}	
}
}

Style StyleLoader::loadStyle(InputStream& stream)
{
	Style style;
	std::unique_ptr<hdf::Parser> hdf(hdf::createParser(stream));

	while (hdf->read()) {
		hdf::Object obj = hdf->getObject();

		if (obj.type != hdf::Object::Node)
			continue;

		Style& tmp = style.substyle(obj.name);
		readObjects(hdf.get(), tmp);
	}

	return style;
}
} // namespace gui
} // namespace aw
