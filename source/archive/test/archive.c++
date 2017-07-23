#include <aw/utility/to_string/tuple.h>
#include "test_archive.h"
#include <aw/utility/test.h>
#include <aw/utility/index_sequence.h>
#include <aw/utility/to_string/pair.h>
#include <aw/archive/types/std/tuple.h>
#include <aw/archive/types/std/vector.h>
#include <aw/archive/types/std/map.h>

TestFile("archive");

namespace aw {
namespace arc {
Test(saveload) {
	testarc arc;
	using test = std::tuple<int, bool, std::string>;
	test proto{
		11, true, "test str"
	};

	test a{proto};
	test b;

	std::vector<int> vec1{11, 18, 45, 99};
	std::vector<int> vec2;

	std::map<int,int> map1{{1,2}, {2,4}, {3,6}};
	std::map<int,int> map2;

	Setup {
		arc.archive(a);
		arc.unarchive(b);

		arc.clear();

		arc.archive(vec1);
		arc.unarchive(vec2);

		arc.archive(map1);
		arc.unarchive(map2);
	}

	Checks {
		TestEqual(a, b);
		TestEqual(vec1, vec2);
		TestEqual(map1, map2);
	}
}


using namespace std::string_view_literals;

struct Base {
	aw_register_class( Base );
	using create_parameters = meta::list<>;

	Base() = default;
	Base(int i) : i{i} {}

	virtual ~Base() = default;

	int i = 11;
};

template<typename Archive>
void save(Archive& arc, Base const& base)
{
	arc(base.i);
}

template<typename Archive>
void load(Archive& arc, Base& base)
{
	arc( base.i);
}


struct Derived : Base {
	aw_register_class( Derived );


	Derived() = default;
	Derived(int i, float f) : Base{i}, f{f} {}

	float f = 1.5;

};

template<typename Archive>
void save(Archive& arc, Derived const& value)
{
	save(arc, (Base const&) value);
	arc(value.f);
}

template<typename Archive>
void load(Archive& arc, Derived& value)
{
	load(arc, (Base&) value);
	arc(value.f);
}

Test(polymorphic) {
	Base* a = new Derived{15, 37.1};

	testarc arc;
	arc.archive(a);
	Base* b = nullptr;
	arc.unarchive(b);

	TestAssert(b != nullptr);
	TestEqual(a->i, b->i);
	TestEqual(((Derived*)a)->f, ((Derived*)b)->f);
}

} // namespace arc
} // namespace aw

RunTests();
