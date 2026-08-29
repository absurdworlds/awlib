#include <aw/test/test.h>
#include <aw/math/matrix4.h>
#include <aw/math/matrix3.h>
#include <aw/math/matrix_extras.h>
#include <aw/math/transform.h>
#include <aw/math/matrix_compare.h>
#include <aw/math/vector_compare.h>
#include <aw/string/to_string/math/matrix.h>
#include <aw/string/to_string/math/vector.h>
#include <aw/types/traits/basic_traits.h>

#include <algorithm>

TestFile("Matrix");

namespace aw {
namespace math {
// Kept trivially copyable; see the note in vector.c++
static_assert(is_trivially_copyable<matrix<float,3,3>>);
static_assert(is_trivially_copyable<matrix<double,4,4>>);
static_assert(std::is_standard_layout_v<matrix<float,4,4>>);
static_assert(std::is_trivial_v<matrix<float,4,4>>);
static_assert(sizeof(matrix<float,4,4>) == 16 * sizeof(float));

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

Test(matrix_copy_assignment) {
	matrix<int,3,3> src {{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	}};
	matrix<int,3,3> dst {{
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	}};

	Checks {
		dst = src;

		TestEqual(dst, src);
	}
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

//! extend pads the added row and column from the identity, so that
//! expanding a rotation gives a transform with no translation
Test(matrix_extend) {
	auto const rot = matrix_from_euler( vector3d<radians<double>>{
		radians<double>{0.4}, radians<double>{0.3}, radians<double>{0.2} } );

	auto const expanded = extend(rot);

	Checks {
		TestEqual( sub_matrix<3,3>(expanded), rot );
	}

	Checks {
		TestEqual( expanded, make_transform(vector3d<double>{}, rot) );
	}

	Postconditions {
		TestEqual( translation(expanded), vector3d<double>{0, 0, 0} );
		TestEqual( get<3,3>(expanded), 1.0 );
	}
}

//! the ^T / ^-1 sugar, which has never been compiled
Test(matrix_extras_sugar) {
	using namespace matrix_extras;

	matrix<double,2,3> const A{
		1, 2, 3,
		4, 5, 6,
	};

	Checks {
		TestEqual( A ^ T, transpose(A) );
	}

	Checks {
		auto const sq = matrix<double,2,2>{ 4, 7, 2, 6 };
		auto const inv = sq ^ -1;

		TestAssert( bool(inv) );
		if (inv)
			TestEqual( sq * inv.value(), identity_matrix<double,2> );
	}
}

//! sub_matrix drops one row and one column -- checked where M != N,
//! since a square matrix hides a swap of the two
Test(matrix_sub_matrix) {
	matrix<int,2,3> const A{
		1, 2, 3,
		4, 5, 6,
	};

	Setup {
		using dropped = decltype(sub_matrix<0,0>(A));
		TestAssert( dropped::num_rows    == 1 );
		TestAssert( dropped::num_columns == 2 );
	}

	Checks {
		TestEqual( sub_matrix<0,0>(A), matrix<int,1,2>{ 5, 6 } );
		TestEqual( sub_matrix<0,2>(A), matrix<int,1,2>{ 4, 5 } );
		TestEqual( sub_matrix<1,1>(A), matrix<int,1,2>{ 1, 3 } );
	}

	Checks {
		// the square case the rest of the library relies on
		auto const m4 = identity_matrix<double,4>;
		TestEqual( sub_matrix<3,3>(m4), identity_matrix<double,3> );
	}
}

//! set_column writes the column that col() reads back
Test(matrix_set_column) {
	matrix<int,2,3> mat{
		1, 2, 3,
		4, 5, 6,
	};

	// a column of a 2×3 holds one entry per row, so two of them
	vector<int,2> const replacement{ 7, 8 };

	Checks {
		set_column(mat, replacement, 1);

		matrix<int,2,3> const expected{
			1, 7, 3,
			4, 8, 6,
		};
		TestEqual( mat, expected );
	}

	Postconditions {
		TestEqual( col<1>(mat), replacement );
	}
}

//! scalar and unary operators, on a matrix that is not square
Test(matrix_scalar_ops) {
	matrix<int,2,3> const A{
		1, 2, 3,
		4, 5, 6,
	};

	matrix<int,2,3> const twice{
		2, 4,  6,
		8, 10, 12,
	};

	matrix<int,2,3> const negated{
		-1, -2, -3,
		-4, -5, -6,
	};

	Checks {
		TestEqual( A * 2, twice );
		TestEqual( 2 * A, twice );
	}

	Checks {
		TestEqual( twice / 2, A );
	}

	Checks {
		TestEqual( -A, negated );
		TestEqual( +A, A );
	}
}

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
