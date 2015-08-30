/*
 * HRDF parser & writer library
 *
 * Copyright (C) 2013-2015  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License, version 3
 * as published by the Free Software Foundation.
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
#ifndef _awrts_hdf_
#define _awrts_hdf_
#include <awrts/common/visibility.h>

#ifdef HR_MODULE_HDF
	#define HR_HDF_EXP HR_EXPORT
#else
	#define HR_HDF_EXP HR_IMPORT
#endif

// Namespace descriptions for Doxygen
namespace awrts {
//! Utilities for processing the HDF file format
namespace hdf {}
}
#endif//_awrts_hdf_
