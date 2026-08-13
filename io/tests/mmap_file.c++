#include <aw/io/mmap_file.h>
#include <aw/test/test.h>
#include <aw/types/array_view.h>
#include <algorithm>

#include "temp_file.h"

TestFile("mmap file");

// TODO: test E2BIG

namespace aw {
using fm = io::file_mode;
using mp = io::map_perms;
using test::temp_file;

Test(mmap_basic_read) {
	constexpr size_t buf_size = 0x12000;

	std::vector<char> buf1(buf_size, 'a');
	buf1[buf_size - 0x10] = 'b';

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(buf1), intmax_t(buf_size) );
	}

	Checks {
		io::mmap_file mapped(file.path, io::map_perms::read);
		array_view<char> view1(mapped);
		array_view<char> view2(buf1);
		// buf_size is too large to be properly displayed
		// so TestAssert here instead of TestEqual
		//TestEqual( view1, view2 );
		TestAssert( view1 == view2 );
	}
};

Test(mmap_view_read) {
	constexpr size_t buf_size = 0x12000;

	std::vector<char> buf1(buf_size, 'a');
	buf1[buf_size - 0x10] = 'd';

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(buf1), intmax_t(buf_size) );
	}

	Checks {
		io::mmap_view file_view(file.path);

		TestAssert(file_view.is_open());
		TestEqual(file_view.size(), buf_size);

		array_view<char> view1(file_view);
		array_view<char> view2(buf1);

		TestAssert( view1 == view2 );
	}
};

/*!
 * A write-only mapping opens, and what is written through it reaches the
 * file
 */
Test(mmap_write_only_still_maps) {
	constexpr size_t buf_size = 0x1000;

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(std::vector<char>(buf_size, 'a')), intmax_t(buf_size) );
	}

	Checks {
		std::error_code ec;
		io::mmap_file mapped(file.path, ec, mp::write);

		TestAssert( !ec );
		TestAssert( mapped.is_open() );

		std::fill(mapped.begin(), mapped.end(), 'z');
	}

	Checks {
		TestEqual( file.read(), std::vector<char>(buf_size, 'z') );
	}
};

/*!
 * Asking for no permissions is refused, rather than reported as open and
 * then faulting on the first read
 */
Test(mmap_rejects_no_permissions) {
	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write("data"), intmax_t(4) );
	}

	Checks {
		std::error_code ec;
		io::mmap_file mapped(file.path, ec, mp::none);

		TestAssert( bool(ec) );
		TestAssert( !mapped.is_open() );
	}
};

Test(mmap_write_back) {
	constexpr size_t buf_size = 0x12000;

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(std::vector<char>(buf_size, 'a')), intmax_t(buf_size) );
	}

	std::vector<char> expected(buf_size, 'z');

	Checks {
		io::mmap_file mapped(file.path, io::map_perms::rdwr);
		TestAssert(mapped.is_open());
		std::fill(mapped.begin(), mapped.end(), 'z');

		array_view<char> view1(mapped);
		array_view<char> view2(expected);

		TestAssert( view1 == view2 );
	}

	Checks {
		TestAssert( file.read() == expected );
	}
};

Test(mmap_missing_file) {
	// constructed and left empty, so nothing is on disk to map
	temp_file file{_context.name};

	Preconditions {
		TestAssert( !file.exists() );
	}

	Checks {
		std::error_code ec;
		io::mmap_file mapped(file.path, ec, io::map_perms::read);
		TestAssert(bool(ec));
		TestAssert(!mapped.is_open());
	}
};

/*!
 * A mapping that has been unmapped no longer counts as valid
 */
Test(unmap_leaves_nothing_behind) {
	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write("data"), intmax_t(4) );
	}

	std::error_code ec;
	io::native::file opened(file.path, fm::read);

	auto mapping = io::native::map_file(opened.descriptor(), mp::read, ec);

	Preconditions {
		TestAssert( !ec );
		TestAssert( mapping.valid() );
	}

	// double-unmapping is a no-op
	Checks {
		TestAssert( io::native::unmap_file(mapping, ec) );
		TestAssert( !ec );

		TestAssert( !mapping.valid() );
	}
};

/*!
 * An unmap that fails leaves behind only what it could not release, so
 * trying again finishes the job instead of failing on what is gone
 */
Test(unmap_can_be_retried_after_a_failure) {
	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write("data"), intmax_t(4) );
	}

	std::error_code ec;
	io::native::file opened(file.path, fm::read);

	auto mapping = io::native::map_file(opened.descriptor(), mp::read, ec);

	Preconditions {
		TestAssert( !ec );
		TestAssert( mapping.valid() );
	}

	void* const view = mapping.address;

	// deliberately misaligned, so no platform will accept it
	mapping.address = reinterpret_cast<void*>(uintptr_t(0x1001));

	Checks {
		TestAssert( !io::native::unmap_file(mapping, ec) );
		TestAssert( bool(ec) );
	}

	// hand back the real view: only that is left to release
	Checks {
		mapping.address = view;

		TestAssert( io::native::unmap_file(mapping, ec) );
		TestAssert( !ec );
		TestAssert( !mapping.valid() );
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
	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(""), intmax_t(0) );
		TestAssert( file.exists() );
		TestEqual( file.size(), 0u );
	}

	Checks {
		std::error_code ec;
		io::mmap_file mapped(file.path, ec, io::map_perms::read);
		TestAssert(!ec);
		TestAssert(!mapped.is_open());
		TestEqual(mapped.size(), 0u);
	}
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
	char const code[] = {
		'\xb8', '\x2a', '\x00', '\x00', '\x00', // mov eax, 42
		'\xc3'                                  // ret
	};

	temp_file file{_context.name};

	Preconditions {
		TestEqual( file.write(std::string_view{code, sizeof(code)}), intmax_t(sizeof(code)) );
	}

	Checks {
		std::error_code ec;
		io::mmap_file mapped(file.path, ec, mp::read|mp::exec);
		TestAssert(!ec);
		TestAssert(mapped.is_open());

		if (mapped.is_open()) {
			auto func = reinterpret_cast<int(*)()>(mapped.data());
			// will segfault with wrong perms
			TestEqual(func(), 42);
		}
	}
};
#endif
} // namespace aw
