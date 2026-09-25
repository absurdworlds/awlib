/*
 * Copyright (C) 2026 Hedede <dev@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_config_warning_h
#define aw_config_warning_h
#include <aw/config.h>

/*!
 * \brief Silence deprecation warnings between
 * AW_NOWARN_DEPRECATED_BEGIN and AW_NOWARN_DEPRECATED_END.
 */
#if AW_COMPILER == AW_COMPILER_MSVC
	#define AW_NOWARN_DEPRECATED_BEGIN \
		__pragma(warning(push)) \
		__pragma(warning(disable: 4996))
	#define AW_NOWARN_DEPRECATED_END \
		__pragma(warning(pop))
#elif AW_COMPILER == AW_COMPILER_UNKNOWN
	#define AW_NOWARN_DEPRECATED_BEGIN
	#define AW_NOWARN_DEPRECATED_END
#else
	#define AW_NOWARN_DEPRECATED_BEGIN \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
	#define AW_NOWARN_DEPRECATED_END \
		_Pragma("GCC diagnostic pop")
#endif

#endif//aw_config_warning_h
