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
bool Parser::read(Object& object)
{
	using namespace std::string_literals;
	token tok = lex.getToken();

	switch (tok.kind) {
	case token::eof:
		object = {};
		return false;
	case token::bang:
		if (depth > 0) {
			lex.error("Unexpected ! inside node.", tok.pos);
			break;
		}
		processCommand();
		break;
	case token::node_begin:
		++depth;
		object = Object{Object::Node, tok.value};
		return true;
	case token::node_end:
		if (depth == 0) {
			lex.error("Unexpected ']'.", tok.pos);
			break;
		}
		--depth;
		object = Object{Object::NodeEnd};
		return true;
	case token::name:
		if (auto&& value = read_value()) {
			object = Object{Object::Value, tok.value, std::move(value)};
			return true;
		}
		break;
	case token::invalid:
		lex.error("illegal token: \""s + tok.value + "\"", tok.pos);
		break;
	default:
		lex.error("unexpected token: \""s + tok.value + "\"", tok.pos);
	}

	return read(object);
}

void Parser::skip_node()
{
	token tok = lex.peekToken();

	size_t depth = 1;
	do {
		if (tok.kind == token::node_begin) {
			++depth;
		} else if (tok.kind == token::node_end) {
			--depth;
		}
		tok = lex.getToken();
	} while (depth > 0);
}

Value Parser::read_value()
{
	token tok = lex.getToken();
	if (tok.kind != token::equals) {
		lex.error("Expected '=', got " + tok.value, tok.pos);
		return {};
	}

	token id = lex.getToken();
	if (id.kind == token::vec_begin)
		return deduce_vector(id.pos);

	tok = lex.peekToken();
	if (tok.kind != token::colon)
		return deduce_value(id);

	tok = lex.nextToken(); // skip ':'
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
Value Parser::parse_value<std::string>()
{
	auto tok = lex.getToken();
	if (!in(tok.kind, tok.string, tok.name, tok.number)) {
		lex.error("Invalid string token", tok.pos);
		return {};
	}
	return Value{tok.value};
}

template<>
Value Parser::parse_value<double>()
{
	auto tok = lex.getToken();
	if (tok.kind != token::number) {
		lex.error("Expected number", tok.pos);
		return {};
	}
	return Value{std::stod(tok.value)};
}

template<>
Value Parser::parse_value<intmax_t>()
{
	auto tok = lex.getToken();
	if (tok.kind != token::number) {
		lex.error("Expected number", tok.pos);
		return {};
	}
	return Value{std::stoll(tok.value)};
}

template<>
Value Parser::parse_value<bool>()
{
	auto tok = lex.getToken();
	if (in(tok.value, "true", "1"))
		return Value{true};
	if (in(tok.value, "false", "0"))
		return Value{false};
	lex.error("Invalid bool token: " + tok.value, tok.pos);
	return {};
}

Value Parser::parse_value(token id)
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

Value Parser::deduce_value(token tok)
{
	switch (tok.kind) {
	case token::number:
		if (tok.value.find('.') == std::string::npos)
			return Value{std::stoll(tok.value)};
		return Value{std::stod(tok.value)};
	case token::name:
		if (tok.value == "true")
			return Value{true};
		if (tok.value == "false")
			return Value{false};
	case token::string:
		return Value{tok.value};
	default:
		lex.error("Invalid token", tok.pos);
	}
	return {};
}

void Parser::skip_vector()
{
	auto tok = lex.getToken();
	while (tok.kind != token::vec_end) {
		tok = lex.getToken();
		if (tok.kind == token::eof) {
			lex.error("Reached end of file searching for '}'", tok.pos);
			break;
		}
	}
}

template<typename T>
std::vector<T> Parser::parse_vector(token::position beg)
{
	auto tok = lex.peekToken();
	std::vector<T> temp;
	while (tok.kind != tok.eof) {
		Value val = parse_value<T>();
		if (val.empty()) {
			skip_vector();
			return temp;
		}
		temp.push_back(*val.get<T>());

		auto tok = lex.getToken();
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

Value Parser::parse_vector(token id)
{
	auto type = parse_type(id.value);
	auto tok = lex.getToken();
	switch (type) {
	case Type::String:
		return Value{parse_vector<std::string>(tok.pos)};
	case Type::Integer:
		return Value{parse_vector<intmax_t>(tok.pos)};
	case Type::Float:
		return Value{parse_vector<double>(tok.pos)};
	case Type::Boolean:
		lex.error("Boolean vector is not supported", id.pos);
		break;
	default:
		lex.error("Invalid type", id.pos);
	}
	skip_vector();
	return {};
}

Value Parser::deduce_vector(token::position beg)
{
	auto tok = lex.peekToken();
	switch (tok.kind) {
	case token::name:
	case token::string:
		return Value{parse_vector<std::string>(beg)};
	case token::number:
		if (tok.value.find('.') == std::string::npos)
			return Value{parse_vector<intmax_t>(beg)};
		return Value{parse_vector<double>(beg)};
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
void Parser::processCommand() {
	token tok = lex.getToken();

	if (tok.kind != token::name) {
		lex.error("Unexpected token:" + tok.value, tok.pos);
		return;
	}

	if (tok.value == "hdf_version") {
		tok = lex.getToken();

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

		tok = lex.getToken();

		if (tok.kind != token::name && tok.kind != token::number) {
			lex.error("Expected true/false value.", tok.pos);
			return;
		}

		auto val = parse_value<bool>();
	}
}
} // namespace hdf
} // namespace aw
