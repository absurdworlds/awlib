#include <cmath>
#include "sse_f32.h"

namespace aw {
using f32=float;
using size_t = decltype(sizeof(void*));
namespace simd {
template<typename T, size_t N>
struct vector;

template<>
struct vector<float, 4> {
	__m128 v;

	vector(float x, float y, float z, float w)
		: v{x, y, z, w}
	{}
	vector(vector const& other)
		: v{other.v}
	{}
	vector(__m128 v)
		: v{v}
	{}

	vector& operator+=(vector const& other)
	{
		v = sse3::add(v, other.v);
		return *this;
	}

	vector& operator-=(vector const& other)
	{
		v = _mm_sub_ps(v, other.v);
		return *this;
	}

	vector& operator*=(vector const& other)
	{
		v = sse3::mul(v, other.v);
		return *this;
	}

	vector& operator/=(vector const& other)
	{
		v = _mm_div_ps(v, other.v);
		return *this;
	}

	vector& operator*=(float a)
	{
		v = sse3::mul(v, a);
		return *this;
	}

	vector& operator/=(float a)
	{
		v = sse3::div(v, a);
		return *this;
	}

	float dot(vector const& other) const
	{
		return sse3::dot(v, other.v);
	}

	float lengthSq() const
	{
		return dot( *this );
	}

	float length() const
	{
		return std::sqrt( lengthSq() );
	}

	float& operator[](size_t idx)
	{
		return v[idx];
	}

	vector& normalize()
	{
#if 0
		// It is either 10-20% slower than divps
		// or 1-2% faster, depending on hardware
		float inv_len = 1.0f / length();
		return (*this) *= inv_len;
#else
		return (*this) /= length();
#endif
	}

	vector normalized() const
	{
		vector copy{*this};
		return copy.normalize();
	}
};

using vec4f = vector<float,4>;

inline vec4f operator+(vec4f a, vec4f b)
{
	return _mm_add_ps(a.v, b.v);
}


} // namespace simd
} // namespace aw

