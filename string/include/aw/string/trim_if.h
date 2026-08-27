#ifndef aw_string_trim_if_h
#define aw_string_trim_if_h
#include <algorithm>
#include <string>
#include <aw/types/string_view.h>
namespace aw::string {

/*!
 * Remove characters matching predicate \a pred
 * from the *beginning* of the string \a str.
 */
template <typename Predicate>
std::string& ltrim_if(std::string& str, Predicate pred)
{
	auto first_not = std::find_if_not(begin(str), end(str), pred);
	str.erase(begin(str), first_not);
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from the *end* of the string \a str.
 */
template <typename Predicate>
std::string& rtrim_if(std::string& str, Predicate pred)
{
	auto last_not = std::find_if_not(rbegin(str), rend(str), pred);
	str.erase(last_not.base(), end(str));
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from both end of the string \a str.
 */
template <typename Predicate>
std::string& trim_if(std::string& str, Predicate pred)
{
	return ltrim_if(rtrim_if(str, pred), pred);
}

/*!
 * Create a l-trimmed copy of a string \a str
 */
template <typename Predicate>
std::string ltrimmed_if(std::string str, Predicate pred)
{
	ltrim_if(str, pred);
	return str;
}

/*!
 * Create a r-trimmed copy of a string \a str
 */
template <typename Predicate>
std::string rtrimmed_if(std::string str, Predicate pred)
{
	rtrim_if(str, pred);
	return str;
}

/*!
 * Create a trimmed copy of a string \a str
 */
template <typename Predicate>
std::string trimmed_if(const std::string& str, Predicate pred)
{
	auto first = std::find_if_not(begin(str), end(str), pred);
	auto last = std::find_if_not(rbegin(str), rend(str), pred);
	return str.substr(first - begin(str), last.base() - first);
}

/*!
 * Remove characters matching predicate \a pred
 * from the *beginning* of the string \a str.
 */
template <typename Predicate>
string_view ltrim_if(string_view str, Predicate pred)
{
	auto first_not = std::find_if_not(begin(str), end(str), pred);
	str.remove_prefix(first_not - begin(str));
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from the *end* of the string \a str.
 */
template <typename Predicate>
string_view rtrim_if(string_view str, Predicate pred)
{
	auto last_not = std::find_if_not(rbegin(str), rend(str), pred);
	str.remove_suffix(last_not - rbegin(str));
	return str;
}

/*!
 * Remove characters matching predicate \a pred
 * from both end of the string \a str.
 */
template <typename Predicate>
string_view trim_if(string_view str, Predicate pred)
{
	auto first = std::find_if_not(begin(str), end(str), pred);
	auto last = std::find_if_not(rbegin(str), rend(str), pred);
	return str.substr(first - begin(str), last.base() - first);
}
} // namespace aw::string
#endif//aw_string_trim_if_h
