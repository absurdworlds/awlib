/*
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awstd/filesystem>

#include <fstream>
#include <string>

#include "awstd_test.h"

namespace fs = awstd::filesystem;

namespace {
void check_decomposition(std::string const& source,
                         std::string const& filename,
                         std::string const& stem,
                         std::string const& extension)
{
	fs::path const p(source);
	std::string const ctx = " [\"" + source + "\"]";

	CheckEqualCtx(p.string(), source, ctx);
	CheckEqualCtx(p.filename().string(),  filename,  ctx);
	CheckEqualCtx(p.stem().string(),      stem,      ctx);
	CheckEqualCtx(p.extension().string(), extension, ctx);
}

void test_decomposition()
{
	check_decomposition("",                "",          "",        "");
	check_decomposition("file.txt",        "file.txt",  "file",    ".txt");
	check_decomposition("/tmp/file.txt",   "file.txt",  "file",    ".txt");
	check_decomposition("/tmp/file",       "file",      "file",    "");
	check_decomposition("/tmp/",           "",          "",        "");
	check_decomposition("/tmp/.hidden",    ".hidden",   ".hidden", "");
	check_decomposition("/tmp/a.b.c",      "a.b.c",     "a.b",     ".c");
	check_decomposition("/tmp/.",          ".",         ".",       "");
	check_decomposition("/tmp/..",         "..",        "..",      "");
}

void test_construction()
{
	CheckEqual(fs::path().empty(), true);
	CheckEqual(fs::path("").empty(), true);
	CheckEqual(fs::path("x").empty(), false);

	char const* ptr = "/tmp/file.txt";
	CheckEqual(fs::path(ptr).string(), std::string(ptr));

	CheckEqual(fs::path(std::string("/tmp/file.txt")).string(),
	           std::string("/tmp/file.txt"));

	CheckEqual(fs::path(L"/tmp/file.txt").string(),
	           std::string("/tmp/file.txt"));

	CheckEqual(fs::path(std::wstring(L"/tmp/file.txt")).string(),
	           std::string("/tmp/file.txt"));

	CheckEqual(fs::path(awstd::string_view("/tmp/file.txt")).string(),
	           std::string("/tmp/file.txt"));

	fs::path const source("/tmp/file.txt");
	fs::path copy(source);
	Check(copy == source);

	copy = fs::path("other");
	Check(copy != source);

	CheckEqual(fs::path("/tmp/file.txt").wstring() == std::wstring(L"/tmp/file.txt"),
	           true);
}

void test_conversion()
{
	CheckEqual(fs::path("/tmp/file.txt").generic_string(),
	           std::string("/tmp/file.txt"));

	fs::path preferred("/tmp/file.txt");
	preferred.make_preferred();

	std::string const expected =
		fs::path::preferred_separator == '/' ? "/tmp/file.txt" : "\\tmp\\file.txt";

	CheckEqual(preferred.string(), expected);
	CheckEqual(preferred.generic_string(), std::string("/tmp/file.txt"));
}

#if __cplusplus >= 201402L
std::string make_test_file(std::string const& name, std::string const& contents)
{
	std::ofstream file(name.c_str(), std::ios::binary);
	file << contents;
	file.close();
	return name;
}

void test_operations()
{
	fs::path const file = make_test_file("awstd_fs_test.tmp", "0123456789");
	fs::path const missing("awstd_fs_test_missing.tmp");

	Check(fs::exists(file));
	Check(!fs::exists(missing));

	CheckEqual(fs::file_size(file), uintmax_t(10));

	std::error_code ec;
	CheckEqual(fs::file_size(missing, ec), uintmax_t(-1));
	Check(bool(ec));

	ec.clear();
	Check(!fs::remove(missing, ec));
	Check(!ec);

	Check(fs::remove(file, ec));
	Check(!ec);
	Check(!fs::exists(file));

	bool thrown = false;
	try {
		fs::file_size(missing);
	} catch (fs::filesystem_error const& error) {
		thrown = true;
		Check(std::string(error.what()).find(missing.string()) != std::string::npos);
		Check(error.path1() == missing);
	}
	Check(thrown);
}
#else
void test_operations() {}
#endif
} // namespace

int main()
{
	test_construction();
	test_decomposition();
	test_conversion();
	test_operations();

	return awstd_test::result();
}
