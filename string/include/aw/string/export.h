#ifndef aw_string_export_h
#define aw_string_export_h
#include <aw/config.h>

#ifdef AW_MODULE_STRING
	#define AW_STRING_EXP AW_EXPORT
#else
	#define AW_STRING_EXP AW_IMPORT
#endif
#endif//aw_string_export_h
