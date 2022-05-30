/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/string/compose.h>

#include <charconv>

namespace aw::string {
namespace _impl {
static constexpr char CompositionChar = '%';

std::string compose(string_view fmt, std::initializer_list<string_view> args)
{
	constexpr char delim = CompositionChar;

	auto arg = [&args] (size_t arg_no)
	{
		return *(args.begin() + arg_no);
	};

	std::string result;
	result.reserve(fmt.size());

	size_t pos = 0;

	while (pos < fmt.size()) {
		size_t nextpos = fmt.find(delim, pos);

		// TODO: C++17 string.append(string_view)
		auto temp = fmt.substr(pos, nextpos - pos);
		result.append(temp.data(), temp.size());
		if (nextpos == std::string::npos)
			break;

		char idx = fmt[++nextpos];
		// '%0' is replaced by one of positional arguments
		if (std::isdigit(idx)) {
			pos = nextpos;

			size_t arg_no = args.size();

			const auto res = std::from_chars(fmt.data() + pos, fmt.data() + fmt.size(), arg_no);

			nextpos = res.ptr - fmt.data();
			if (arg_no < args.size())
				result += arg(arg_no);
		// '%%' is replaced by a single '%' (for escaping)
		} else if (idx == delim) {
			result += delim;
			++nextpos;
		// Just a '%' written to output unmodified
		} else {
			result += delim;
		}
		pos = nextpos;
	}

	return result;
}
} // namepsace _impl
} // namespace aw
