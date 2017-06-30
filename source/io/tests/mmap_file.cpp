#include <aw/io/mmap_file.h>
#include <aw/utility/test.h>
#include <aw/types/array_view.h>
#include <algorithm>

TestFile("mmap file");

namespace aw {
Test(mmpa_basic_read) {
	char const filename[] { "~temp_mmap_test.bin" };
	constexpr size_t buf_size = 0x12000;

	char* buf1 = new char[buf_size];
	std::fill_n(buf1, buf_size, 'a');
	buf1[buf_size - 0x10] = 'b';

	using fm = io::file_mode;
	auto mode = fm::write|fm::create|fm::truncate;

	Checks {
		io::native::file file(filename, mode);
		auto ret = file.write(buf1, buf_size);
		TestAssert(ret > 0);
	}

	Checks {
		io::mmap_file file(filename, io::map_perms::read);
		array_view<char> view1(file);
		array_view<char> view2(buf1, buf_size);
		TestEqual( view1, view2 );
	}

	fs::remove( filename );
};
} // namespace aw
