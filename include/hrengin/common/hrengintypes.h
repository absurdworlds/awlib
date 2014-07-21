#ifndef __HRENGIN_TYPES_H__
#define __HRENGIN_TYPES_H__

namespace hrengin
{

#if defined(_MSC_VER)
	typedef unsigned __int8		u8;
#else
	typedef unsigned char		u8;
#endif

typedef u8 byte;

#if defined(_MSC_VER)
	typedef signed __int8		i8;
#else
	typedef signed char		i8;
#endif


#if defined(_MSC_VER)
	typedef unsigned __int16	u16;
#else
	typedef unsigned short		u16;
#endif

#if defined(_MSC_VER)
	typedef signed __int16		i16;
#else
	typedef signed short		i16;
#endif


#if defined(_MSC_VER)
	typedef unsigned __int32	u32;
#else
	typedef unsigned int		u32;
#endif

#if defined(_MSC_VER)
	typedef unsigned __int64	u64;
#else
	typedef unsigned long long	u64;
#endif

#if defined(_MSC_VER)
	typedef signed __int32		i32;
#else
	typedef signed int		i32;
#endif

typedef float				f32;

typedef double				f64;

}

#endif //__HRENGIN_TYPES_H__