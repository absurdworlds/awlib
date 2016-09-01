#include <aw/types/containers/flat_map.h>
#include <iostream>
#include <string>

int main()
{
	using namespace std;
	aw::flat_map<string, int> map;

	map["abc"] = 10;
	map["abe"] = 20;

	std::cout << map["abc"] << "\n";
	std::cout << map["abe"] << "\n";
	std::cout << map["abf"] << "\n";

	std::cout << "--------------\n";

	map.insert(std::make_pair("bcd", 11));

	std::cout << map["abc"] << "\n";
	std::cout << map["abe"] << "\n";
	std::cout << map["abf"] << "\n";
	std::cout << map["bcd"] << "\n";

	std::cout << "--------------\n";

	aw::flat_map<string,int>::iterator it = map.find("ccc");
	if (it == map.end())
		std::cout << "notfund\n";
	else
		std::cout << "dounf: " << it->second << "\n";

	it = map.find("bcd");
	if (it == map.end())
		std::cout << "notfund\n";
	else
		std::cout << "found: " << it->second << "\n";

	std::cout << "--------------\n";

	for (auto const& s : map)
		std::cout << '{' << s.first << ':' << s.second << '}' << ", ";
	std::cout << "\n";
}
