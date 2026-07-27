/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
/*
 * Check that the headers can be reached under their standard names,
 * when include/awstd is added to the include path (the awstd::shims target).
 */
#include <filesystem>
#include <nullptr>
#include <string_view>

#include "awstd_test.h"

int main()
{
	awstd::string_view sv("/tmp/file.txt");
	CheckEqual(sv.size(), size_t(13));

	awstd::filesystem::path p(sv);
	CheckEqual(p.filename().string(), std::string("file.txt"));

	return awstd_test::result();
}
