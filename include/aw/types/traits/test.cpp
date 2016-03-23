#include "basic_traits.h"
#include <iostream>
#include <vector>


int main()
{
	std::cout << aw::IsContainer<int> << "\n";
	std::cout << aw::IsContainer<std::string> << "\n";
	std::cout << aw::IsContainer<std::vector<int>> << "\n";
}
