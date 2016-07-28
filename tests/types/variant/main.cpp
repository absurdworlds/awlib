#include <iostream>

#include <aw/types/variant.h>

int main()
{
	using namespace std::string_literals;

	aw::variant<int, float, std::string> var1;
	var1.set("A string."s);

	std::cout << *var1.get<std::string>() << "\n";

	aw::variant<int,float> var2{1.01f};
	var1 = var2;

	std::cout << *var1.get<float>() << "\n";
	std::cout << *var2.get<float>() << "\n";

	var1 = std::move(aw::variant<std::string, int>{"Test string!"s});

	auto f = var1.get<float>();
	auto s = var1.get<std::string>();
	auto i = var1.get<int>();

	std::cout << std::boolalpha;
	std::cout << "float:  " << bool(f) << "\n";
	std::cout << "string: " << bool(s) << "\n";
	std::cout << "int:    " << bool(i) << "\n";

	std::cout << *s << "\n";


	// aw::variant<> empty;
}
