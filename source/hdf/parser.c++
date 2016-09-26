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

bool Parser::read() {
	token tok = lex.peekToken();

	if (tok.kind == token::eof)
		return false;

	switch (tok.kind) {
	case token::eof:
		return false;
	case token::bang:
		if (depth > 0) {
			error(tok.pos, "Unexpected ! inside node.");
			break;
		}
		lex.getToken();
		processCommand();
		break;
	case token::node_begin:
		state = State::Object;
		return true;
	case token::node_end:
		if (depth == 0) {
			error(tok.pos, "Unexpected ].");
			break;
		}
		state = State::Object;
		return true;
	case token::name:
		if (depth == 0) {
			lex.getToken();
			error(tok.pos, "Value must be inside node.");
			break;
		}
		state = State::Object;
		return true;
	case token::invalid:
		lex.getToken();
		error(tok.pos,
		      string::compose("read(): illegal token: %0", tok.value));
		break;
	default:
		lex.getToken();
		error(tok.pos,
		      string::compose("read(): unexpected token: %0", tok.value));
	}

	return read();
}

Object Parser::getObject()
{
	token tok = lex.getToken();

	if (state != State::Object) {
		error(tok.pos, "there is no object");
		return Object::Null;
	}

	switch (tok.kind) {
	case token::node_begin:
		++depth;

		state = State::Idle;
		return Object(Object::Node, tok.value);
	case token::node_end:
		--depth;

		state = State::Idle;
		return Object(Object::NodeEnd);
	case token::name:
		state = State::Value;
		return Object(Object::Value, tok.value);
	default:
		error(tok.pos, "Unexpected token.");
	}

	return Object(Object::Null);
}

void Parser::skipValue() 
{
	Value trash;
	readValue(trash);
}

void Parser::skipNode() 
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

	read();
}

void Parser::error(size_t pos, std::string msg)
{
	// TODO: use aw::log
	printf("[HDF:%zu]: %s\n", pos, msg.c_str());
}

void Parser::readValue(Value& var)
{
	if (state != State::Value) {
		error(0, "Call getObject() before callin readValue");
		return;
	}
	token tok = lex.getToken();

	if (tok.kind != token::equals) {
		error(tok.pos, string::compose("Expected '=', got %0", tok.value));
		return;
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
		error(tok.pos, "parseVector: Reached end looking for '}'");

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
	Token tok = lex.getToken();

	if (tok.kind != token::name) {
		error(tok.pos,
		      string::compose("Unexpected token: %0", tok.value));
		return;
	}

	if (tok.value == "hdf_version") {
		tok = lex.getToken();

		if (tok.kind != token::string) {
			error(tok.pos, "Expected string after \"hdf_version\".");
			return;
		}

		std::string ver = tok.value.substr(0,3);
		if (ver == "1.2") {
			error(tok.pos, "HDF version: 1.2");
		} else if (ver == "1.1") {
			error(tok.pos, "Version 1.1 is not supported.");
			return;
		} else if (ver == "1.0") {
			error(tok.pos, "Version 1.0 is not supported.");
			return;
		} else {
			error(tok.pos,
			      string::compose(
			              "hdf_version: invalid version %0.",
			               tok.value));
			return;
		}
	}

	if (tok.value == "strict") {
		error(tok.pos, "Strict mode: not implemented");

		tok = lex.getToken();

		if (tok.type != Token::Name && tok.type != Token::Number) {
			error(tok.pos, "Expected true/false value.");
			return;
		}

		bool strict = parseBoolean(tok.value);
	}
}
} // namespace hdf
} // namespace aw
