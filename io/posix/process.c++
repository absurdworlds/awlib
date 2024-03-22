#include "aw/io/posix/process.h"

#include <aw/types/string_view.h>
#include <aw/algorithm/in.h>

#include <vector>

#include <cassert>

#include <sys/types.h>
#include <sys/wait.h>
#include <spawn.h>
#include <unistd.h>
#include <signal.h>

#ifdef __APPLE__
extern char** environ;
#endif

namespace aw::io::posix {
AW_IO_EXP
process_handle spawn(const char* path, aw::array_view<char*> argv, std::error_code& ec) noexcept
{
	/*! enforce `nullptr` at the end of `argv` */
	assert( argv.empty() || argv.back() == nullptr );

	pid_t pid;
	int rc = posix_spawnp(&pid, path, nullptr, nullptr, argv.data(), environ);
	if (rc == 2)
		rc = posix_spawn(&pid, path, nullptr, nullptr, argv.data(), environ);

	if (rc == 0)
		return process_handle( pid );

	ec.assign( rc, std::generic_category() );
	return invalid_process_handle;
}

AW_IO_EXP
process_handle spawn(aw::array_view<char*> argv, std::error_code& ec) noexcept
{
	return spawn( argv[0], argv, ec );
}

AW_IO_EXP
process_handle spawn(std::string path, aw::array_ref<std::string> argv, std::error_code& ec)
{
	std::vector<char*> args;
	args.push_back(path.data());
	for (std::string& arg : argv)
		args.push_back(arg.data());
	args.push_back(nullptr);

	return spawn(path.data(), args, ec);
}

AW_IO_EXP
int kill(process_handle pid, int signal, std::error_code& ec) noexcept
{
	// TODO: don't accept -1 or 0 as pid, add separate functions for that
	if( in( pid, process_handle(0), process_handle(-1) ) ) {
		ec = make_error_code( std::errc::invalid_argument );
		return -1;
	};

	auto ret = ::kill( pid_t(pid), signal);
	if (ret < 0)
		ec.assign( errno, std::generic_category() );
	return ret;
}

AW_IO_EXP wait_status wait(process_handle pid, std::error_code& ec) noexcept
{
	int status = 0;
	pid_t ret = waitpid( pid_t(pid), &status, 0);
	if (ret < 0) {
		ec.assign( errno, std::generic_category() );
		return wait_status::failed;
	}
	return wait_status::finished;
}
} // namespace aw::platform::posix
