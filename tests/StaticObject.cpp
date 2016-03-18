#include <iostream>
#include <aw/utility/StaticObject.h>

struct TestBefore {
	void print()
	{
		std::cout << "test_before\n";
	}
};

using GlobalTestBefore = aw::StaticObject<TestBefore>;

struct Test {
	void print()
	{
		GlobalTestBefore::instance().print();
		std::cout << "test\n";
	}
};

using GlobalTest = aw::StaticObject<Test>;

int main()
{
	GlobalTest::instance().print();
}

//
