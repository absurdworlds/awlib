#include <aw/utility/test.h>
#include <aw/math/matrix4.h>
#include <aw/math/matrix_compare.h>
#include <aw/utility/to_string/math/matrix.h>

#include <algorithm>

TestFile("Matrix");

namespace aw {
namespace math {
Test(matrix4_identity) {
	matrix<int, 4,4> I {{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	}};

	TestEqual(I, identity_matrix<int,4>);
}
} // namespace math
} // namespace aw
