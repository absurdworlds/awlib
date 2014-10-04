/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_utf_convert_
#define _hrengin_utf_convert_

#include <string>

#include <hrengin/common/utf.h>
#include <hrengin/common/stringutils.h>

namespace hrengin {
namespace locale {

template<typename out_type, typename in_type>
std::basic_string<out_type>
utf_convert(in_type const* begin, in_type const* end)
{
	typedef std::basic_string<out_type> value_type;
	typedef std::back_insert_iterator<value_type> iterator_type;

	value_type result;
	iterator_type it(result);

	while(begin != end) {
		u32 cp = UTF<in_type>::template get<in_type const *>(begin, end);

		if(cp == -1) {
			continue;
		} 

		UTF<out_type>::template append<iterator_type>(cp, it);
	}

	return result;
}

template<typename out_type, typename in_type>
std::basic_string<out_type>
utf_convert(std::basic_string<in_type> const& str)
{
	typedef typename std::basic_string<out_type> value_type;
	typedef typename std::back_insert_iterator<value_type> out_iterator_type;
	typedef typename std::basic_string<in_type>::const_iterator in_iterator_type;

	value_type result;
	in_iterator_type begin(str.begin());
	in_iterator_type end(str.end());
	out_iterator_type out(result);

	while(begin != end) {
		u32 cp = UTF<in_type>::template get<in_iterator_type>(begin, end);

		if(cp == -1) {
			continue;
		} 

		UTF<out_type>::template append<out_iterator_type>(cp, out);
	}

	return result;
}

template<typename out_type, typename in_type>
out_type* utf_convert(out_type* buffer, size_t buffer_size,
	in_type const* begin, in_type const* end)
{
	out_type* output = buffer;
	if(buffer_size == 0) {
		return 0;
	}

	-- buffer_size;

	while(begin != end) {
		u32 cp = UTF<in_type>::template get<in_type const *>(begin, end);

		if(cp == -1) {
			continue;
		}

		size_t width = UTF<out_type>::width(cp);

		if(buffer_size < width) {
			output = 0;
			break;
		}

		buffer = UTF<out_type>::template append<out_type *>(cp, buffer);
		buffer_size -= width;
	}
	*buffer++ = 0;
	return output;
}

inline char* narrow(char *output,size_t output_size,wchar_t const *source)
{
	return utf_convert(output,output_size,source,source + strlen_g(source));
}
inline char* narrow(char *output,size_t output_size,wchar_t const *begin,wchar_t const *end)
{
	return utf_convert(output,output_size,begin,end);
}

inline wchar_t* widen(wchar_t *output,size_t output_size,char const *source)
{
	return utf_convert(output,output_size,source,source + strlen_g(source));
}

inline wchar_t* widen(wchar_t *output,size_t output_size,char const *begin,char const *end)
{
	return utf_convert(output,output_size,begin,end);
}


inline std::string narrow(wchar_t const *s)
{
	return utf_convert<char>(s, s + strlen_g(s));
}
inline std::wstring widen(char const *s)
{
	return utf_convert<wchar_t>(s, s + strlen_g(s));
}

inline std::string narrow(std::wstring const& s) 
{
	return utf_convert<char>(s);
}
inline std::wstring widen(std::string const& s) 
{
	return utf_convert<wchar_t>(s);
}


} // namespace locale
} // namespace hrengin

#endif//_hrengin_utf_convert_
