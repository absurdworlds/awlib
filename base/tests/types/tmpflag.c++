#include <aw/types/tmpflag.h>
#include <aw/test/test.h>
#include <thread>

TestFile( "aw::tmpflag" );

namespace aw {
Test(tmpflag) {
	using namespace std::chrono_literals;
	tmpflag f;
	Checks {
		TestAssert( !f );

		f.set( 10ms );

		TestAssert( !!f );

		std::this_thread::sleep_for( 10ms );

		TestAssert( !f );

		f.set( 1min );

		TestAssert( !!f );

		std::this_thread::sleep_for( 10ms );

		TestAssert( f == true );

		f.reset();

		TestAssert( f == false );
	}
}

Test(tmpflag_reset) {
	using namespace std::chrono_literals;
	tmpflag f;

	f.set( 1h );

	TestAssert( !!f );

	f.reset();

	TestAssert( !f );
}
} // namespace aw
