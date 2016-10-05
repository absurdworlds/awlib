#include <filesystem>

namespace awstd {
namespace filesystem {
namespace {
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
const string_view _path_separators("/\\", 2);
#else
const string_view _path_separators("/", 1);
#endif
}

path& path::make_preferred()
{
#if __cplusplus >= 201103L
	for (char& c : p) {
		if (_path_separators.find(c))
			c = preferred_separator;
	}
#else
	for (size_t i = 0, e = p.size(); i < e; ++i) {
		if (_path_separators.find(p[i]))
			p[i] = preferred_separator;
	}
#endif
	return *this;
}

string_view path::path_view() const
{
	return string_view( p );
}

string_view path::filename_view() const
{
	string_view pv = path_view();
	size_t pos = pv.find_last_of(_path_separators);
	if (pos == pv.npos) return "";
	return pv.substr( pos + 1 );
}

namespace {
struct stem_and_ext {
	stem_and_ext(string_view fn) : stem(fn) {}
	stem_and_ext(string_view fn, string_view ext) : stem(fn), ext(ext) {}
	string_view stem;
	string_view ext;
};

stem_and_ext split_filename(string_view fn)
{
	if (fn.empty() || fn == "." || fn == "..")
		return stem_and_ext(fn);
	size_t pos = fn.rfind('.');
	if (pos == fn.npos)
		return stem_and_ext(fn);
	return stem_and_ext( fn.substr(0, pos), fn.substr(pos) );
}
} // namespace

string_view path::stem_view() const
{
	return split_filename(filename_view()).stem;
}

string_view path::extension_view() const
{
	return split_filename(filename_view()).ext;
}

} // namespace awstd
} // namespace filesystem
