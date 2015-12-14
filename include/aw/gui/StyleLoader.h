/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_GUI_Style_Loader_
#define aw_GUI_Style_Loader_
#include <aw/io/InputStream.h>
#include <aw/gui/Style.h>

namespace aw {
namespace gui {
class AW_GUI_EXP StyleLoader {
public:
	StyleLoader() = default;
	virtual ~StyleLoader() = default;

	virtual Style loadStyle(io::InputStream& stream) const;
};
} // namespace gui
} // namespace aw
#endif//aw_GUI_Style_Loader_
