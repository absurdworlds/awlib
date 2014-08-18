#ifndef __HRENGIN_FILESYSTEM_CHndfParser_H__
#define __HRENGIN_FILESYSTEM_CHndfParser_H__

#include <string>
#include <vector>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/filesystem/IHndfParser.h>


namespace hrengin {
namespace io {

class IBufferedStream;



class CHndfParser : public IHndfParser
{
public:
	CHndfParser(IReadFile* file);
	~CHndfParser();

	virtual bool readObject();
	virtual void skipObject();
	virtual HndfObjectType getObjectType();
	virtual std::string getObjectName();

	virtual bool getStringValue(std::string& val);
	virtual bool getFloatValue(float& val);
	virtual bool getIntegerValue(int& val);
	virtual bool getBooleanValue(bool& val);

	virtual void addError(std::string error);
private:
	enum TokenType {
			TOKEN_EOF = 0,
			TOKEN_OBJECT_BEGIN,
			TOKEN_OBJECT_END,
			TOKEN_ARRAY_ELEMENT,
			TOKEN_LITERAL,
			TOKEN_NUMERIC,
			TOKEN_DIRECTIVE,
			TOKEN_STRING,
			TOKEN_COMMENT,
			TOKEN_SEPARATOR,
			TOKEN_TYPE_SEPARATOR,
			TOKEN_VALUE,
			TOKEN_INVALID,
	};

	struct Token {
		TokenType type;
		std::string value;
	};

	Token token_;

	void read();

	bool readObjectContents(Token& token);
	void readHead();
	bool readDirective(Token& token);
	void readToken(Token& token);

	void readLiteral(std::string& val);
	void readString (std::string& val);
	void readNumeric(std::string& val);
	void skipComment();
	void skipSeparators();
	//void skipWhitespace();


	enum VariableType
	{
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_STRING
	};

	IBufferedStream* stream_;

	HndfObjectType objectType_;
	std::string objectName_;
	std::string stringValue_;
	u32 level_;

	std::vector<std::string> errors_;

};


}
}


#endif//__HRENGIN_FILESYSTEM_CHndfParser_H__