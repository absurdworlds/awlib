/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/math/Matrix4.h>

int main()
{
	aw::Matrix4<double> A{{
		{1,5,9,3},
		{2,6,1,4},
		{3,7,1,5},
		{4,8,2,1}
	}};

	auto inv = inverse(A);
	if(!inv)
		return 2;

	aw::Matrix4<double> B = inv.value();

	aw::Matrix4<double> I = A * B;
	aw::Matrix4<double> I2 = aw::makeIdentity<double,4>();

	assert(I == I2);
}
