
#include <hrengin/filesystem/IReadFile.h>

#include "CHndfParser.h"

namespace hrengin {
namespace io {

IHndfParser* createHndfParser(IReadFile* file)
{
	if(!file->isOpen()) {
		return 0;
	}

	return new CHndfParser(file);
}

CHndfParser::CHndfParser(IReadFile* file)
: file_(file), pos_(0), level_(0)
{
	buffer_ = new char[1024];
	file_->read(buffer_, 1024);
	
	readHead();

}

CHndfParser::~CHndfParser()
{
	delete[] buffer_;
}


bool CHndfParser::readObject() 
{
	Token token;

	do {
		readToken(token);
	} while(token.type == TOKEN_SEPARATOR);

	if(token.type == TOKEN_OBJECT_BEGIN) {
		if(token.type == TOKEN_LITERAL) {
			objectName_ = token.value;
			objectType_ = HNDF_NODE;
			level_ ++;
			return true;
		} else if(token.type == TOKEN_ARRAY_ELEMENT || token.type == TOKEN_SEPARATOR) {
			objectName_ = "*";
			objectType_ = HNDF_NODE;
			level_ ++;
			return true;
		} else {
			addError("expected node name");
			return false;
		}
	} else if (level_ == 0) {
		addError("expected node");
		return false;
	}
	
	if(token.type == TOKEN_OBJECT_END) {
		if (level_ == 0) {
			addError("extra closing bracket");
		} else {
			level_--;
		}
		return false;
	}
	
	if(token.type == TOKEN_LITERAL) {
		objectName_ = token.value;
		objectType_ = HNDF_VARIABLE;

		readToken(token);

		if(token.type != TOKEN_VALUE) {
			addError("expected value");
			return false;
		}

		return true;
	}

	return false;
}


void CHndfParser::skipObject() 
{
	Token token;

	do {
		readToken(token);
	} while(token.type == TOKEN_SEPARATOR);

	if(objectType_ == HNDF_VARIABLE) {
		do {
			readToken(token);
		} while(token.type != TOKEN_SEPARATOR);
	} else {
		/*if(token.type != TOKEN_OBJECT_BEGIN) {
			return;
		}*/
	
		do {
			readToken(token);
		} while(token.type != TOKEN_OBJECT_END);
	
	
		level_--;
	}
}

bool CHndfParser::getStringValue(std::string& val)
{
	Token token;
	readToken(token);
	
	if(token.type == TOKEN_STRING) {
		val = token.value;
		return true;
	} 
	
	if (token.type != TOKEN_LITERAL) {
		addError("expected value or type");
		return false;
	}
	
	stringValue_ = token.value;
	readToken(token);

	if(token.type == TOKEN_SEPARATOR) {
		val = stringValue_;
		return true;
	} else if(token.type == TOKEN_TYPE_SEPARATOR && stringValue_ != "string") {
		addError("expected string value");
		return false;
	} else if(token.type == TOKEN_LITERAL) {
		do {
			stringValue_ += " " + token.value;
			readToken(token);
		} while (token.type != TOKEN_SEPARATOR);
		val = stringValue_;
		return true;
	}
			
	readToken(token);

	if(token.type == TOKEN_LITERAL) {
		stringValue_ = "";
		do {
			stringValue_ += " " + token.value;
			readToken(token);
		} while (token.type != TOKEN_SEPARATOR);
		val = stringValue_;
		return true;
	} else if(token.type == TOKEN_STRING) {
		val = token.value;
		return true;
	} else if(token.type == TOKEN_NUMERIC) {
		val = token.value;
		return true;
	}
	
	addError("expected string value");
	return false;
}

bool CHndfParser::getFloatValue(float& val)
{
	Token token;
	readToken(token);

	if (token.type != TOKEN_LITERAL) {
		addError("expected type");
		return false;

	}

	if(token.value != "float") {
		addError("expeted float");
		return false;
	}

	readToken(token);
	
	if (token.type != TOKEN_TYPE_SEPARATOR) {
		addError("expected ':'");
		return false;
	}
	
	readToken(token);

	if (token.type != TOKEN_NUMERIC) {
		addError("expected numeric value");
		return false;
	}

	val = strtof(token.value.c_str(), 0);
	return true;
}

bool CHndfParser::getIntegerValue(int& val)
{
	Token token;
	readToken(token);

	if (token.type != TOKEN_LITERAL) {
		addError("expected type");
		return false;

	}

	if(token.value != "int") {
		addError("expeted integer");
		return false;
	}

	readToken(token);
	
	if (token.type != TOKEN_TYPE_SEPARATOR) {
		addError("expected ':'");
		return false;
	}
	
	readToken(token);

	if (token.type != TOKEN_NUMERIC) {
		addError("expected numeric value");
		return false;
	}

	val = strtol(token.value.c_str(), 0, 0);
	return true;
}

std::string CHndfParser::getObjectName()
{
	return objectName_;
}

HndfObjectType CHndfParser::getObjectType()
{
	return objectType_;
}


bool CHndfParser::getBooleanValue(bool& val)
{
	return false;
}


void CHndfParser::addError(std::string error)
{
	errors_.push_back(error);
	printf("HNDF: %s\n",error.c_str());
}

char CHndfParser::readChar()
{
	char c = buffer_[pos_ % 1024];

	pos_++;
	
	if((pos_) == file_->getSize()) {
		return 0;
	}

	if(pos_ % 1024 == 0) {
		file_->read(buffer_, 1024);
	}

	return c;
}

char CHndfParser::peekChar()
{
	if((pos_ + 1) % 1024 == 0) {
		char tmp;
		file_->read(&tmp, 1);
		return tmp;
	}

	if((pos_ + 1) == file_->getSize()) {
		return 0;
	}
	
	//return *(buffer_ + ((pos_ + 1) % 1024));
	return buffer_[(pos_ + 1) % 1024];
}

void CHndfParser::readHead()
{
	Token token;
	readToken(token);
	
	while(token.type != TOKEN_OBJECT_BEGIN) {
		if(token.type == TOKEN_EOF) {
			addError("unexpected end of stream");
			return;
		}
		readDirective(token);
		readToken(token);
	}
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

void CHndfParser::readToken(CHndfParser::Token& token) {
	char c;

	do {
		c = readChar();
	} while (c == ' ' || c == '\t');

	if(c == '[') {
		token.type = TOKEN_OBJECT_BEGIN;
	} else if(c == ']') {
		token.type = TOKEN_OBJECT_END;
	} else if(c == '!') {
		token.type = TOKEN_DIRECTIVE;
	} else if(c == '*') {
		token.type = TOKEN_ARRAY_ELEMENT;
	} else if(c == ':') {
		token.type = TOKEN_TYPE_SEPARATOR;
	} else if(c == '\n' || c == ';') {
		token.type = TOKEN_SEPARATOR;
	} else if((c > 'a' && c < 'z') || (c > 'A' && c < 'Z')) {
		token.type = TOKEN_LITERAL;
		token.value += c;
		readLiteral(token.value);
	} else if(c == '"') {
		token.type = TOKEN_STRING;
		token.value += c;
		readString(token.value);
	} else if(c == '=') {
		token.type = TOKEN_VALUE;
	} else if(c == '-' || (c > '0' && c < '9')) {
		token.type = TOKEN_NUMERIC;
		token.value += c;
		readNumeric(token.value);
	} else if(c == '/') {
		if(peekChar() == '/') {
			token.type = TOKEN_COMMENT;
			skipComment();
		}
	} else if (c == 0) {
		token.type = TOKEN_EOF;
	} else {
		token.type = TOKEN_INVALID;
		//success = false;
	}
}

void CHndfParser::readLiteral(std::string val) {
	char c = readChar();
	
	while (c == '_' || (c > 'a' && c < 'z') || (c > 'A' && c < 'Z'))
	{
		c = readChar();
		val += c;
	}
}

void CHndfParser::readString(std::string val) {
	char c = readChar();
	
	while (c != '"') {
		c = readChar();
		if ( c == '\\' ) {
			c = readChar();
		}
		val += c;
	}
}


inline bool cmp4(char c, char c1, char c2, char c3, char c4)
{
	return c == c1  ||  c == c2  ||  c == c3  ||  c == c4;
}

inline bool cmp5(char c, char c1, char c2, char c3, char c4, char c5)
{
	return c == c1  ||  c == c2  ||  c == c3  ||  c == c4  ||  c == c5;
}

void CHndfParser::readNumeric(std::string val)
{
	char c  = readChar();
	//bool e_encountered;
	//bool m_encountered;
	
	while (c != '\n' && c != ' ' && c != ';') {
		c = readChar();
		if (!(c >= '0' && c <= '9') && !cmp5(c, '.', 'e', 'E', '+', '-' )) {
			break;
		}
		val += c;
	}
}

void CHndfParser::skipComment()
{
	char c;
	
	do {
		c = readChar();
	} while (c != '\n' && c != ' ' && c != ';');
}

}
}