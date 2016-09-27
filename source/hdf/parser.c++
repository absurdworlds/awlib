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
#include <aw/utility/string_view.h>
#include <aw/utility/string/compose.h>
#include <aw/fileformat/hdf/type.h>

namespace aw {
namespace hdf {
hdf::Type tokenToType(token const& token)
{
	if (token.value == "bool" || token.value == "b") {
		return Type::Boolean;
	} else if (token.value == "int" || token.value == "i") {
		return Type::Integer;
	} else if (token.value == "float" || token.value == "f") {
		return Type::Float;
	} else if (token.value == "vec3" || token.value == "v3") {
		return Type::Vector3d;
	} else if (token.value == "vec2" || token.value == "v2") {
		return Type::Vector2d;
	} else if (token.value == "string" || token.value == "s") {
		return Type::String;
	} else {
		return Type::Unknown;
	}
}

bool parseBoolean(std::string const& str)
{
	bool val;

	if (str == "true" || str == "1") {
		val = true;
	} else if (str == "false" || str == "0") {
		val = false;
	}

	return val;
}

Value parseInteger(std::string const& str)
{
	auto type = Type::Integer;
	for (char c : str) {
		if (c == '.') {
			type = Type::Float;
		}
	}

	if (type == Type::Integer)
		return Value(i64(stoll(str)));
	else
		return Value(f64(stod(str)));
}

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
		if (depth == 0) {
			lex.error("Value must be inside node.", tok.pos);
			break;
		}
		object = Object{Object::Value, tok.value, read_value()};
		return true;
	case token::invalid:
		lex.error("read(): illegal token: %0"s + tok.value, tok.pos);
		break;
	default:
		lex.error("read(): unexpected token: %0"s + tok.value, tok.pos);
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
		lex.error(string::compose("Expected '=', got %0", tok.value), tok.pos);
		return {};
	}

	token id = lex.getToken();
	tok = lex.peekToken();

	bool hasType = tok.kind == token::colon;
	if (hasType) {
		tok = lex.getToken();
		var = convertValue(tokenToType(id));
	} else {
		var = convertValue(id);
	}

	state = State::Idle;
}


Value Parser::convertValue(Type type)
{
	token tok = lex.getToken();

	switch (type) {
	case Type::Enum:
	case Type::String:
		if (!(tok.kind == token::string || tok.kind == token::name))
			break;

		return Value(tok.value);
	case Type::Float:
		if (tok.kind != token::number)
			break;

		return Value(std::stod(tok.value));
	case Type::Integer:
		if (tok.kind != token::number)
			break;

		return Value(i64(std::stoll(tok.value)));
	case Type::Boolean:
		if (tok.kind != token::name)
			break;

		return Value(parseBoolean(tok.value));
	case Type::Vector2d:
	case Type::Vector3d:
	case Type::Vector4d:
		return parseVector(type);
	}

	return Value();
}

Value Parser::convertValue(token tok)
{
	switch (tok.kind) {
	case token::string:
		return Value(tok.value);
	case token::number:
		return parseInteger(tok.value);
	case token::name:
		if (tok.value == "true" || tok.value == "false")
			return Value(bool(parseBoolean(tok.value)));
		return Value(tok.value);
	case token::vec_begin:
		return parseVector();
	}

	return Value();
}

Value Parser::parseVector(Type type)
{
	token tok = lex.peekToken();

	if (tok.kind != token::vec_begin)
		return Value();

	Value tmp = parseVector();

	if (tmp.getType() != type)
		return Value();

	return tmp;
}

Value Parser::parseVector()
{
	token tok = lex.peekToken();

	// Damn it, why is it so messy …
	std::array<f32, 4> vec;
	auto it = vec.begin();

	while (tok.kind != token::eof) {
		tok = lex.getToken();
		if (tok.kind != token::number)
			return Value();

		if (it < vec.end())
			*(it++) = stof(tok.value);

		tok = lex.getToken();
		
		if (tok.kind == token::vec_end)
			break;

		if (tok.kind != token::comma)
			return Value();
	}

	if (tok.kind == token::eof)
		lex.error("parseVector: Reached end looking for '}'", tok.pos);

	size_t size = it - vec.begin();
	switch (size) {
	default:
	case 1:
		return Value();
	case 2:
		return Value(math::vector2d<f32>{vec[0], vec[1]});
	case 3:
		return Value(math::vector3d<f32>{vec[0], vec[1], vec[2]});
	case 4:
		return Value(math::vector4d<f32>{vec[0], vec[1], vec[2], vec[3]});
	}
}

// TODO: rewrite
void Parser::processCommand() {
	token tok = lex.getToken();

	if (tok.kind != token::name) {
		lex.error(string::compose("Unexpected token: %0", tok.value), tok.pos);
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
			lex.error(string::compose("hdf_version: invalid version %0.",
			               tok.value), tok.pos);
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

		bool strict = parseBoolean(tok.value);
	}
}
} // namespace hdf
} // namespace aw
