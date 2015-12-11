/*
 * AWengine Utility Library
 * Copyright (C) 2013-2015  absurdworlds
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. 
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>. 
 */
#ifndef aw_utils_h_
#define aw_utils_h_
#include <aw/config/visibility.h>

#ifdef AW_MODULE_UTILS
	#define AW_UTILS_EXP AW_EXPORT
#else
	#define AW_UTILS_EXP AW_IMPORT
#endif

// Namespace descriptions for Doxygen
namespace aw {
/*!
 * Namespace for aw utility library.
 * Contains miscellaneous helpers and utilities.
 */
namespace utils {}
}
#endif//aw_utils_h_
