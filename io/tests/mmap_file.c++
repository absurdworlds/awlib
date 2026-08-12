#include <aw/io/mmap_file.h>
#include <aw/test/test.h>
#include <aw/types/array_view.h>
#include <algorithm>

TestFile("mmap file");

// TODO: test E2BIG
// TODO: look into the temporary file cleanup

namespace aw {
using fm = io::file_mode;
using mp = io::map_perms;

Test(mmap_basic_read) {
	char const filename[] { "~temp_mmap_test.bin" };
	constexpr size_t buf_size = 0x12000;

	char* buf1 = new char[buf_size];
	std::fill_n(buf1, buf_size, 'a');
	buf1[buf_size - 0x10] = 'b';

	const auto mode = fm::write|fm::create|fm::truncate;

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

Test(mmap_view_read) {
	char const filename[] { "~temp_mmap_view_test.bin" };
	constexpr size_t buf_size = 0x12000;

	char* buf1 = new char[buf_size];
	std::fill_n(buf1, buf_size, 'c');
	buf1[buf_size - 0x10] = 'd';

	const auto mode = fm::write|fm::create|fm::truncate;

	Checks {
		io::native::file file(filename, mode);
		auto ret = file.write(buf1, buf_size);
		TestAssert(ret > 0);
	}

	Checks {
		io::mmap_view view(filename);
		TestAssert(view.is_open());
		TestEqual(view.size(), buf_size);
		TestAssert( std::equal(view.begin(), view.end(), buf1, buf1 + buf_size) );
	}

	fs::remove( filename );
};

Test(mmap_write_back) {
	char const filename[] { "~temp_mmap_write_test.bin" };
	constexpr size_t buf_size = 0x12000;

	char* buf1 = new char[buf_size];
	std::fill_n(buf1, buf_size, 'a');

	const auto mode = fm::write|fm::create|fm::truncate;

	Checks {
		io::native::file file(filename, mode);
		auto ret = file.write(buf1, buf_size);
		TestAssert(ret > 0);
	}

	Checks {
		io::mmap_file file(filename, io::map_perms::rdwr);
		TestAssert(file.is_open());
		std::fill(file.begin(), file.end(), 'z');
	}

	Checks {
		char* buf2 = new char[buf_size];
		io::native::file file(filename, fm::read);
		auto ret = file.read(buf2, buf_size);
		TestAssert(ret > 0);

		char* expected = new char[buf_size];
		std::fill_n(expected, buf_size, 'z');
		TestAssert( std::equal(buf2, buf2+buf_size, expected, expected+buf_size) );
	}

	fs::remove( filename );
};

Test(mmap_missing_file) {
	char const filename[] { "~temp_mmap_missing_test.bin" };
	fs::remove( filename );

	Checks {
		std::error_code ec;
		io::mmap_file file(filename, ec, io::map_perms::read);
		TestAssert(bool(ec));
		TestAssert(!file.is_open());
	}
};

Test(mmap_invalid_fd) {
	Checks {
		std::error_code ec;
		io::mmap_file file(io::invalid_fd, ec, io::map_perms::read);
		TestAssert(bool(ec));
		TestAssert(!file.is_open());
	}
};

Test(mmap_empty_file) {
	char const filename[] { "~temp_mmap_empty_test.bin" };

	const auto mode = fm::write|fm::create|fm::truncate;

	Checks {
		io::native::file file(filename, mode);
		TestAssert(file.is_open());
	}

	Checks {
		std::error_code ec;
		io::mmap_file file(filename, ec, io::map_perms::read);
		TestAssert(!ec);
		TestAssert(!file.is_open());
		TestEqual(file.size(), 0u);
	}

	fs::remove( filename );
};

#if 0// (AW_PLATFORM_SPECIFIC == AW_PLATFORM_LINUX)
Test(mmap_blkdevide)
{
	Checks {
		std::error_code ec;
		io::mmap_file file("/dev/sdc1", ec, io::map_perms::read);
		TestAssert(!ec);
	}
}
#endif

#if (AW_ARCH == AW_ARCH_x86_64) || (AW_ARCH == AW_ARCH_i686)
Test(mmap_execute) {
	char const filename[] { "~temp_mmap_exec_test.bin" };

	char const code[] = {
		'\xb8', '\x2a', '\x00', '\x00', '\x00', // mov eax, 42
		'\xc3'                                  // ret
	};

	const auto mode = fm::write|fm::create|fm::truncate;

	Checks {
		io::native::file file(filename, mode);
		auto ret = file.write(code, sizeof(code));
		TestAssert(ret > 0);
	}

	Checks {
		std::error_code ec;
		io::mmap_file file(filename, ec, mp::read|mp::exec);
		TestAssert(!ec);
		TestAssert(file.is_open());

		if (file.is_open()) {
			auto func = reinterpret_cast<int(*)()>(file.data());
			// will segfault with wrong perms
			TestEqual(func(), 42);
		}
	}

	fs::remove( filename );
};
#endif
} // namespace aw
