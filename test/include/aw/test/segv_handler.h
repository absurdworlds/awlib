/*
 * Copyright (C) 2016  Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_test_segv_handler_h
#define aw_test_segv_handler_h

#include "registry.h"
#include "print.h"

namespace aw::test {

void context::segvhandler(int signum)
{
#if (AW_PLATFORM == AW_PLATFORM_POSIX)
	//file_context.test_failure();
	print(bold, red, "caught SIGSEGV, aborting tests", reset, '\n');
	signal(signum, SIG_DFL);
	kill(getpid(), signum);
#endif
}

} // namespace aw::test

#endif//aw_test_segv_handler_h
