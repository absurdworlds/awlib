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

namespace aw {
namespace string {
static constexpr char CompositionChar = '%';

std::string compose(string_view fmt, array_view<std::string> args)
{
	constexpr char delim = CompositionChar;

	std::string result;
	result.reserve(fmt.size());

	size_t pos = 0;

	while (pos != std::string::npos) {
		size_t nextpos = fmt.find(delim, pos);

		// TODO: C++17 string.append(string_view)
		auto temp = fmt.substr(pos, nextpos - pos);
		result.append(temp.data(), temp.size());
		if (nextpos == std::string::npos)
			break;

		char idx = fmt[++nextpos];
		// '%0' is replaced by one of positional arguments
		if (isdigit(idx)) {
			pos = nextpos;

			while (isdigit(fmt[nextpos]))
				++nextpos;

			// TODO: C++17 from_chars
			std::string temp(fmt.substr(pos, nextpos - pos));
			size_t arg_no = stoull(temp);

			if (arg_no < args.size())
				result += args[arg_no];
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
} // namespace string
} // namespace aw
