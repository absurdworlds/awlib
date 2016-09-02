#include <aw/types/containers/flat_map.h>
#include <iostream>
#include <string>

void separator()
{
	std::cout << "--------------\n";
}


template<typename K, typename V>
void print_pair(std::pair<K,V> const& s)
{
	std::cout << '{' << s.first << ':' << s.second << '}';
}

template<typename K, typename V, typename C, typename A>
void print_map(aw::flat_map<K,V,C,A> const& map)
{
	auto begin = std::begin(map);
	auto end   = std::end(map);

	std::cout << '{';
	if (begin != end) {
		print_pair(*begin++);
		while (begin != end) {
			std::cout << ", ";
			print_pair(*begin++);
		}
	}
	std::cout << '}';
}


void test_merge()
{
	separator();

	using namespace std;
	aw::flat_map<string, int> map1{{"aaa",0}, {"aac",2}, {"bac",5}, {"bcc",6}};
	aw::flat_map<string, int> map2{{"aab",1}, {"aad",3}, {"baa",4}, {"ccc",7}};

	map1.insert(begin(map2), end(map2));
	print_map(map1);
	std::cout << '\n';

	map1.insert(begin(map2), end(map2));
	print_map(map1);
	std::cout << '\n';

	aw::flat_map<string, int> map3{{"aba",8}, {"ada",9}, {"baa",0}, {"cac",10}};
	map1.insert(begin(map3), end(map3));
	print_map(map1);
	std::cout << '\n';
}

void test_assignment()
{
	separator();

	using namespace std;
	aw::flat_map<string, int> map1{{"aaa",0}, {"aac",2}, {"bac",5}, {"bcc",6}};
	aw::flat_map<string, int> map2{{"aab",1}, {"aad",3}, {"baa",4}, {"ccc",7}};

	map1 = map2;
	print_map(map1);
	std::cout << '\n';

	map1 = std::move(map2);
	print_map(map1);
	std::cout << '\n';
	print_map(map2);
	std::cout << '\n';

	map2 = {{"aba",1}, {"ada",2}, {"baa",3}, {"cac",4}};
	print_map(map2);
	std::cout << '\n';
}

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

	print_map(map);
	std::cout << '\n';

	std::cout << "--------------\n";

	map.erase("abe");

	print_map(map);
	std::cout << '\n';

	test_merge();
	test_assignment();
}
