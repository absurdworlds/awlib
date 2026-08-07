#include <aw/types/containers/flat_map.h>

#include <aw/utility/to_string/pair.h>
#include <aw/test/test.h>

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
		map.insert(std::pair{"bcd", 11});

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

Test(flat_map_merge_custom_compare) {
	using map_type = aw::flat_map<std::string, int, std::greater<std::string>>;

	map_type map{ {"ddd",4}, {"bbb",2} };
	map_type const expected{
		{"aaa",1}, {"bbb",2}, {"ccc",3}, {"ddd",4}, {"eee",5}
	};

	std::vector<std::pair<std::string, int>> const range{
		{"aaa",1}, {"ccc",3}, {"eee",5}
	};

	Preconditions {
		TestAssert(std::is_sorted(begin(map), end(map), map.value_comp()));
	}

	Checks {
		map.insert(begin(range), end(range));

		TestAssert(std::is_sorted(begin(map), end(map), map.value_comp()));
		TestEqual(map, expected);
	}

	Checks {
		TestEqual(map.size(), 5u);
		TestEqual(map.find("aaa")->second, 1);
		TestEqual(map.find("bbb")->second, 2);
		TestEqual(map.find("ccc")->second, 3);
		TestEqual(map.find("ddd")->second, 4);
		TestEqual(map.find("eee")->second, 5);
	}
}

Test(flat_map_range_constructor) {
	std::vector<std::pair<std::string, int>> const range{
		{"bcc",6}, {"aaa",0}, {"bac",5}, {"aac",2}, {"aab",1}
	};
	aw::flat_map<std::string, int> const expected{
		{"aaa",0}, {"aab",1}, {"aac",2}, {"bac",5}, {"bcc",6}
	};

	Checks {
		aw::flat_map<std::string, int> map(begin(range), end(range));

		TestEqual(map, expected);
		TestAssert(std::is_sorted(begin(map), end(map), map.value_comp()));
	}

	Checks {
		// the range constructor must honour a custom comparator
		using map_type = aw::flat_map<std::string, int, std::greater<std::string>>;
		map_type map(begin(range), end(range), std::greater<std::string>{});

		TestAssert(std::is_sorted(begin(map), end(map), map.value_comp()));
		TestEqual(map.size(), 5u);
		TestEqual(begin(map)->first, "bcc");
		TestEqual(map.find("aaa")->second, 0);
		TestEqual(map.find("bac")->second, 5);
	}

	Checks {
		// duplicate keys are collapsed; which one survives is unspecified,
		// so only check that the map is deduplicated and still searchable
		std::vector<std::pair<std::string, int>> const dupes{
			{"aab",1}, {"aaa",0}, {"aab",9}, {"aaa",8}, {"aac",2}
		};
		aw::flat_map<std::string, int> map(begin(dupes), end(dupes));

		TestEqual(map.size(), 3u);
		TestAssert(std::is_sorted(begin(map), end(map), map.value_comp()));
		TestAssert(map.find("aaa") != map.end());
		TestAssert(map.find("aab") != map.end());
		TestAssert(map.find("aac") != map.end());
	}

	Checks {
		aw::flat_map<std::string, int> map(begin(range), begin(range));
		TestAssert(map.empty());
	}
}

Test(flat_map_insert_or_assign) {
	aw::flat_map<std::string, int> map{
		{"aaa",0}, {"bbb",1}, {"ccc",2}
	};

	Checks {
		// assigning over an existing key must overwrite, not insert
		auto [pos, inserted] = map.insert_or_assign("bbb", 20);

		TestAssert(!inserted);
		TestEqual(pos->first, "bbb");
		TestEqual(pos->second, 20);
		TestEqual(map.size(), 3u);
		TestEqual(map.find("bbb")->second, 20);
	}

	Checks {
		// a new key smaller than everything goes to the front
		auto [pos, inserted] = map.insert_or_assign("aa", 30);

		TestAssert(inserted);
		TestEqual(pos->second, 30);
		TestAssert(pos == begin(map));
		TestEqual(map.size(), 4u);
	}

	Checks {
		// a new key in the middle
		auto [pos, inserted] = map.insert_or_assign("bcc", 40);

		TestAssert(inserted);
		TestEqual(pos->second, 40);
		TestEqual(map.size(), 5u);
	}

	Checks {
		// a new key greater than everything goes to the back
		auto [pos, inserted] = map.insert_or_assign("zzz", 50);

		TestAssert(inserted);
		TestEqual(pos->second, 50);
		TestAssert(pos == end(map) - 1);
		TestEqual(map.size(), 6u);
	}

	Checks {
		TestAssert(std::is_sorted(begin(map), end(map), map.value_comp()));
		TestEqual(map.find("aa")->second, 30);
		TestEqual(map.find("aaa")->second, 0);
		TestEqual(map.find("bbb")->second, 20);
		TestEqual(map.find("bcc")->second, 40);
		TestEqual(map.find("ccc")->second, 2);
		TestEqual(map.find("zzz")->second, 50);
	}

	Checks {
		// insert_or_assign on an empty map
		aw::flat_map<std::string, int> empty;
		auto [pos, inserted] = empty.insert_or_assign("aaa", 1);

		TestAssert(inserted);
		TestEqual(empty.size(), 1u);
		TestEqual(pos->second, 1);
	}

	Checks {
		// the mapped value is forwarded, so a move-only mapped type works
		aw::flat_map<std::string, std::string> smap;
		smap.insert_or_assign("k", std::string{"first"});
		auto [pos, inserted] = smap.insert_or_assign("k", std::string{"second"});

		TestAssert(!inserted);
		TestEqual(pos->second, "second");
		TestEqual(smap.size(), 1u);
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
