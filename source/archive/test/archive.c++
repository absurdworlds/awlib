#include "test_archive.h"
#include <aw/utility/test.h>
#include <aw/utility/index_sequence.h>
#include <aw/utility/to_string/tuple.h>
#include <aw/archive/types/std/tuple.h>

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
	arc.archive("", a);
	test b;
	arc.unarchive("", b);

	TestEqual(a, b);
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
	arc.archive("i", base.i);
}

template<typename Archive>
void load(Archive& arc, Base& base)
{
	arc.unarchive("i", base.i);
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
	arc.archive("f", value.f);
}

template<typename Archive>
void load(Archive& arc, Derived& value)
{
	load(arc, (Base&) value);
	arc.unarchive("f", value.f);
}

Test(polymorphic) {
	Base* a = new Derived{15, 37.1};

	testarc arc;
	arc.archive("a", a);
	Base* b = nullptr;
	arc.unarchive("a", b);

	TestAssert(b != nullptr);
	TestEqual(a->i, b->i);
	TestEqual(((Derived*)a)->f, ((Derived*)b)->f);
}

} // namespace arc
} // namespace aw

RunTests();
