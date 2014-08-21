
#include <hrengin/filesystem/IReadFile.h>
#include <hrengin/filesystem/IBufferedStream.h>

#include "CHndfParser.h"
#include "HdfTypes.h"

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

bool CHndfParser::read() {
	char c;

	stream_->getCurrent(c);

	if(c == 0) {
		return false;
	}

	fastForward();

	if(depth_ == 0) {
	
	} else {
		if(c == ']') {
			if(state_ != HDF_S_IDLE) {
				error(HDF_ERR_ERROR, "unexpected node-end");
			} else {
				depth_--;
			}
		}
	}
}

void CHndfParser::readToken(HdfToken& token)
{
	fastForward();

	char c;

	stream_->getCurrent(c);

	if(isNameBeginChar(c)) {
	
	} else if(c == '-' || (c > '0' && c < '9')) {
		token.type = HDF_TOKEN_NUMBER;
		readNumber(token.value);
	} else if(c == '"') {
		token.type = HDF_TOKEN_STRING;
		readString(token.value);
	} else if(isNameBeginChar(c)) {
		token.type = HDF_TOKEN_NAME;
		readName(token.value);
	} else {
		error(HDF_ERR_ERROR,"illegal token");
	}
}

void CHndfParser::readString(std::string& val) {
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

	while(!isWhitespace(c) && (c != stop)) {
		if(isNameChar(c)) {
			name += c;
		} else {
			error(HDF_ERR_WARNING, "invalid name char");
		}
		stream_->getNext(c);
	}
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

	bool hasType = parseType(token);

	if(hasType) {
		HdfType type = hdfTokenToType(token);

	} else {
		HdfType = hdfConvertImpicitType(token);
	}
	
	if(isValidHdfType<T>(type) == false) {
		error(HDF_EL_ERROR, "type mismatch " + token);
		skipValue(type);

		return;
	}
	
	convertValue<T>(T& var);
}

template<typename T> 
void CHndfParser::convertValue(T& val)
{
	// should never get this error
	error(HDF_EL_ERROR, "unknown type");
}

template<> 
void CHndfParser::convertValue(float& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtof(token.value.c_str(), 0);
}

template<> 
void CHndfParser::convertValue(double& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtod(token.value.c_str(), 0);
}

template<> 
void CHndfParser::convertValue(Vector3d& val)
{
	HdfToken token;
	
	// would look nicer:
	// repeat 3 {
	readToken(token);
	
	val.X = strtod(token.value.c_str(), 0);
	//}
	
	readToken(token);
	
	val.Y = strtod(token.value.c_str(), 0);
	
	readToken(token);
	
	val.Z = strtod(token.value.c_str(), 0);
}

template<> 
void CHndfParser::convertValue(std::string& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = token.value;
}

template<> 
void CHndfParser::convertValue(u32& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtoul(token.value.c_str(), 0, 10);
}

template<> 
void CHndfParser::convertValue(i32& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtoul(token.value.c_str(), 0, 10);
}

template<> 
void CHndfParser::convertValue(bool& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = false;
	 
	if(token.value == "true" || token.value == "1") {
		val = true;
	} else if(token.value != "false" && token.value != "0") {
		error(HDF_ERR_WARNING, "invalid boolean value");
	}
}


void CHndfParser::skipObject() 
{
}



void CHndfParser::error(HdfParserMessage type, std::string msg)
{
	errors_.push_back(msg);
	printf("[HDF:%d]: %s\n",0,msg.c_str());
}

void CHndfParser::readDirective() {
	HdfToken token;
	
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


}
}