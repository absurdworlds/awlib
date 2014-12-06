/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_default_settings_
#define _hrengin_default_settings_

namespace hrengin {

//! File, which will be used when a settings file is absent in filesystem
const char* const default_settings = 
"[settings"
" [graphics"
"  resolutionX = int:800"
"  resolutionY = int:600"
"  fullscreen = bool:false"
" ]"
"]";

} //namespace hrengin
#endif//_hrengin_default_settings_
