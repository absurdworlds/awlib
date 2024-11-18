#ifndef aw_gl_export_h
#define aw_gl_export_h
#include <aw/config.h>
#ifdef AW_MODULE_GL_LOADER
#define AW_GL_EXP AW_EXPORT
#else
#define AW_GL_EXP AW_IMPORT
#endif
#endif//aw_gl_export_h
