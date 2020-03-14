/*
 * Copyright (C) 2013-2020  absurdworlds
 * Copyright (C) 2016-2020  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_doc_export_h
#define aw_fileformat_doc_export_h
#include <aw/config.h>

#ifdef AW_MODULE_DOC
	#define AW_DOC_EXP AW_EXPORT
#else
	#define AW_DOC_EXP AW_IMPORT
#endif
#endif//aw_fileformat_doc_export_h
