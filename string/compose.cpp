#include <aw/string/compose.h>

#include <vector>

#include <charconv>

namespace aw::string {
static constexpr char CompositionChar = '%';

std::string compose_v(string_view fmt, array_view<string_view> args)
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

std::string compose_v(string_view fmt, array_view<std::string> args)
{
	std::vector<string_view> tmp(args.begin(), args.end());
	return compose_v(fmt, tmp);
}

} // namespace aw::string
