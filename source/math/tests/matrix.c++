#include <aw/utility/test.h>
#include <aw/math/matrix4.h>
#include <aw/math/matrix_compare.h>
#include <aw/utility/to_string/math/matrix.h>

#include <algorithm>

TestFile("Matrix");

namespace aw {
namespace math {
Test(matrix_basic) {
	matrix<int, 4,4> A {{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	}};

	TestEqual(A, identity_matrix<int,4>);

	matrix<int, 3,3> B {{
		{1,2,3},
		{2,2,3},
		{3,3,3},
	}};

	matrix<int, 4,4> C {{
		{1,2,3,0},
		{2,2,3,0},
		{3,3,3,0},
		{0,0,0,1}
	}};

	A = B;
	TestEqual(A, C);

	auto D = A * C;
	A *= C;
	TestEqual(A, D);

	TestEqual( get<15>(C), get<3,3>(C) );
}

Test(matrix_inverse) {
	matrix<double,4,4> A{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 1, 1, 2,
		3, 4, 5, 1
	};

	matrix<double,4,4> B {};
	Checks {
		auto inv = inverse(A);
		TestAssert(bool(inv));
		if (inv) B = inv.value();
	}

	Postconditions {
		auto I1 = A * B;
		auto I2 = identity_matrix<double, 4>;

		TestEqual(I1, I2);
	}
};

Test(matrix_product) {
	matrix<int,4,2> _4x2{
		1,3,
		2,2,
		3,1,
		5,7,
	};

	matrix<int,2,3> _2x3{
		3,5,2,
		4,6,1,
	};

	Setup {
		TestAssert(decltype(_4x2)::num_columns == 2);
		TestAssert(decltype(_4x2)::num_rows    == 4);

		TestAssert(decltype(_2x3)::num_columns == 3);
		TestAssert(decltype(_2x3)::num_rows    == 2);
	}

	matrix<int,4,3> const _4x3{
		15, 23, 5,
		14, 22, 6,
		13, 21, 7,
		43, 67, 17,
	};

	Checks {
		auto mat = (_4x2 * _2x3);
		TestEqual(_4x3, mat);
	}
};
} // namespace math
} // namespace aw
