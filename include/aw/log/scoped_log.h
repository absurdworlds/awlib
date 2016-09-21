/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_scoped_log_h
#define aw_log_scoped_log_h
#include <vector>
#include <aw/log/log_provider.h>
namespace aw {
inline namespace v1 {
/*!
 * Adds scope functionality to log_provider
 */
struct scoped_log : log_provider {
	/*!
	 * \{
	 * \see log::message()
	 */
	void message(log::level lvl, std::string const& src, std::string const& msg)
	{
		log_provider::message(lvl, src, indent + msg);
	}

	void info(std::string const& src, std::string const& msg)
	{
		message(log::info, src, msg);
	}

	void warning(std::string const& src, std::string const& msg)
	{
		message(log::warning, src, msg);
	}

	void error(std::string const& src, std::string const& msg)
	{
		message(log::error, src, msg);
	}

	void fatal(std::string const& src, std::string const& msg)
	{
		message(log::critical, src, msg);
	}

	/*! \} */

	void enter_scope(char const* src)
	{
		if (disable_logger) return;
		info(src, "enter {");
		scope_stack.push_back(src);
		indent.resize(scope_stack.size()*2, ' ');
	}

	void exit_scope()
	{
		if (disable_logger) return;
		if (scopes.empty()) {
			error("aw::log", "scope mismatch");
			return;
		}
		char const* scope = scope_stack.back();
		scope_stack.pop_back();

		indent.resize(scope_stack.size()*2, ' ');
		info(src, "}");
	}
private:
	/* TODO: replace by string_view */
	std::vector<char const*> scope_stack;
	std::string indent;
};
} // namespace log
} // namespace aw
#endif//aw_log_log_provider_h
