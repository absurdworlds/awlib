#include "vector.h"
void use(aw::simd::vec4f& v);
#include <chrono>
#include <iostream>
int main()
{
	using namespace aw;

	simd::vector<float, 4> vec{1,1,0,0};
	std::cout << vec.length() << '\n';
	vec += vec;
	std::cout << vec[1] << '\n';

	using namespace std::chrono;
	constexpr int niter = 100'000'000;
	for (int i = 0; i < niter; ++i)
	{
		use( vec );
		simd::vec4f n = vec.normalized();
		use( n );
	}
	for (int i = 0; i < niter; ++i)
	{
		use( vec );
		simd::vec4f n = vec.normalized2();
		use( n );
	}
	auto t3 = steady_clock::now();
	for (int i = 0; i < niter; ++i)
	{
		use( vec );
		simd::vec4f n = vec.normalized();
		use( n );
	}
	auto t4 = steady_clock::now();
	auto t1 = steady_clock::now();
	for (int i = 0; i < niter; ++i)
	{
		use( vec );
		simd::vec4f n = vec.normalized2();
		use( n );
	}
	auto t2 = steady_clock::now();
	std::cout << '*' << duration<double>(t2-t1).count() << "s\n";
	std::cout << '/' << duration<double>(t4-t3).count() << "s\n";
	std::cout << "----\n";
}
