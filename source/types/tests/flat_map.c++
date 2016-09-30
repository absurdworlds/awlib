#include <aw/types/containers/flat_map.h>

#include <aw/utility/to_string/pair.h>
#include <aw/utility/test.h>

// TODO: test exception-safety

TestFile( "aw::flat_map" );

namespace aw {
Test(flat_map_basic)
{
	aw::flat_map<std::string, int> map;
	Checks {
		map["abc"] = 10;
		map["abe"] = 20;

		TestEqual(map["abc"], 10);
		TestEqual(map["abe"], 20);
		TestEqual(map["abf"], 0);
	}

	Checks {
		map.insert(std::make_pair("bcd", 11));

		TestEqual(map["abc"], 10);
		TestEqual(map["abe"], 20);
		TestEqual(map["abf"], 0);
		TestEqual(map["bcd"], 11);
	}

	Checks {
		map.erase("abe");
		TestEqual(map["abe"], 0);
	}
}

Test(flat_map_find) {
	aw::flat_map<std::string, int> map{
		{"abc",10}, {"abe",20}, {"abf",0}, {"bcd",11}
	};

	Checks {
		TestAssert(map.find("abd") == map.end());
		TestAssert(map.find("ccc") == map.end());
		TestAssert(map.find("bcd")->second == 11);
	}

	Checks {
		TestAssert(map.find("abe") != map.end());
		map.erase("abe");
		TestAssert(map.find("abe") == map.end());
	}
}

Test(flat_map_merge) {
	aw::flat_map<std::string, int> map1{
		{"aaa",0}, {"aab",1}, {"aac",2}, {"bac",5}, {"bcc",6}
	};
	aw::flat_map<std::string, int> map2{
		{"aab",6}, {"aad",3}, {"baa",4}, {"bac",4}, {"ccc",7}
	};
	aw::flat_map<std::string, int> const expected{
		{"aaa",0}, {"aab",1}, {"aac",2}, {"aad",3},
		{"baa",4}, {"bac",5}, {"bcc",6}, {"ccc",7}
	};

	Checks {
		auto tmp = map1;
		map1.insert(begin(map2), end(map2));
		TestEqual(map1, expected);
	}

	Checks {
		auto tmp = map1;
		map1.insert(begin(map2), end(map2));
		TestEqual(map1, tmp);
	}
}

Test(flat_map_assignment) {

	aw::flat_map<std::string, int> map{
		{"aaa",0}, {"aac",2}, {"bac",5}, {"bcc",6}
	};
	aw::flat_map<std::string, int> map1{
		{"aaa",0}, {"aac",2}, {"bac",5}, {"bcc",6}
	};
	aw::flat_map<std::string, int> map2{
		{"aab",1}, {"aad",3}, {"baa",4}, {"ccc",7}
	};

	Preconditions {
		TestEqual(map, map1);
	}

	Checks {
		map = map2;
		TestEqual(map, map2);
	}

	Setup {
		map.clear();
		TestAssert(map.empty());
	}

	Checks {
		auto tmp = map2;
		map = std::move(tmp);
		TestEqual(map, map2);
		TestAssert(tmp.empty());
	}

	Checks {
		map = {{"aba",1}, {"ada",2}, {"baa",3}, {"cac",4}};
		TestAssert(map.size() == 4);
		TestEqual(map.find("aba")->second, 1);
		TestEqual(map.find("ada")->second, 2);
		TestEqual(map.find("baa")->second, 3);
		TestEqual(map.find("cac")->second, 4);
	}
}
} // namespace aw
