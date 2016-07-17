/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_export_h
#define aw_log_export_h
#include <aw/config.h>
#ifdef AW_MODULE_LOG
	#define AW_LOG_EXP AW_EXPORT
#else
	#define AW_LOG_EXP AW_IMPORT
#endif
// Namespace descriptions for Doxygen
namespace aw {
//! This namespace contains interfaces/tools for logging.
inline namespace log {}
}
#endif//aw_log_export_h
