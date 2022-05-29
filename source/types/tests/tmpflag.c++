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

		f.set( 500ms );

		TestAssert( !!f );

		std::this_thread::sleep_for( 500ms );

		TestAssert( !f );

		f.set( 250ms );

		TestAssert( !!f );

		std::this_thread::sleep_for( 200ms );

		TestAssert( f == true );

		f.reset();

		TestAssert( f == false );
	}
}
} // namespace aw
