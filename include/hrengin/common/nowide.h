/*
   This file is a part of boost library, apart from the fact that it was
   reformatted to match hrengin conventions.
 */
/*
   Copyright (c) 2012 Artyom Beilis (Tonkikh)
   
   Distributed under the Boost Software License, Version 1.0. (See
   accompanying file BOOST_LICENSE_1_0.txt or copy at
   http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef _hrengin_nowide_
#define _hrengin_nowide_

#include <string>

#include <hrengin/common/locale.h>

namespace hrengin {
namespace locale {

typedef enum {
	skip = 0,
	stop = 1,
	default_method = skip
} method_type;

template<typename CharOut,typename CharIn>
std::basic_string<CharOut>
utf_to_utf(CharIn const *begin,CharIn const *end, method_type how = default_method)
{
	std::basic_string<CharOut> result;
	result.reserve(end-begin);
	typedef std::back_insert_iterator<std::basic_string<CharOut> > inserter_type;
	inserter_type inserter(result);
	code_point c;
	while(begin!=end) {
		c=utf_traits<CharIn>::template decode<CharIn const *>(begin,end);
		if(c==illegal || c==incomplete) {
			if(how==stop) {
				break;
				//throw conversion_error();
			}
		} else {
			utf_traits<CharOut>::template encode<inserter_type>(c,inserter);
		}
	}
	return result;
}

template<typename CharOut,typename CharIn>
std::basic_string<CharOut>
utf_to_utf(CharIn const *str, method_type how = default_method)
{
	CharIn const *end = str;

	while(*end) {
		end++;
	}

	return utf_to_utf<CharOut,CharIn>(str,end,how);
}

template<typename CharOut,typename CharIn>
std::basic_string<CharOut>
utf_to_utf(std::basic_string<CharIn> const &str,method_type how = default_method)
{
	return utf_to_utf<CharOut,CharIn>(str.c_str(),str.c_str()+str.size(),how);
}

template<typename CharOut,typename CharIn>
CharOut *basic_convert(CharOut *buffer,size_t buffer_size,CharIn const *source_begin,CharIn const *source_end)
{
	CharOut *rv = buffer;
	if(buffer_size == 0) {
		return 0;
	}
	buffer_size --;
	while(source_begin!=source_end) {
		code_point c = utf_traits<CharIn>::template decode<CharIn const *>(source_begin,source_end);
		if(c==illegal || c==incomplete) {
			rv = 0;
			break;
		}
		size_t width = utf_traits<CharOut>::width(c);
		if(buffer_size < width) {
			rv=0;
			break;
		}
		buffer = utf_traits<CharOut>::template encode<CharOut *>(c,buffer);
		buffer_size -= width;
	}
	*buffer++ = 0;
	return rv;
}

namespace details {
	//
	// wcslen defined only in C99... So we will not use it
	//
	template<typename Char>
	Char const *basic_strend(Char const *s)
	{
		while(*s) {
			s++;
		}
		return s;
	}
}

inline char* narrow(char *output,size_t output_size,wchar_t const *source)
{
	return basic_convert(output,output_size,source,details::basic_strend(source));
}
inline char* narrow(char *output,size_t output_size,wchar_t const *begin,wchar_t const *end)
{
	return basic_convert(output,output_size,begin,end);
}

inline wchar_t* widen(wchar_t *output,size_t output_size,char const *source)
{
	return basic_convert(output,output_size,source,details::basic_strend(source));
}

inline wchar_t* widen(wchar_t *output,size_t output_size,char const *begin,char const *end)
{
	return basic_convert(output,output_size,begin,end);
}

inline u32* utf32(u32 *output,size_t output_size,char const *source)
{
	return basic_convert(output,output_size,source,details::basic_strend(source));
}

inline u32* utf32(u32 *output,size_t output_size,char const *begin,char const *end)
{
	return basic_convert(output,output_size,begin,end);
}


inline std::string narrow(wchar_t const *s)
{
	return utf_to_utf<char>(s);
}
inline std::wstring widen(char const *s)
{
	return utf_to_utf<wchar_t>(s);
}

inline std::string narrow(std::wstring const &s) 
{
	return utf_to_utf<char>(s);
}
inline std::wstring widen(std::string const &s) 
{
	return utf_to_utf<wchar_t>(s);
}

} // namespace locale
} // namespace hrengin
#endif//_hrengin_nowide_
