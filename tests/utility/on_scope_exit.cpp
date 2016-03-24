#include <aw/utility/on_scope_exit.h>
#include <iostream>

int main()
{
	int x = 100;
	auto on_exit1 = aw::call_on_exit([&] {x = 0;});
	{
		decltype(on_exit1) on_exit2(std::move(on_exit1));

		std::cout << x << "\n";
	}
	std::cout << x << "\n";
}
