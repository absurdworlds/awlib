#include <aw/log/scoped_log.h>
#include <aw/test/test.h>
#include "log_tester.h"

TestFile("scoped_log");

namespace aw {
Test(scoped_log_basic)
{
	log_tester log;
	scoped_log scoped;

	Setup {
		scoped.set_logger(&log);
		log.expect(log::info, "test", "enter {");
		log.expect(log::info, "test", "}");
	};

	scoped.enter_scope("test");
	scoped.exit_scope();
}

Test(scoped_log_nested)
{
	log_tester log;
	scoped_log scoped;

	Setup {
		scoped.set_logger(&log);
		log.expect(log::info, "outer", "enter {");
		log.expect(log::info, "inner", "  enter {");
		log.expect(log::info, "inner", "  }");
		log.expect(log::info, "outer", "}");
	};

	scoped.enter_scope("outer");
	scoped.enter_scope("inner");
	scoped.exit_scope();
	scoped.exit_scope();
}

Test(scoped_log_messages)
{
	log_tester log;
	scoped_log scoped;

	Setup {
		scoped.set_logger(&log);
		log.expect(log::info, "test", "enter {");
		log.expect(log::info, "test", "hello");
		log.expect(log::warning, "test", "warn");
		log.expect(log::error, "test", "err");
		log.expect(log::info, "test", "}");
	};

	scoped.enter_scope("test");
	scoped.info("test", "hello");
	scoped.warning("test", "warn");
	scoped.error("test", "err");
	scoped.exit_scope();
}

Test(scoped_log_indentation)
{
	log_tester log;
	scoped_log scoped;

	Setup {
		scoped.set_logger(&log);
		log.expect(log::info, "a", "enter {");
		log.expect(log::info, "b", "  enter {");
		log.expect(log::info, "b", "  }");
		log.expect(log::info, "a", "}");
	};

	scoped.enter_scope("a");
	scoped.enter_scope("b");
	scoped.exit_scope();
	scoped.exit_scope();
}

Test(scoped_log_scope_mismatch)
{
	log_tester log;
	scoped_log scoped;

	Setup {
		scoped.set_logger(&log);
		log.expect(log::info, "test", "enter {");
		log.expect(log::error, "aw::log", "scope mismatch");
	};

	scoped.enter_scope("test");
	scoped.exit_scope();
	scoped.exit_scope(); // One too many - should trigger error
}
} // namespace aw
