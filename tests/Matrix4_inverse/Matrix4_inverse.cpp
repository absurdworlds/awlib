/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <iostream>
#include <aw/math/Matrix4.h>
#include <aw/math/Matrix_compare.h>

int main()
{
	aw::Matrix<double,4,4> A{
		1,2,3,4,
		5,6,7,8,
		9,1,1,2,
		3,4,5,1
	};

	auto inv = inverse(A);
	if(!inv)
		return 2;

	aw::Matrix4<double> B = inv.value();

	aw::Matrix4<double> I = A * B;
	aw::Matrix4<double> I2 = aw::makeIdentity<double,4>();

	assert(I == I2);

	I.for_each_row([] (aw::Matrix<double,4,4>::row_type const& r) {
		std::cout<<r.x()<<" "<<r.y()<<" "<<r.z()<<" "<<r.w()<<"\n";
	});

	std::cout << "\n";

	I2.for_each_row([] (aw::Matrix<double,4,4>::row_type r) {
		std::cout<<r.x()<<" "<<r.y()<<" "<<r.z()<<" "<<r.w()<<"\n";
	});
}
