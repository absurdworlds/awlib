/*
 * Code in this file is placed in public domain.
 * Contact: Hedede <Haddayn@gmail.com>
 */
#ifndef aw_gl_types
#define aw_gl_types
#include <aw/types/types.h>
#include <aw/config.h>

#define AW_GL_EXP // TODO

#if (AW_PLATFORM_SPECIFIC == AW_PLATFORM_APPLE)
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif

using GLenum     = unsigned int;
using GLboolean  = unsigned char;
using GLbitfield = unsigned int;
using GLvoid     = void;
using GLbyte     = signed char;
using GLshort    = short;
using GLint      = int;
using GLubyte    = unsigned char;
using GLushort   = unsigned short;
using GLuint     = unsigned int;
using GLsizei    = int;
using GLfloat    = float;
using GLclampf   = GLfloat;
using GLdouble   = double;
using GLclampd   = GLdouble;
using GLchar     = char;
using GLcharARB  = char;
using GLhalfARB  = GLushort;
using GLhalf     = GLushort;
using GLfixed    = GLint;
using GLintptr      = aw::ptrdiff_t;
using GLsizeiptr    = aw::ptrdiff_t;
using GLintptrARB   = aw::ptrdiff_t;
using GLsizeiptrARB = aw::ptrdiff_t;
using GLint64       = aw::i64;
using GLuint64      = aw::u64;
using GLint64EXT    = aw::i64;
using GLuint64EXT   = aw::u64;
using GLsync = struct __GLsync*;

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
#define AWGL_API __stdcall
#else
#define AWGL_API
#endif

struct _cl_context;
struct _cl_event;
using GLDEBUGPROC    = void (AWGL_API *)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
using GLDEBUGPROCARB = void (AWGL_API *)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
using GLDEBUGPROCAMD = void (AWGL_API *)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);

using GLhalfNV = unsigned short;
using GLvdpauSurfaceNV = GLintptr;
#endif//aw_gl_types
