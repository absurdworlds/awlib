#include "new_pool.h"
#include <iostream>
int main()
{
	using namespace aw::memory;

	pool<sizeof(std::string), alignof(std::string)> p(3);


	auto mem1 = p.alloc();
	std::cout << mem1 << "\n";
	auto mem2 = p.alloc();
	std::cout << mem2 << "\n";
	auto mem3 = p.alloc();
	std::cout << mem3 << "\n";

	std::cout << "" << "\n";

	p.dealloc(mem2);
	p.dealloc(mem3);

	mem2 = p.alloc();
	std::cout << mem2 << "\n";
	mem3 = p.alloc();
	std::cout << mem3 << "\n";
	auto mem4 = p.alloc();
	std::cout << mem4 << "\n";

	std::cout << "" << "\n";

	p.dealloc(mem1);
	p.dealloc(mem4);

	mem1 = p.alloc();
	std::cout << mem1 << "\n";
	mem4 = p.alloc();
	std::cout << mem4 << "\n";

	std::cout << "" << "\n";

	p.dealloc(mem2);
	p.dealloc(mem1);

	mem1 = p.alloc();
	mem2 = p.alloc();

	auto mem5 = p.alloc();
	std::cout << mem5 << "\n";

	p.dealloc(mem1);
	p.dealloc(mem2);
	p.dealloc(mem3);
	p.dealloc(mem4);
	p.dealloc(mem5);
}
