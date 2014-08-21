
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
: level_(0)
{
	stream_ = createBufferedStream(file);
	
	readHead();
}

CHndfParser::~CHndfParser()
{
	delete stream_;
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
	
	parseValue<T>(T& var);
}

template<typename T> 
void CHndfParser::parseValue(T& val)
{
	// should never get this error
	error(HDF_EL_ERROR, "unknown type");
}

template<> 
void CHndfParser::parseValue(float& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtof(token_.value.c_str(), 0);
}

template<> 
void CHndfParser::parseValue(double& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtod(token_.value.c_str(), 0);
}

template<> 
void CHndfParser::parseValue(Vector3d& val)
{
	HdfToken token;
	
	// would look nicer:
	// repeat 3 {
	readToken(token);
	
	val.x = strtod(token_.value.c_str(), 0);
	//}
	
	readToken(token);
	
	val.y = strtod(token_.value.c_str(), 0);
	
	readToken(token);
	
	val.z = strtod(token_.value.c_str(), 0);
}

template<> 
void CHndfParser::parseValue(std::string& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = token.value;
}

template<> 
void CHndfParser::parseValue(u32& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtoul(token_.value.c_str(), 0);
}

template<> 
void CHndfParser::parseValue(i32& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = strtoul(token_.value.c_str(), 0);
}

template<> 
void CHndfParser::parseValue(bool& val)
{
	HdfToken token;
	
	readToken(token);
	
	val = false;
	 
	if(token.value == "true" || token.value == "1") {
		val = true;
	} else if(token.value != "false" && token.value != "0") {
		error(HDF_EL_WARNING, "invalid boolean value");
	}
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
				//token.type = TOKEN_COMMENT;
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


void CHndfParser::readToken(HdfToken& token)
{
	fastForward();

	char c;

	stream_->getCurrent(c);

	if(isNameBeginChar(c)) {
	
	} else if(c == '-' || (c > '0' && c < '9')) {
		
	} else if(c == '"') {
	
	} else if() {

	}
}


std::string CHndfParser::getObjectName()
{
	return objectName_;
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
		state_ = HDF_S_IDLE;
		readNodeName(name);
	} else if(state_ == HDF_S_VALUE_BEGIN) {
		state_ = HDF_S_VALUE_DATA;
		readValueName(name);
	}

	error(HDF_ERR_ERROR, "must be called after getObjectType()");
}

inline CHndfParser::readNodeName(std::string& name)
{
	char c;

	stream_->getCurrent(c);

	while(!isWhitespace(c)) {
		if(isNameChar(c)) {
			name += c;
		} else {
			error(HDF_ERR_WARNING, "invalid name char");
		}
		stream_->getNext(c);
	}
}

inline CHndfParser::readValueName(std::string& name)
{
	char c;

	stream_->getCurrent(c);

	// c == '=': make sure we don't 'eat' the '=' as it was in previous version
	while(!(isInlineWhitespace(c) || c == '=')) {
		if(isNameChar(c)) {
			name += c;
		} else {
			error(HDF_ERR_WARNING, "invalid name char");
		}
		stream_->getNext(c);
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

bool CHndfParser::readDirective(Token& token) {
	if(token.type != TOKEN_DIRECTIVE) {
		addError("unexpected token");
		return false;
	}

	readToken(token);

	if(token.type != TOKEN_LITERAL) {
		addError("expected directive name");
		return false;
	}
	
	if (token.value == "hndf_version") {
		readToken(token);
		if(token.type != TOKEN_STRING) {
			addError("expected version number");
			return false;
		} else if(token.value != "1.1") {
			addError("your version is bullshit!");
			return false;
		}
	} else {
		addError("unknown directive");
		return false;
	}
		
	return true;
}




void CHndfParser::readString(std::string& val) {
	char c = readChar();
	
	while (c != '"') {
		if ( c == '\\' ) {
			c = readChar();
		}
		val += c;
		c = readChar();
	}
}

void CHndfParser::readNumeric(std::string& val)
{
	char c  = readChar();
	//bool e_encountered;
	//bool m_encountered;
	
	while (c != '\n' && c != ' ' && c != ';') {
		if (!(c >= '0' && c <= '9') && !cmp5(c, '.', 'e', 'E', '+', '-' )) {
			c = readChar();
			break;
		}
		val += c;
		c = readChar();
	}
}


}
}