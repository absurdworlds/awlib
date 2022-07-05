#include <format>

int main()
{
	auto res = std::format("{}", 1);
	return res.empty();
}
