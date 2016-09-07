#include <aw/utility/test.h>
#include <aw/math/matrix4.h>
#include <aw/math/matrix_compare.h>
#include <aw/utility/to_string/math/matrix.h>

#include <algorithm>

TestFile("Matrix");

namespace aw {
namespace math {
Test(matrix_inverse) {
	matrix<double,4,4> A{
		1,2,3,4,
		5,6,7,8,
		9,1,1,2,
		3,4,5,1
	};

	matrix<double,4,4> B {};
	Checks {
		auto inv = inverse(A);
		TestAssert(bool(inv));
		if (inv) B = inv.value();
	}

	Postconditions {
		auto I1 = A * B;
		auto I2 = make_identity<double, 4>();

		TestEqual(I1, I2);
	}
};
} // namespace math
} // namespace aw
