/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cassert>
#include <cstdio>

#include <awengine/string/compose.h>
#include <awengine/io/InputStream.h>
#include <awengine/hdf/Type.h>

#include "Parser.h"

namespace awrts {
namespace hdf {
bool in(char c, char c1)
{
	return c == c1;
}

template<typename... Args>
bool in(char c, char c1, Args... chars)
{
	return c == c1 || in(c, chars...);
}


inline bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

inline bool isNameBeginChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool isNameChar(char c) {
	return isNameBeginChar(c) || isDigit(c) || c == '-' || c == '_';
}

inline bool isWhitespace(char c) {
	return (in(c, ' ', '\t', '\r', '\n'));
}

inline bool isInlineWhitespace(char c) {
	return c == ' ' || c == '\t';
}

hdf::Type tokenToType(Token const& token) 
{
	if(token.value == "bool" || token.value == "b") {
		return Type::Boolean;
	} else if(token.value == "int" || token.value == "i") {
		return Type::Integer;
	} else if(token.value == "float" || token.value == "f") {
		return Type::Float;
	} else if(token.value == "vec3" || token.value == "v3") {
		return Type::Vector3d;
	} else if(token.value == "vec2" || token.value == "v2") {
		return Type::Vector2d;
	} else if(token.value == "string" || token.value == "s") {
		return Type::String;
	} else {
		return Type::Unknown;
	}
}


Parser* createParser(io::InputStream& stream)
{
	return new impl_::Parser(stream);
}

namespace impl_ {
Parser::Parser(io::InputStream& stream)
	: depth(0), state(State::Idle), stream(stream)
{
}

bool Parser::read() {
	tok = getToken();

	if (tok.type == Token::Eof)
		return false;

	switch (tok.type) {
	case Token::Eof:
		return false;
	case Token::Bang:
		if (depth > 0) {
			error(HDF_LOG_WARNING, "Unexpected ! inside node.");
			break;
		}
		processCommand();
		break;
	case Token::NodeBegin:
		state = State::Object;
		return true;
	case Token::NodeEnd:
		if (depth == 0) {
			error(HDF_LOG_WARNING, "Unexpected ].");
			break;
		}
		state = State::Object;
		return true;
	case Token::Name:
		if (depth == 0) {
			error(HDF_LOG_WARNING, "Value must be inside node.");
			break;
		}
		state = State::Object;
		return true;
	case Token::Invalid:
		error(HDF_LOG_WARNING,
		      string::compose("Illegal token: %0", tok.value));
		break;
	default:
		error(HDF_LOG_WARNING,
		      string::compose("Unexpected token: %0", tok.value));
	}

	return read();
}

Object Parser::getObject()
{
	if(state != State::Object) {
		error(HDF_LOG_ERROR, "there is no object");
		return Object::Null;
	}

	switch (tok.type) {
	case Token::NodeBegin:
		++depth;

		tok = getToken();
		if (tok.type != Token::Name)
			break;

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
		error(HDF_LOG_ERROR, "Unexpected token.");
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
	size_t depth = 1;

	do {
		if (tok.type == Token::NodeBegin) {
			++depth;
		} else if (tok.type == Token::NodeEnd) {
			--depth;
		}
		tok = getToken();
	} while (depth > 0);

	read();
}

void Parser::error(hdf::ParserMessage type, std::string msg)
{
	errors.push_back(msg);
	printf("[HDF:%u]: %s\n", stream.getPos(), msg.c_str());
}

//void Parser::skip(bool (*condition)(char))
template<typename Func>
void Parser::skip(Func condition)
{
	char c;
	stream.peek(c);

	while(condition(c) && c != 0)
		stream.next(c);
}

void Parser::skipLine()
{
	skip(
		[] (char c) {
			return c != '\n';
		}
	);
}

void Parser::skipWhitespace()
{
	skip(isWhitespace);
}

void Parser::skipInlineWhitespace()
{
	skip(isInlineWhitespace);
}

bool junk(char c)
{
	return isWhitespace(c) || c == '/';
}

void Parser::fastForward()
{
	char c;
	stream.peek(c);

	if (isWhitespace(c)) {
		skipWhitespace();
	} else if (c == '/') {
		stream.next(c);

		if (c == '/') {
			skipLine();
		} else {
			stream.get(c);
			error(HDF_LOG_WARNING,"unexpected token: /");
		}
	}
}

Token Parser::getToken() {
	char c;
	stream.peek(c);

	while (junk(c))
		fastForward();

	stream.peek(c);

	Token tok;

	switch (c) {
	case 0:
		return Token(Token::Eof);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return Token(Token::Number, readNumber());
	case '"':
		stream.next(c); // consume '"'
		return Token(Token::String, readString());
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
	case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
	case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
	case 'v': case 'w': case 'x': case 'y': case 'z':
		return Token(Token::Name, readName());
	case '=':
		return Token(Token::Equals, c);
	case ':':
		return Token(Token::Colon, c);
	case ',':
		return Token(Token::Comma, c);
	case '!':
		return Token(Token::Bang, c);
	case '[':
		return Token(Token::NodeBegin, c);
	case ']':
		return Token(Token::NodeEnd, c);
	case '{':
		return Token(Token::VecBegin, c);
	case '}':
		return Token(Token::VecEnd, c);
	default:
		return Token(Token::Invalid, readIllegalToken());
	}
}

std::string Parser::readNumber()
{
	char c;
	stream.peek(c);

	std::string val;

	while ((c >= '0' && c <= '9') || in(c, '.', 'e', 'E', '+', '-' )) {
		val += c;
		stream.next(c);
	}

	return val;
}

std::string Parser::readString() {
	char c;
	stream.peek(c);

	std::string val;

	while (c != '"') {
		// When '\' is encountered in a string, skip the '\' and read
		// next character as it is.
		if (c == '\\')
			stream.next(c);

		val += c;
		stream.next(c);
	}

	// consume "
	stream.get(c);
	return val;
}

std::string Parser::readName()
{
	char c;
	stream.peek(c);

	std::string name;

	while(isNameChar(c)) {
		name += c;

		stream.next(c);
	}

	return name;
}

std::string Parser::readIllegalToken()
{
	char c;
	stream.peek(c);

	std::string name;

	while(!isWhitespace(c) && !in(c, '[', ']', '=', ':', ',')) {
		name += c;

		stream.next(c);
	}

	return name;
}

void Parser::readValue(Value& var)
{
	if (tok.type != Token::Name)
		return;

	Token id = tok;

	tok = getToken();
	bool hasType = tok.type == Token::Colon;

	var = hasType ? convertValue(tokenToType(id)) :
		        convertUntypedValue();

	state = State::Idle;
}


Value Parser::convertValue(Type type)
{
	std::string str = tok.value;

	switch (type) {
	case Type::Enum:
	case Type::String:
		return Value(str);
	case Type::Float:
		return Value(std::stod(str));
	case Type::Integer:
		return Value(std::stoll(str));
	case Type::Boolean:
	       {
			bool val;

			if(str == "true" || str == "1") {
				val = true;
			} else if(str == "false" || str == "0") {
				val = false;
			}

			return Value(val);
		}
	case Type::Vector2d: {
			Vector2d<f32> result;
			bool parse = parseVector(result, 2);
			if (!parse)
				break;

			return Value(result);
		}
	case Type::Vector3d: {
			Vector3d<f32> result;
			bool parse = parseVector(result, 3);
			if (!parse)
				break;

			return Value(result);
		}
	case Type::Vector4d: {
			Vector4d<f32> result;
			bool parse = parseVector(result, 4);
			if (!parse)
				break;

			return Value(result);
		}
	}

	return Value();
}

Value Parser::convertUntypedValue()
{
	switch (tok.type) {
	case Token::String:
		return convertValue(Type::String);
	case Token::Number:
		{
			auto type = Type::Integer;
			for (char c : tok.value) {
				if (c == '.') {
					type = Type::Float;
				}
			}

			return convertValue(type);
		}
	case Token::Name:
		if (tok.value == "true" || tok.value == "false")
			return convertValue(Type::Boolean);

		return convertValue(Type::Enum);
	case Token::VecBegin:
		{
		}

	}

	return Value();
}

template <typename T>
bool Parser::parseVector(T& vec, size_t vecsize)
{
	for (int i = 0; i < vecsize; ++i) {
		tok = getToken();
		if (tok.type != Token::Number)
			return false;

		tok = getToken();
		vec[i] = stof(tok.value);

		if (tok.type != Token::Comma)
			return false;
	}

}

// TODO: rewrite
void Parser::processCommand() {
	tok = getToken();

	if (tok.type != Token::Name) {
		error(HDF_LOG_ERROR,
		      string::compose("Unexpected token: %0", tok.value));
		return;
	}

	if (tok.value == "hdf_version") {
		tok = getToken();

		if (tok.type != Token::String) {
			error(HDF_LOG_ERROR, "Expected string after \"hdf_version\".");
			return;
		}

		std::string ver = tok.value.substr(0,3);
		if (ver == "1.2") {
			error(HDF_LOG_NOTICE, "HDF version: 1.2");
		} else if (ver  == "1.1") {
			error(HDF_LOG_ERROR, "Version 1.1 is not supported.");
			return;
		} else if (ver == "1.0") {
			error(HDF_LOG_ERROR, "Version 1.0 is not supported.");
			return;
		} else {
			error(HDF_LOG_ERROR,
			      string::compose(
			              "hdf_version: invalid version %0.",
			               tok.value));
			return;
		}
	}
}
} // namespace impl_
} // namespace hdf
} // namespace awrts
