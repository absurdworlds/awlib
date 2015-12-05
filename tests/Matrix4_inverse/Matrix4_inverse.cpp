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
	aw::Matrix4<double> A(
		1,2,3,4,
		5,6,7,8,
		9,1,1,2,
		3,4,5,1);

	auto inv = A.inverse();
	if(!inv)
		return 2;

	aw::Matrix4<double> B = inv.value();

	aw::Matrix4<double> I = A * B;
	aw::Matrix4<double> I2;

	I2.setIdentity();

	if (I == I2)
		return 0;

	return 1;
}
