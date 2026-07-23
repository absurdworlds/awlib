namespace aw::term::posix {

void show_cursor(bool show)
{
	printf(show?"\e[?25h":"\e[?25l");
}

// Enables xterm SGR mouse reporting: button-event tracking (1000) with
// extended SGR coordinate encoding (1006).
void enable_mouse(bool enable)
{
	printf(enable ? "\e[?1000h\e[?1006h" : "\e[?1000l\e[?1006l");
}

char read_char()
{
#if 0
	char c = 0;
	if (read(STDIN_FILENO, &c, 1) != 1) {
		journal.error("terminal", std::format("read() failed: {}", strerror(errno)));
	}
	return c;
#else
	return getchar();
#endif
}

} // namespace aw::term::posix
