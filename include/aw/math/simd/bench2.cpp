#include <mmintrin.h>
#include <immintrin.h>
#include "vector.h"

float x[] { 1, 0.5, 0.75, 0.33 };
float y[] { 0.5, 1, 0.33, 3 };
__m128 volatile a = _mm_load_ps(x);
__m128 volatile b = _mm_load_ps(y);

void store(float f) {}
void store(__m128 v) {}
void use(aw::simd::vec4f& v) {}
