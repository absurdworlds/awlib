/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/resource_manager.h>

#include <aw/test/test.h>

TestFile( "graphics::gl3 resource manager" );

namespace aw::gl3 {
namespace {
struct dummy {
	int value = 0;
};
} // namespace

Test(resource_ref_copy_of_empty_stays_empty) {
	resource_ref<dummy> empty;

	auto copy = empty;

	Checks {
		TestAssert( !empty.is_valid() );
		TestAssert( !copy.is_valid() );
	}
}

Test(resource_ref_assignment_of_empty_stays_empty) {
	resource_manager<dummy> mgr;
	auto idx = mgr.add_resource( "thing", dummy{} );

	auto ref = mgr[idx];
	ref = resource_ref<dummy>{};

	Checks {
		TestAssert( !ref.is_valid() );
	}
}

Test(resource_ref_to_a_freed_slot_stays_empty) {
	resource_manager<dummy> mgr;

	auto idx = mgr.add_resource( "thing", dummy{} );
	mgr.release( idx );

	auto freed = mgr[idx];
	auto copy  = freed;

	Checks {
		TestAssert( !freed.is_valid() );
		TestAssert( !copy.is_valid() );
	}
}

Test(resource_ref_keeps_the_slot_while_copies_live) {
	resource_manager<dummy> mgr;
	auto idx = mgr.add_resource( "thing", dummy{} );

	auto ref  = mgr[idx];
	auto copy = ref;

	mgr.release( idx );

	Checks {
		// two references outstanding, so the slot is not up for reuse
		TestAssert( mgr[idx].is_valid() );
	}
}
} // namespace aw::gl3
