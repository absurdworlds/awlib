
#include <hrengin/filesystem/IReadFile.h>
#include <hrengin/filesystem/IBufferedStream.h>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/Vector2d.h>
#include <hrengin/common/Vector3d.h>

#include "CHndfParser.h"

namespace hrengin {
namespace io {

inline bool in(char c, char c1, char c2, char c3, char c4)
{
	return c == c1  ||  c == c2  ||  c == c3  ||  c == c4;
}

inline bool in(char c, char c1, char c2, char c3, char c4, char c5)
{
	return c == c1  ||  c == c2  ||  c == c3  ||  c == c4  ||  c == c5;
}

inline bool isNameChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-' || c == '_';
}

inline bool isNameBeginChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool isWhitespace(char c) {
	return (in(c, ' ', '\t', '\r', '\n'));
}

inline bool isInlineWhitespace(char c) {
	return c == ' ' || c == '\t';
}


template<typename T>
bool isValidHdfType(HdfType type)
{
	return false;
}

#if 0

template<typename T>
bool isValidHdfType(HdfType type, typename std::enable_if<std::is_integral<T>::value,T>::type* t = 0) {
	return HDF_INTEGER == type;
}

template<typename T>
bool isValidHdfType(HdfType type, typename std::enable_if<std::is_floating_point<T>::value,T>::type* t = 0) {
	return HDF_FLOAT == type;
}

#else

template<>
bool isValidHdfType<i32>(HdfType type) {
	return HDF_INTEGER == type;
}

template<>
bool isValidHdfType<u32>(HdfType type) {
	return HDF_INTEGER == type;
}

template<>
bool isValidHdfType<f32>(HdfType type) {
	return HDF_FLOAT == type;
}

template<>
bool isValidHdfType<f64>(HdfType type) {
	return HDF_FLOAT == type;
}
#endif

template<>
bool isValidHdfType<bool>(HdfType type) {
	return HDF_BOOLEAN == type;
}

template<>
bool isValidHdfType<std::string>(HdfType type) {
	return HDF_STRING == type;
}

template<>
bool isValidHdfType<Vector2d>(HdfType type) {
	return HDF_VECTOR2 == type;
}

template<>
bool isValidHdfType<Vector3d>(HdfType type) {
	return HDF_VECTOR3 == type;
}


HdfType hdfTokenToType(const HdfToken& token) 
{
	if(token.value == "bool" || token.value == "b") {
		return HDF_BOOLEAN;
	} else if(token.value == "int" || token.value == "i") {
		return HDF_INTEGER;
	} else if(token.value == "float" || token.value == "f") {
		return HDF_FLOAT;
	} else if(token.value == "vec3" || token.value == "v3") {
		return HDF_VECTOR3;
	} else if(token.value == "vec2" || token.value == "v2") {
		return HDF_VECTOR2;
	} else if(token.value == "string" || token.value == "s") {
		return HDF_STRING;
	} else {
		return HDF_UNKNOWN_TYPE;
	}
}

HdfType hdfConvertImpicitType(const HdfToken& token) 
{
	char c = token.value.c_str()[0];
	if(isNameBeginChar(c) || c == '"') {
		return HDF_STRING;
	} else if(c == '-' || (c > '0' && c < '9')) {
		return HDF_FLOAT;
	} else {
		return HDF_UNKNOWN_TYPE;
	}
}


IHndfParser* createHndfParser(IReadFile* file)
{
	if(!file->isOpen()) {
		return 0;
	}

	return new CHndfParser(file);
}

CHndfParser::CHndfParser(IReadFile* file)
: depth_(0)
{
	stream_ = createBufferedStream(file);
	
}

CHndfParser::~CHndfParser()
{
	delete stream_;
}

bool CHndfParser::read() {
	char c;

	stream_->getCurrent(c);

	if(c == 0) {
		return false;
	}

	fastForward();

	if(depth_ == 0) {
	
	} else {
		if(isNameBeginChar(c) || c == '[') {
			state_ = HDF_S_OBJECT;
		} else if(c == ']') {
			if(state_ != HDF_S_IDLE) {
				error(HDF_ERR_ERROR, "unexpected node-end");
			} else {
				depth_--;
			}
		}
	}

	return (state_ == HDF_S_PANIC) ? false : true;
}

HdfObjectType CHndfParser::getObjectType()
{
	if(state_ == HDF_S_PANIC) {
		return HDF_OBJ_NULL;
	}

	char c;

	stream_->getCurrent(c);

	if(state_ != HDF_S_OBJECT) {
		error(HDF_ERR_ERROR, "there is no object");
		return HDF_OBJ_NULL;
	} else {
		if(c == '[') {
			// step forward - getObjectName expects a nameChar to
			// be the first char
			stream_->getNext(c); 
			state_ = HDF_S_NODE_BEGIN;
			depth_ ++;
			return HDF_OBJ_NODE;
		} else if (c == '!') {
			if(depth_ > 0) {
				error(HDF_ERR_ERROR, "unexpected token: '!'");
				return HDF_OBJ_NULL;
			}
			state_ = HDF_S_CMD_BEGIN;
			return HDF_OBJ_CMD;
		} else if (isNameBeginChar(c)) {
			if(depth_ == 0) {
				error(HDF_ERR_ERROR, "unexpected name token");
				return HDF_OBJ_NULL;
			}
			state_ = HDF_S_VALUE_BEGIN;
			return HDF_OBJ_VAL;
		} else {
			error(HDF_ERR_ERROR, "invalid character: " + c);
			return HDF_OBJ_NULL;
		}
	}
}

void CHndfParser::getObjectName(std::string& name)
{
	if(state_ == HDF_S_PANIC) {
		return;
	}

	if(state_ == HDF_S_NODE_BEGIN) {
		readName(name);
		state_ = HDF_S_IDLE;
	} else if(state_ == HDF_S_VALUE_BEGIN) {
		readValueName(name);
		state_ = HDF_S_VALUE_DATA;
	}

	error(HDF_ERR_ERROR, "must be called after getObjectType()");
}

void CHndfParser::readFloat(float& val)
{
	readValue<f32>(val);
}
void CHndfParser::readFloat(double& val)
{
	readValue<f64>(val);
}
void CHndfParser::readInt(u32& val)
{
	readValue<u32>(val);
}
void CHndfParser::readInt(i32& val)
{
	readValue<i32>(val);
}
void CHndfParser::readBool(bool& val)
{
	readValue<bool>(val);
}
void CHndfParser::readString(std::string& val)
{
	readValue<std::string>(val);
}
void CHndfParser::readVector3d(Vector3d& val)
{
	readValue<Vector3d>(val);
}

//TODO: rewrite those two properly
void CHndfParser::skipValue() 
{
	HdfToken token;
	HdfType type;
	
	bool hasType = parseType(token);

	if(hasType) {
		type = hdfTokenToType(token);
		readToken(token);
	} else {
		type = hdfConvertImpicitType(token);
	}
	
	if(type == HDF_VECTOR3 || type == HDF_VECTOR2) {
		readToken(token);
		if(type == HDF_VECTOR3) {
			readToken(token);
		}
	}
}

void CHndfParser::skipNode() 
{
	char c;

	stream_->getCurrent(c);

	while (c != ']') {
		stream_->getNext(c);
	}

	read();
}

void CHndfParser::error(HdfParserMessage type, std::string msg)
{
	errors_.push_back(msg);
	printf("[HDF:%d]: %s\n",0,msg.c_str());
}

void CHndfParser::skipLine()
{
	char c;
	
	stream_->getCurrent(c);
	
	do {
		stream_->getNext(c);
	} while (c != '\n');
}

void CHndfParser::skipWhitespace()
{
	char c;

	stream_->getCurrent(c);
	
	while(isWhitespace(c)) {
		stream_->getNext(c);
	}
}
void CHndfParser::skipInlineWhitespace()
{
	char c;

	stream_->getCurrent(c);
	
	while(isInlineWhitespace(c)) {
		stream_->getNext(c);
	}
}

void CHndfParser::fastForward() {
	char c;

	stream_->getCurrent(c);

	bool end = false;

	do {
		if(isWhitespace(c)) {
			skipWhitespace();
		} else if(c == '/') {
			stream_->getNext(c);

			if(c == '/') {
				//token.type = tokenCOMMENT;
				skipLine();
			} else {
				error(HDF_ERR_WARNING,"unexpected token: /");
			}
		} else {
			end = true;
		}
		
		stream_->getNext(c);
	} while (end == false);
}

bool CHndfParser::parseType(HdfToken& token) {
	skipInlineWhitespace();

	char c;

	stream_->getCurrent(c);

	if(c != '=') {
		error(HDF_ERR_ERROR, "illegal token");
	} 
	
	skipInlineWhitespace();
	
	stream_->getCurrent(c);

	if(isNameBeginChar(c)) {
		token.type = HDF_TOKEN_NAME;
		readName(token.value);
	} else {
		error(HDF_ERR_ERROR, "illegal token");	
	}

	skipInlineWhitespace();

	if(c == ':') {
		stream_->getNext(c);
		return true;
	} else {
		return false;
	}
}

void CHndfParser::readToken(HdfToken& token)
{
	fastForward();

	char c;

	stream_->getCurrent(c);

	if(isNameBeginChar(c)) {
		token.type = HDF_TOKEN_NAME;
		readName(token.value);	
	} else if(c == '-' || (c > '0' && c < '9')) {
		token.type = HDF_TOKEN_NUMBER;
		readNumber(token.value);
	} else if(c == '"') {
		token.type = HDF_TOKEN_STRING;
		readStringToken(token.value);
	} else {
		error(HDF_ERR_ERROR,"illegal token");
	}
}

void CHndfParser::readStringToken(std::string& val) {
	char c;

	stream_->getCurrent(c);
	
	while (c != '"') {
		if ( c == '\\' ) {
			stream_->getNext(c);
		}
		val += c;
		stream_->getNext(c);
	}
}

void CHndfParser::readNumber(std::string& val)
{
	char c;

	stream_->getCurrent(c);

	while (!isWhitespace(c)) {
		if (!(c >= '0' && c <= '9') && !in(c, '.', 'e', 'E', '+', '-' )) {
			error(HDF_ERR_WARNING, "invalid number");
		}
		val += c;
		stream_->getNext(c);
	}
}

void CHndfParser::readName(std::string& name, char stop)
{
	char c;
	
	stream_->getCurrent(c);

	while(!isWhitespace(c) && (c != stop) && (c != ']')) {
		if(isNameChar(c)) {
			name += c;
		} else {
			error(HDF_ERR_WARNING, "invalid name char");
		}
		stream_->getNext(c);
	}
}

inline void CHndfParser::readValueName(std::string& name)
{
	readName(name, '=');
}

void CHndfParser::readTypeName(std::string& name)
{
	readName(name, ':');
}


template<typename T> 
void CHndfParser::readValue(T& var)
{
	HdfToken token;
	HdfType type;
	
	bool hasType = parseType(token);

	if(hasType) {
		type = hdfTokenToType(token);
		readToken(token);
	} else {
		type = hdfConvertImpicitType(token);
	}
	
	if(isValidHdfType<T>(type) == false) {
		error(HDF_ERR_ERROR, "type mismatch " + token.value);
		//skipValue(type);

		return;
	}
	
	convertValue<T>(token, var);
}

// TODO: make helper class to reduce almost duplicate functions

template<typename T> 
void CHndfParser::convertValue(HdfToken& token, T& val)
{
	// should never get this error
	error(HDF_ERR_ERROR, "unknown type");
}

template<> 
void CHndfParser::convertValue(HdfToken& token, f32& val)
{	
	val = strtof(token.value.c_str(), 0);
}

template<> 
void CHndfParser::convertValue(HdfToken& token, f64& val)
{
	val = strtod(token.value.c_str(), 0);
}

template<> 
void CHndfParser::convertValue(HdfToken& token, Vector3d& val)
{
	val.X = strtod(token.value.c_str(), 0);
	
	readToken(token);
	
	val.Y = strtod(token.value.c_str(), 0);
	
	readToken(token);
	
	val.Z = strtod(token.value.c_str(), 0);
}

template<> 
void CHndfParser::convertValue(HdfToken& token, std::string& val)
{	
	val = token.value;
}

template<> 
void CHndfParser::convertValue(HdfToken& token, u32& val)
{	
	val = strtoul(token.value.c_str(), 0, 10);
}

template<> 
void CHndfParser::convertValue(HdfToken& token, i32& val)
{	
	val = strtol(token.value.c_str(), 0, 10);
}

template<> 
void CHndfParser::convertValue(HdfToken& token, bool& val)
{
	if(token.value == "true" || token.value == "1") {
		val = true;
	} else if(token.value == "false" || token.value == "0") {
		val = false;
	} else {
		error(HDF_ERR_WARNING, "invalid boolean value");
	}
}


// todo: rewrite
void CHndfParser::readDirective() {
	HdfToken token;
	
	char c;

	stream_->getCurrent(c);

	if (c == '!') {
		stream_->getNext(c);
	}

	readToken(token);

	if (token.value == "hndf_version") {
		readToken(token);
		if(token.type != HDF_TOKEN_STRING) {
			error(HDF_ERR_ERROR,"expected string");
			return ;
		} else if(token.value == "1.1") {
			error(HDF_ERR_ERROR, "Version 1.1 is outdated.");
			return;
		} else if(token.value != "1.1.1") {
			error(HDF_ERR_ERROR, "your version is bullshit!");
			return;
		}
	}
}


} // namespace io
} // namespace hrengin