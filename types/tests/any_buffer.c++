#include <aw/math/matrix4.h>
#include <aw/math/matrix_compare.h>
#include <aw/types/containers/any_buffer.h>
#include <aw/utility/to_string/math/matrix.h>

#include <aw/test/test.h>
#include <aw/test/helpers/counted.h>

#include <utility>

TestFile( "aw::any_buffer" );

constexpr auto buf_size = std::max({ size_t(32), sizeof(std::string) });

Test(any_buffer_basic) {
	using namespace std::string_literals;
	aw::any_buffer<buf_size> buf;
	buf.emplace<std::string>("Test string!"s);
	TestEqual(buf.get<std::string>(), "Test string!"s);
}

using m4 = aw::math::matrix<int, 4, 4>;
struct aligned_matrix {
	alignas(32) m4 m;
};

//! destroy() must run the destructor of the stored type
Test(any_buffer_destroy) {
	using aw::test::counted;

	aw::any_buffer<sizeof(counted)> buf;

	Setup {
		counted::live = 0;
	}

	Checks {
		buf.emplace<counted>();
		TestEqual( counted::live, 1 );
		TestEqual( buf.get<counted>().value, counted::payload() );

		buf.destroy<counted>();
		TestEqual( counted::live, 0 );
	}
}

Test(any_buffer_aligned) {
	using namespace std::string_literals;
	aw::any_buffer<sizeof(aligned_matrix), 32> buf[3];
	buf[2].emplace<aligned_matrix>(aligned_matrix{{{
		{1, 2, 3, 4},
		{2, 2, 3, 4},
		{3, 2, 3, 4},
		{4, 2, 3, 4},
	}}});
	TestEqual(buf[2].get<aligned_matrix>().m, m4{{
		{1, 2, 3, 4},
		{2, 2, 3, 4},
		{3, 2, 3, 4},
		{4, 2, 3, 4},
	}});
}
