/*
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/graphics/gl/command_list.h>
#include <aw/graphics/gl/render_context.h>

#include <aw/test/test.h>

#include <vector>

TestFile( "graphics::gl3 command list" );

namespace aw::gl3 {
namespace {
std::vector<int> order;

//! Records that it ran, so a stored command can be told apart from a lost one
struct append_command {
	int id;

	void operator()(render_context&) { order.push_back(id); }
};
} // namespace

Test(command_storage_copy_runs_the_same_command) {
	order.clear();

	command_storage original{ append_command{7} };
	command_storage copy{ original };

	render_context ctx{};
	copy( ctx );

	Checks {
		TestEqual( order.size(), size_t(1) );

		if (order.size() == 1)
			TestEqual( order[0], 7 );
	}
}

Test(command_list_runs_commands_in_the_order_they_were_added) {
	order.clear();

	command_list list;
	list.add( append_command{1} );
	list.add( append_command{2} );
	list.add( append_command{3} );

	render_context ctx{};
	list.render( ctx );

	Preconditions {
		TestEqual( order.size(), size_t(3) );
	}

	Checks {
		TestEqual( order[0], 1 );
		TestEqual( order[1], 2 );
		TestEqual( order[2], 3 );
	}
}
} // namespace aw::gl3
