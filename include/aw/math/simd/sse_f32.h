#include <pmmintrin.h>

namespace aw {
namespace sse3 {
using v4f32 = __m128;
using f32   = float __attribute__(( aligned(16) ));// alignas(16);

inline v4f32 broadcast(float x)
{
	return _mm_set1_ps(x);
}

inline v4f32 mul(v4f32 v, float x)
{
	v4f32 s = broadcast(x);
	return _mm_mul_ps(v, s);
}

inline v4f32 div(v4f32 v, float x)
{
	v4f32 s = broadcast(x);
	return _mm_div_ps(v, s);
}

inline v4f32 sqrt(v4f32 v)
{
	return _mm_sqrt_ss(v);
}

//------------------------------------------------------------------------------
// Comparisons
inline bool equal(v4f32 a, v4f32 b)
{
	__m128 cmp = _mm_cmpeq_ps(a, b);
	return _mm_movemask_ps(cmp) == 0b1111;
}

//------------------------------------------------------------------------------
// Arithmetic
inline v4f32 add(v4f32 x, v4f32 y)
{
	return _mm_add_ps(x, y);
}

inline v4f32 mul(v4f32 x, v4f32 y)
{
	return _mm_mul_ps(x, y);
}

inline float dot(v4f32 x, v4f32 y)
{
// haddps appears to be 20% slower
//#define AW_SSE_USE_HADD_PS
#ifndef AW_SSE_USE_HADD_PS
	// note: I ordered LHS arguments specifically to coax
	// GCC into producing one movaps less
	y = _mm_mul_ps(y, x);    // x*y  -> abcd
	x = _mm_movehdup_ps(y);  // abcd -> bbdd
	y = _mm_add_ps(y, x);    // abcd  + bbdd -> stuv
	x = _mm_movehl_ps(x, y); // stuv -> uvuv (s = a+b, u = c+d)
	x = _mm_add_ss(x, y);    // s(tuv) + u(vuv) -> a+b+c+d
	return _mm_cvtss_f32(x);
#else
	// note: I reordered multiplication args
	// to coax GCC into storing result into xmm0
	x = mul(y, x);  // x*y -> abcd
	x = _mm_hadd_ps(x, x); // acac + bdbd -> stuv (s = a+b, u = c+d)
	x = _mm_hadd_ps(x, x); // stst + uvuv -> a+b+c+d
	return _mm_cvtss_f32(x);
#endif
}
} // namespace sse3
} // namespace aw
