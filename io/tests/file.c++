#include <aw/io/file.h>
#include <aw/io/buffered_file.h>
#include <aw/test/test.h>
#include <cstring>
#include <algorithm>

#include "temp_file.h"

TestFile("File IO");

namespace aw {
using test::temp_file;

Test(basic_rw) {
	constexpr size_t buf_size = 0x12000;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	temp_file tmp{_context.name};

	auto fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::file file(tmp.path, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1.data(), buf1.size());
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::file(tmp.path, io::file_mode::read);
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
};

Test(size_reports_error) {
	io::file file{ io::invalid_fd };

	TestCatch(fs::filesystem_error, file.size());
};

Test(buffered_file_move_keeps_path) {
	char const data[] { "abcde" };

	temp_file tmp{_context.name};

	auto const fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::buffered_file file(tmp.path, fm);
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
};

Test(basic_buf_rw) {
	constexpr size_t buf_size = 0x12000;

	std::vector<char> buf1(buf_size, 'a');
	std::vector<char> buf2(buf_size, 'x');
	buf1[buf_size - 0x10] = 'b';

	temp_file tmp{_context.name};

	auto const fm = io::file_mode::write|io::file_mode::create|io::file_mode::truncate;
	io::buffered_file file(tmp.path, fm);

	Preconditions {
		TestAssert(file.is_open());
	}

	Checks {
		auto ret = file.write(buf1.data(), buf1.size());
		TestAssert(ret > 0);
	}

	Setup {
		file.close();
		file = io::buffered_file(tmp.path, io::file_mode::read);
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
};
} // namespace aw
