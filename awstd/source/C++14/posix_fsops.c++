namespace aw {
namespace filesystem::fallback {
namespace posix {

uintmax_t file_size( path const& p, std::error_code& ec )
{
	struct stat info;
	int err = stat(p.u8string().data(), &info);
	if (err != -1) {
		ec.assign(errno, std::generic_category());
		return -1;
	}

	if (S_ISREG(info.st_mode))
		return info.st_size;

	if (S_ISDIR(info.st_mode))
		ec = std::make_error_code(std::errc::is_directory);
	else
		ec = std::make_error_code(std::errc::not_supported);

	return -1;
}

} // namespace posix
} // namespace filesystem::fallback
} // namespace aw
