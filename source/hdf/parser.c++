/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/fileformat/hdf/parser.h>

#include <cassert>
#include <cstdio>

#include <aw/algorithm/in.h>
#include <aw/types/string_view.h>
#include <aw/fileformat/hdf/type.h>

namespace aw {
namespace hdf {
inline namespace v1 {
object parser::read()
{
	using namespace std::string_literals;
	token tok = lex.get_token();

	switch (tok.kind) {
	case token::eof:
		return {};
	case token::bang:
		if (depth > 0) {
			lex.error("Unexpected ! inside node.", tok.pos);
			break;
		}
		processCommand();
		break;
	case token::node_begin:
		++depth;
		return {object::node, tok.value};
	case token::node_end:
		if (depth == 0) {
			lex.error("Unexpected ']'.", tok.pos);
			break;
		}
		--depth;
		return {object::end};
	case token::name:
		if (auto&& value = read_value())
			return {object::value, tok.value, std::move(value)};
		break;
	case token::invalid:
		lex.error("illegal token: \""s + tok.value + "\"", tok.pos);
		break;
	default:
		lex.error("unexpected token: \""s + tok.value + "\"", tok.pos);
	}

	return read();
}

void parser::skip_node()
{
	token tok = lex.peek_token();

	size_t depth = 1;
	do {
		if (tok.kind == token::node_begin) {
			++depth;
		} else if (tok.kind == token::node_end) {
			--depth;
		}
		tok = lex.get_token();
	} while (depth > 0);
}

value parser::read_value()
{
	token tok = lex.get_token();
	if (tok.kind != token::equals) {
		lex.error("Expected '=', got " + tok.value, tok.pos);
		return {};
	}

	token id = lex.get_token();
	if (id.kind == token::vec_begin)
		return deduce_vector(id.pos);

	tok = lex.peek_token();
	if (tok.kind != token::colon)
		return deduce_value(id);

	tok = lex.next_token(); // skip ':'
	if (tok.kind == token::vec_begin)
		return parse_vector(id);
	return parse_value(id);
}

hdf::Type parse_type(string_view token)
{
	if (token == "bool" || token == "b")
		return Type::Boolean;
	if (token == "int" || token == "i")
		return Type::Integer;
	if (token == "float" || token == "f")
		return Type::Float;
	if (token == "string" || token == "s")
		return Type::String;
	return Type::Unknown;
}

template<>
value parser::parse_value<std::string>()
{
	auto tok = lex.get_token();
	if (!in(tok.kind, tok.string, tok.name, tok.number)) {
		lex.error("Invalid string token", tok.pos);
		return {};
	}
	return value{tok.value};
}

template<>
value parser::parse_value<double>()
{
	auto tok = lex.get_token();
	if (tok.kind != token::number) {
		lex.error("Expected number", tok.pos);
		return {};
	}
	return value{std::stod(tok.value)};
}

template<>
value parser::parse_value<intmax_t>()
{
	auto tok = lex.get_token();
	if (tok.kind != token::number) {
		lex.error("Expected number", tok.pos);
		return {};
	}
	return value{std::stoll(tok.value)};
}

template<>
value parser::parse_value<bool>()
{
	auto tok = lex.get_token();
	if (in(tok.value, "true", "1"))
		return value{true};
	if (in(tok.value, "false", "0"))
		return value{false};
	lex.error("Invalid bool token: " + tok.value, tok.pos);
	return {};
}

value parser::parse_value(token id)
{
	auto type = parse_type(id.value);

	switch (type) {
	case Type::String:
		return parse_value<std::string>();
	case Type::Float:
		return parse_value<double>();
	case Type::Integer:
		return parse_value<intmax_t>();
	case Type::Boolean:
		return parse_value<bool>();
	default:
		lex.error("Invalid type", id.pos);
	}
	return {};
}

value parser::deduce_value(token tok)
{
	switch (tok.kind) {
	case token::number:
		if (tok.value.find('.') == std::string::npos)
			return value{std::stoll(tok.value)};
		return value{std::stod(tok.value)};
	case token::name:
		if (tok.value == "true")
			return value{true};
		if (tok.value == "false")
			return value{false};
	case token::string:
		return value{tok.value};
	default:
		lex.error("Invalid token", tok.pos);
	}
	return {};
}

void parser::skip_vector()
{
	auto tok = lex.get_token();
	while (tok.kind != token::vec_end) {
		tok = lex.get_token();
		if (tok.kind == token::eof) {
			lex.error("Reached end of file searching for '}'", tok.pos);
			break;
		}
	}
}

template<typename T>
std::vector<T> parser::parse_vector(token::position beg)
{
	auto tok = lex.peek_token();
	std::vector<T> temp;
	while (tok.kind != tok.eof) {
		value val = parse_value<T>();
		if (val.empty()) {
			skip_vector();
			return temp;
		}
		temp.push_back(*val.get<T>());

		auto tok = lex.get_token();
		if (tok.kind == token::vec_end)
			break;
		if (tok.kind != token::comma) {
			lex.error("Expected ','", tok.pos);
			skip_vector();
			return temp;
		}
	}

	if (tok.kind == token::eof)
		lex.error("Unmatched '{'", beg);

	return temp;
}

value parser::parse_vector(token id)
{
	auto type = parse_type(id.value);
	auto tok = lex.get_token();
	switch (type) {
	case Type::String:
		return value{parse_vector<std::string>(tok.pos)};
	case Type::Integer:
		return value{parse_vector<intmax_t>(tok.pos)};
	case Type::Float:
		return value{parse_vector<double>(tok.pos)};
	case Type::Boolean:
		return value{parse_vector<bool>(tok.pos)};
	default:
		lex.error("Invalid type", id.pos);
	}
	skip_vector();
	return {};
}

value parser::deduce_vector(token::position beg)
{
	auto tok = lex.peek_token();
	switch (tok.kind) {
	case token::name:
		if (in(tok.value, "true", "false"))
			return value{parse_vector<bool>(beg)};
	case token::string:
		return value{parse_vector<std::string>(beg)};
	case token::number:
		if (tok.value.find('.') == std::string::npos)
			return value{parse_vector<intmax_t>(beg)};
		return value{parse_vector<double>(beg)};
	case token::vec_end:
		lex.warning("Empty vector", tok.pos);
		break;
	default:
		lex.error("Invalid token", tok.pos);
	}
	skip_vector();
	return {};
}


// TODO: rewrite
void parser::processCommand() {
	token tok = lex.get_token();

	if (tok.kind != token::name) {
		lex.error("Unexpected token:" + tok.value, tok.pos);
		return;
	}

	if (tok.value == "hdf_version") {
		tok = lex.get_token();

		if (tok.kind != token::string) {
			lex.error("Expected string after \"hdf_version\".", tok.pos);
			return;
		}

		std::string ver = tok.value.substr(0,3);
		if (ver == "1.2") {
			lex.message("HDF version: 1.2", tok.pos);
		} else if (ver == "1.1") {
			lex.error("Version 1.1 is not supported.", tok.pos);
			return;
		} else if (ver == "1.0") {
			lex.error("Version 1.0 is not supported.", tok.pos);
			return;
		} else {
			lex.error("hdf_version: invalid version: " +
			               tok.value + ".", tok.pos);
			return;
		}
	}

	if (tok.value == "strict") {
		lex.error("Strict mode: not implemented", tok.pos);

		tok = lex.get_token();

		if (tok.kind != token::name && tok.kind != token::number) {
			lex.error("Expected true/false value.", tok.pos);
			return;
		}

		auto val = parse_value<bool>();
	}
}
} // inline namespace v1
} // namespace hdf
} // namespace aw
