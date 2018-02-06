#include <aw/types/tmpflag.h>
#include <aw/utility/test.h>
#include <thread>

TestFile( "aw::tmpflag" );

namespace aw {
Test(tmpflag) {
	using namespace std::chrono_literals;
	tmpflag f;
	Checks {
		TestAssert( !f );

		f.set( 10s );

		TestAssert( !!f );

		std::this_thread::sleep_for( 10s );

		TestAssert( !f );

		f.set( 5s );

		std::this_thread::sleep_for( 3s );

		TestAssert( f == true );

		f.reset();

		TestAssert( f == false );
	}
}
} // namespace aw
