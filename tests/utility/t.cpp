#include <iostream>
#include "bitmath.h"

void test(size_t v)
{
	std::cout << log2(v) << " "<< aw::math::log2(v) << std::endl;
}
int main()
{
	test(2);
	test(4);
	test(16);
	test(32);
	test(64);
	test(127);
	test(128);
	test(1000);
	test(1023);
	test(1024);
	test(1025);
	test(aw::math::swapBits(0b000'001,5,0));
	std::cout <<std::hex<<0xA00F <<std::endl;
	std::cout <<std::hex<<aw::math::byteswap(0xD00A00Ful) <<std::endl;
	std::cout <<std::hex<<aw::math::byteswap(0xD00A00F) <<std::endl;
}
