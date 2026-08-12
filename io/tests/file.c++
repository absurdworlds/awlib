#include <aw/io/file.h>
#include <aw/io/buffered_file.h>
#include <aw/test/test.h>
#include <cstdio>
#include <cstring>
#include <algorithm>

TestFile("File IO");

namespace aw {
Test(basic_rw) {
	char const filename[] { "~temp_io_test.bin" };
	constexpr size_t buf_size = 0x12000;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	auto fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::file file(filename, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1.data(), buf1.size());
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::file(filename, io::file_mode::read);
	}

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.read(buf2.data(), buf2.size());
		TestAssert(ret > 0);
	}

	Postconditions {
		// buf_size is too large to be properly displayed
		// so TestAssert here instead of TestEqual
		TestAssert( buf1 == buf2 );
	}

	file.close();
	fs::remove( filename );
};

Test(size_reports_error) {
	io::file file{ io::invalid_fd };

	TestCatch(fs::filesystem_error, file.size());
};

Test(buffered_file_move_keeps_path) {
	char const filename[] { "~temp_io_movepath_test.bin" };
	char const data[]     { "abcde" };

	auto const fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::buffered_file file(filename, fm);
	file.write(data, sizeof(data) - 1);
	file.flush();

	Preconditions {
		TestAssert(file.is_open());
	}

	auto const old_path = file.path();

	io::buffered_file moved(std::move(file));

	Checks {
		TestAssert(moved.is_open());
		TestEqual(moved.path().string(), old_path.string());
		TestEqual(moved.size(), intmax_t(sizeof(data) - 1));
	}

	moved.close();
	fs::remove(filename);
};

Test(basic_buf_rw) {
	char const filename[] { "~temp_io_test.bin" };
	constexpr size_t buf_size = 0x12000;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	auto const fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::buffered_file file(filename, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1.data(), buf1.size());
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::buffered_file(filename, io::file_mode::read);
	}

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.read(buf2.data(), buf2.size());
		TestAssert(ret > 0);
	}

	Postconditions {
		TestAssert( buf1 == buf2 );
	}

	file.close();
	fs::remove( filename );
};
} // namespace aw
