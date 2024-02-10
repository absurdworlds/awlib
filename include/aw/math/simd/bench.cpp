#include <pmmintrin.h>
float dot_ps(__m128 x, __m128 y)
{
	// note: I ordered LHS arguments specifically to coax
	// GCC into producing one movaps less
	y = _mm_mul_ps(y, x);    // x*y  -> abcd
	x = _mm_movehdup_ps(y);  // abcd -> bbdd
	y = _mm_add_ps(y, x);    // abcd  + bbdd -> stuv
	x = _mm_movehl_ps(x, y); // stuv -> uvuv (s = a+b, u = c+d)
	x = _mm_add_ps(x, y);    // stuv  + uvuv -> a+b+c+d
	return _mm_cvtss_f32(x);
}

float dot_ps2(__m128 x, __m128 y)
{
	// note: I reordered multiplication args
	// to coax GCC into storing result into xmm0
	x = _mm_mul_ps(y,x);    // x*y -> abcd
	x = _mm_hadd_ps(x,x); // acac + bdbd -> stuv (s = a+b, u = c+d)
	x = _mm_hadd_ps(x,x); // stst + uvuv -> a+b+c+d
	return _mm_cvtss_f32(x);
}

float nonsse(__m128 a, __m128 b)
{
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3];
}

extern __m128 volatile a;
extern __m128 volatile b;
void store(float f);
#include <chrono>
#include <iostream>
int main()
{
	for (int j = 0; j <10; ++j) {
		int niters = 10000000;
	using namespace std::chrono;
	auto t1 = steady_clock::now();
	for (int i = 0; i < niters; ++i)
		store(dot_ps(a,b));
	auto t2 = steady_clock::now();
	for (int i = 0; i < niters; ++i)
		store(dot_ps2(a,b));
	auto t3 = steady_clock::now();
	for (int i = 0; i < niters; ++i) {
		store(nonsse(a,b));
	}
	auto t4 = steady_clock::now();

	std::cout << "v1: " << duration<double>(t2-t1).count() << "s\n";
	std::cout << "v2: " << duration<double>(t3-t2).count() << "s\n";
	std::cout << "no: " << duration<double>(t4-t3).count() << "s\n";
	std::cout <<"---\n";
	}
	std::cout << dot_ps(a,b) << '\n';
	std::cout << dot_ps2(a,b) << '\n';
	std::cout << nonsse(a,b) << '\n';
}
