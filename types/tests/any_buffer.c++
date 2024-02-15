#include <aw/math/matrix4.h>
#include <aw/math/matrix_compare.h>
#include <aw/test/test.h>
#include <aw/types/containers/any_buffer.h>
#include <aw/utility/to_string/math/matrix.h>

TestFile( "aw::any_buffer" );

Test(any_buffer_basic) {
	using namespace std::string_literals;
	aw::any_buffer<32> buf;
	buf.emplace<std::string>("Test string!"s);
	TestEqual(buf.get<std::string>(), "Test string!"s);
}

using m4 = aw::math::matrix<int, 4, 4>;
struct aligned_matrix {
	alignas(32) m4 m;
};

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
