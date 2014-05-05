

#ifndef __HR_TYPE_H__
#define __HR_TYPE_H__

namespace hrengin
{
/* int typedefs for better portability */
#if defined(_MSC_VER)
typedef unsigned __int8		uint8;
#else
typedef unsigned char		uint8;
#endif

#if defined(_MSC_VER)
typedef signed __int8		int8;
#else
typedef signed char			int8;
#endif


#if defined(_MSC_VER)
typedef unsigned __int8		uint16;
#else
typedef unsigned short		uint16;
#endif

#if defined(_MSC_VER)
typedef signed __int8		int16;
#else
typedef signed short		int16;
#endif


#if defined(_MSC_VER)
typedef unsigned __int32	uint32;
#else
typedef unsigned int		uint32;
#endif

#if defined(_MSC_VER)
typedef signed __int32		int32;
#else
typedef signed int			int32;
#endif

typedef float				float32;

typedef double				float64;
}

#endif //__HR_TYPE_H__