#include <stdexcept>
#include <aw/test/test.h>

TestFile( "test fail", aw::test::negative );

Test(always_fail0) { Checks { TestAssert(1 == 2); } }
Test(always_fail1) { Checks { TestAssert(false); } }
Test(always_fail2) { Checks { TestEqual(1, 2); } }
Test(always_fail3) { Checks { TestEqualV(1, 2, 2); } }
Test(always_fail4) { Checks { TestEqualV(1, 2, 3); } }
Test(always_fail5) { Checks { throw "what is this"; } }
Test(always_fail6) { Checks { throw std::logic_error("you suck"); } }
Test(always_fail7) { Checks { TestCatch(std::logic_error, (void)0); } }
Test(always_fail8) { Checks { TestCatch(std::logic_error, throw 2); } }
Test(always_fail9) { Checks { TestCatch(std::logic_error, throw std::runtime_error{"a"}); } }
Test(always_faila) { Checks { TestEqual(1, 2); } }
Test(always_failb) { Checks { TestNEqual(1, 1); } }
Test(always_failc) { Checks { TestEqual(1, 2); } }
Test(always_faild) { Checks { TestEqual(1, 2); } }
Test(always_faile) { Checks { TestEqual(1, 2); } }
Test(always_failf) { Checks { TestEqual(1, 2); } }
