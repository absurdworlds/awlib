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

inline bool in(char c, char c1, char c2, char c3, char c4)
{
	return c == c1  ||  c == c2  ||  c == c3  ||  c == c4;
}

inline bool in(char c, char c1, char c2, char c3, char c4, char c5)
{
	return c == c1  ||  c == c2  ||  c == c3  ||  c == c4  ||  c == c5;
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

hdf::Type convertImpicitType(Token const& token) 
{
	char c = token.value.c_str()[0];
	if(isNameBeginChar(c) || c == '"') {
		return Type::String;
	} else if(c == '-' || (c > '0' && c < '9')) {
		return Type::Float;
	} else {
		return Type::Unknown;
	}
}

Parser* createParser(io::InputStream* stream)
{
	return new impl_::Parser(stream);
}

namespace impl_ {
Parser::Parser(io::InputStream* stream)
	: depth(0), state(State::Idle), stream(stream)
{
}

bool Parser::read() {
	char c;
	fastForward();
	stream->peek(c);

	if(c == 0)
		return false;

	if(depth == 0) {
		while(c == '!') {
			processCommand();
			fastForward();
			stream->peek(c);
		}
		if(c == '[' || c == ']') {
			state = State::Object;
		}
	} else {
		if(isNameBeginChar(c) || c == '[' || c == ']') {
			state = State::Object;
		}
	}

	return (state == State::Panic) ? false : true;
}

Object Parser::getObjectType()
{
	if(state == State::Panic)
		return Object::Null;

	char c;
	stream->peek(c);

	if(state != State::Object) {
		error(HDF_LOG_ERROR, "there is no object");
		return Object::Null;
	} else {
		if(c == '[') {
			// step forward - getObjectName expects a nameChar to
			// be the first char
			stream->get(c); 
			++depth;
			state = State::Node;
			return Object::Node;
		} else if (isNameBeginChar(c)) {
			if(depth == 0) {
				error(HDF_LOG_ERROR, "unexpected name token");
				return Object::Null;
			}
			state = State::Value;
			return Object::Value;
		} else if (c == ']') {
			stream->get(c); 
			--depth;
			state = State::Idle;
			return Object::NodeEnd;

			/*if(state != State::Idle) {
				error(HDF_LOG_ERROR, "unexpected node-end");
			} else {
				depth--;
			}*/
		} else if (c == '!') {
			//if(depth > 0) {
			error(HDF_LOG_ERROR, "unexpected token: '!'");
			return Object::Null;
			//}
			//state = HDF_S_MD_BEGIN;
			//return HDF_OBJ_MD;
		} else {
			std::string msg("invalid character: ");
			msg += c;
			error(HDF_LOG_ERROR, msg);
			return Object::Null;
		}
	}
}

void Parser::getObjectName(std::string& name)
{
	if(state == State::Panic)
		return;

	if(state == State::Node) {
		readName(name);
		state = State::Idle;
	} else if(state == State::Value) {
		readValueName(name);
		state = State::Data;
	} else {
		error(HDF_LOG_ERROR, "must be called after getObjectType()");
	}
}

void Parser::readFloat(float& val)
{
	readValue<f32>(val);
}
void Parser::readFloat(double& val)
{
	readValue<f64>(val);
}
void Parser::readInt(u32& val)
{
	readValue<u32>(val);
}
void Parser::readInt(i32& val)
{
	readValue<i32>(val);
}
void Parser::readBool(bool& val)
{
	readValue<bool>(val);
}
void Parser::readString(std::string& val)
{
	readValue<std::string>(val);
}
void Parser::readVector3d(Vector3d<f32>& val)
{
	readValue<Vector3d<f32>>(val);
}

//TODO: rewrite those two properly
void Parser::skipValue() 
{
	Token token;
	hdf::Type type;

	bool hasType = parseType(token);

	if(hasType) {
		type = tokenToType(token);
		readToken(token);
	} else {
		type = convertImpicitType(token);
	}

	if(type == Type::Vector3d || type == Type::Vector2d) {
		readToken(token);
		if(type == Type::Vector3d) {
			readToken(token);
		}
	}
}

void Parser::skipNode() 
{
	char c;
	u32 depth = 1;

	while (depth > 0) {
		stream->get(c);

		if(c == '[' ) {
			depth++;
		} else if(c == ']') {
			depth--;
		}
	}

	read();
}

void Parser::error(hdf::ParserMessage type, std::string msg)
{
	errors.push_back(msg);
	printf("[HDF:%u]: %s\n",stream->getPos(),msg.c_str());

	if(type == HDF_LOG_ERROR)
		state = State::Panic;
}

//void Parser::skip(bool (*condition)(char))
template<bool (*condition)(char)>
void Parser::skip()
{
	char c;
	stream->peek(c);

	while(condition(c) && c != 0)
		stream->get(c);
}

inline bool notLineBreak(char c)
{
	return c != '\n';
}

void Parser::skipLine()
{
	skip<notLineBreak>();
}

void Parser::skipWhitespace()
{
	skip<isWhitespace>();
}

void Parser::skipInlineWhitespace()
{
	skip<isInlineWhitespace>();
}

void Parser::fastForward() {
	char c;
	stream->peek(c);

	bool needsFastForward = isWhitespace(c) || c == '/';

	while (needsFastForward) {
		if(isWhitespace(c)) {
			skipWhitespace();
		} else if(c == '/') {
			stream->get(c);
			stream->peek(c);

			if(c == '/') {
				//token.type = tokenCOMMENT;
				skipLine();
			} else {
				error(HDF_LOG_WARNING,"unexpected token: /");
			}
		}		

		stream->peek(c);
		needsFastForward = isWhitespace(c) || c == '/';
		//stream->getNext(c);
	}
}

bool Parser::parseType(Token& token) {
	skipInlineWhitespace();

	char c;
	stream->peek(c);

	if(c == '=') {
		stream->get(c);
	} else {
		error(HDF_LOG_ERROR, "illegal token, expected '='");
	}

	skipInlineWhitespace();

	stream->peek(c);

	if(isNameBeginChar(c)) {
		token.type = Token::Name;
		readName(token.value, ':');
	} else {
		error(HDF_LOG_ERROR,
		      string::compose("illegal token %0, expected typename", c));
	}

	skipInlineWhitespace();

	stream->peek(c);

	if(c == ':') {
		stream->get(c);
		return true;
	} else {
		//stream->getNext(c);
		return false;
	}
}

void Parser::readToken(Token& token)
{
	fastForward();

	char c;
	stream->peek(c);

	if(isNameBeginChar(c)) {
		token.type = Token::Name;
		readName(token.value);	
	} else if(c == '-' || (c >= '0' && c <= '9')) {
		token.type = Token::Number;
		readNumber(token.value);
	} else if(c == '"') {
		token.type = Token::String;
		readStringToken(token.value);
	} else {
		error(HDF_LOG_ERROR,"illegal token");
	}
}

void Parser::readStringToken(std::string& val) {
	val = "";
	char c;
	stream->peek(c);

	assert(c == '"' && "Improper call of Parser::readStringToken()");

	stream->get(c);

	while (c != '"') {
		// When '\' is encountered in a string, skip the '\' and read
		// next character as it is.
		stream->peek(c);
		if (c == '\\')
			stream->get(c);

		stream->peek(c);
		val += c;
		stream->get(c);
	}

	// consume "
	stream->get(c);
}

void Parser::readNumber(std::string& val)
{
	val = "";
	char c;

	stream->peek(c);

	while (!isWhitespace(c) && (c != ']')) {
		if (!(c >= '0' && c <= '9') && !in(c, '.', 'e', 'E', '+', '-' ))
			error(HDF_LOG_WARNING, "invalid number");

		stream->get(c);
		val += c;
		stream->peek(c);
	}
}

void Parser::readName(std::string& name, char stop)
{
	name = "";
	char c;
	stream->peek(c);

	while(!isWhitespace(c) && (c != stop) && (c != ']')) {
		stream->get(c);

		if(isNameChar(c)) {
			name += c;
		} else {
			error(HDF_LOG_WARNING, "invalid name char");
		}

		stream->peek(c);
	}
}

void Parser::readValueName(std::string& name)
{
	readName(name, '=');
}

void Parser::readTypeName(std::string& name)
{
	readName(name, ':');
}


template<typename T> 
void Parser::readValue(T& var)
{
	Token token;
	hdf::Type type;

	bool hasType = parseType(token);

	if(hasType) {
		type = tokenToType(token);
		readToken(token);
	} else {
		type = convertImpicitType(token);
	}

	if(checkType<T>(type) == false) {
		error(HDF_LOG_ERROR, "type mismatch: " + token.value);
		//skipValue(type);

		return;
	}

	convertValue<T>(token, var);
	state = State::Idle;
}

// TODO: make helper class to reduce almost duplicate functions

template<typename T>
void Parser::convertValue(Token& token, T& val)
{
	// should never get this error
	error(HDF_LOG_ERROR, "unknown type");
}

template<>
void Parser::convertValue(Token& token, f32& val)
{	
	val = strtof(token.value.c_str(), 0);
}

template<>
void Parser::convertValue(Token& token, f64& val)
{
	val = strtod(token.value.c_str(), 0);
}

template<>
void Parser::convertValue(Token& token, Vector3d<f32>& val)
{
	val[0] = strtod(token.value.c_str(), 0);

	readToken(token);

	val[1] = strtod(token.value.c_str(), 0);

	readToken(token);

	val[2] = strtod(token.value.c_str(), 0);
}

template<>
void Parser::convertValue(Token& token, std::string& val)
{	
	val = token.value;
}

template<>
void Parser::convertValue(Token& token, u32& val)
{	
	val = strtoul(token.value.c_str(), 0, 10);
}

template<>
void Parser::convertValue(Token& token, i32& val)
{	
	val = strtol(token.value.c_str(), 0, 10);
}

template<>
void Parser::convertValue(Token& token, bool& val)
{
	if(token.value == "true" || token.value == "1") {
		val = true;
	} else if(token.value == "false" || token.value == "0") {
		val = false;
	} else {
		error(HDF_LOG_WARNING, "invalid boolean value");
	}
}

// TODO: rewrite
void Parser::processCommand() {
	Token token;

	char c;

	stream->peek(c);

	if (c == '!') {
		stream->get(c);
	} else {
		error(HDF_LOG_ERROR, "No command to process");
	}

	readToken(token);

	if (token.value == "hdf_version" || token.value == "hdf") {
		readToken(token);
		if(token.type != Token::String) {
			error(HDF_LOG_ERROR,"expected string");
			return ;
		} else if(token.value == "1.1.1") {
			error(HDF_LOG_NOTICE, "HDF version: 1.1.1");
			return;
		} else if(token.value == "1.1") {
			error(HDF_LOG_ERROR, "Version 1.1 is outdated.");
			return;
		} else {
			error(HDF_LOG_ERROR,
			      string::compose(
			              "format %0 is not supported.",
			               token.value));
			return;
		}
	}
}
} // namespace impl_
} // namespace hdf
} // namespace awrts
