/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cassert>
#include <cstdio>

#include <aw/utility/string/compose.h>
#include <aw/io/InputStream.h>
#include <aw/hdf/Type.h>
#include <aw/math/vector4d.h>

#include "Parser.h"

namespace aw {
namespace hdf {
hdf::Type tokenToType(Token const& token) 
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

Parser* createParser(io::InputStream& stream)
{
	return new impl_::Parser(stream);
}

namespace impl_ {
Parser::Parser(io::InputStream& stream)
	: depth(0), state(State::Idle), lex(stream)
{
}

bool Parser::read() {
	Token tok = lex.peekToken();

	if (tok.type == Token::Eof)
		return false;

	switch (tok.type) {
	case Token::Eof:
		return false;
	case Token::Bang:
		if (depth > 0) {
			error(tok.pos, "Unexpected ! inside node.");
			break;
		}
		lex.getToken();
		processCommand();
		break;
	case Token::NodeBegin:
		state = State::Object;
		return true;
	case Token::NodeEnd:
		if (depth == 0) {
			error(tok.pos, "Unexpected ].");
			break;
		}
		state = State::Object;
		return true;
	case Token::Name:
		if (depth == 0) {
			lex.getToken();
			error(tok.pos, "Value must be inside node.");
			break;
		}
		state = State::Object;
		return true;
	case Token::Invalid:
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
	Token tok = lex.getToken();

	if (state != State::Object) {
		error(tok.pos, "there is no object");
		return Object::Null;
	}

	switch (tok.type) {
	case Token::NodeBegin:
		++depth;

		state = State::Idle;
		return Object(Object::Node, tok.value);
	case Token::NodeEnd:
		--depth;

		state = State::Idle;
		return Object(Object::NodeEnd);
	case Token::Name:
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
	Token tok = lex.peekToken();

	size_t depth = 1;

	do {
		if (tok.type == Token::NodeBegin) {
			++depth;
		} else if (tok.type == Token::NodeEnd) {
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
	Token tok = lex.getToken();

	if (tok.type != Token::Equals) {
		error(tok.pos, string::compose("Expected '=', got %0", tok.value));
		return;
	}
	Token id = lex.getToken();
	tok = lex.peekToken();

	bool hasType = tok.type == Token::Colon;
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
	Token tok = lex.getToken();

	switch (type) {
	case Type::Enum:
	case Type::String:
		if (!(tok.type == Token::String || tok.type == Token::Name))
			break;

		return Value(tok.value);
	case Type::Float:
		if (tok.type != Token::Number)
			break;

		return Value(std::stod(tok.value));
	case Type::Integer:
		if (tok.type != Token::Number)
			break;

		return Value(i64(std::stoll(tok.value)));
	case Type::Boolean:
		if (tok.type != Token::Name)
			break;

		return Value(parseBoolean(tok.value));
	case Type::Vector2d:
	case Type::Vector3d:
	case Type::Vector4d:
		return parseVector(type);
	}

	return Value();
}

Value Parser::convertValue(Token tok)
{
	switch (tok.type) {
	case Token::String:
		return Value(tok.value);
	case Token::Number:
		return parseInteger(tok.value);
	case Token::Name:
		if (tok.value == "true" || tok.value == "false")
			return Value(bool(parseBoolean(tok.value)));
		return Value(tok.value);
	case Token::VecBegin:
		return parseVector();
	}

	return Value();
}

Value Parser::parseVector(Type type)
{
	Token tok = lex.peekToken();

	if (tok.type != Token::VecBegin)
		return Value();

	Value tmp = parseVector();

	if (tmp.getType() != type)
		return Value();

	return tmp;
}

Value Parser::parseVector()
{
	Token tok = lex.peekToken();

	// Damn it, why is it so messy …
	std::array<f32, 4> vec;
	auto it = vec.begin();

	while (tok.type != Token::Eof) {
		tok = lex.getToken();
		if (tok.type != Token::Number)
			return Value();

		if (it < vec.end())
			*(it++) = stof(tok.value);

		tok = lex.getToken();
		
		if (tok.type == Token::VecEnd)
			break;

		if (tok.type != Token::Comma)
			return Value();
	}

	if (tok.type == Token::Eof)
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

	if (tok.type != Token::Name) {
		error(tok.pos,
		      string::compose("Unexpected token: %0", tok.value));
		return;
	}

	if (tok.value == "hdf_version") {
		tok = lex.getToken();

		if (tok.type != Token::String) {
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
} // namespace impl_
} // namespace hdf
} // namespace aw
