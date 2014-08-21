#ifndef __hrengin_CHndfParser_H__
#define __hrengin_CHndfParser_H__

#include <string>
#include <vector>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/filesystem/IHndfParser.h>


namespace hrengin {
namespace io {

class IReadFile;
class IBufferedStream;

/* 
 * Most of those are legacy values, only few are actually used
 * Probably should clean up, unless is decided to make parser backward-compatible
 *
 */
enum HdfTokenType {
	TOKEN_EOF = 0,
	TOKEN_NAME,
	TOKEN_NUMBER,
	TOKEN_STRING,
	TOKEN_WHITESPACE,
	TOKEN_COMMENT,
	TOKEN_OBJECT_BEGIN,
	TOKEN_OBJECT_END,
	TOKEN_SEPARATOR,
	TOKEN_TYPE_SEPARATOR,
	TOKEN_DIRECTIVE,
	TOKEN_ARRAY_ELEMENT,
	TOKEN_VALUE,
	TOKEN_INVALID
};


struct HdfToken {
	HdfTokenType type;
	std::string value;
};


class CHndfParser : public IHndfParser
{
public:
	CHndfParser(IReadFile* file);
	~CHndfParser();

	virtual bool read();
	virtual void skipObject();
	virtual HdfObjectType getObjectType();
	virtual void getObjectName(std::string& name);

	virtual bool getStringValue(std::string& val);
	virtual bool getFloatValue(float& val);
	virtual bool getIntegerValue(int& val);
	virtual bool getBooleanValue(bool& val);
private:
	virtual void readNodeName(std::string& name);
	virtual void readValueName(std::string& name);

	enum HdfParserState {
		HDF_S_IDLE = 0,
		HDF_S_OBJECT,
		HDF_S_NODE_BEGIN,
		HDF_S_CMD_BEGIN,
		HDF_S_VALUE_BEGIN,
		HDF_S_VALUE_DATA,
		HDF_S_PANIC
	} state_;
	
	enum HdfParserMessage {
		HDF_ERR_NOTICE,
		HDF_ERR_WARNING,
		HDF_ERR_ERROR
	};
	
	std::vector<std::string> errors_;

	virtual void error(HdfParserMessage type, std::string msg);

	void fastForward();
	void skipLine();
	void skipWhitespace();

	bool readObjectContents(Token& token);
	void readHead();
	bool readDirective(Token& token);
	void readToken(Token& token);

	void readLiteral(std::string& val);
	void readString (std::string& val);
	void readNumeric(std::string& val);

	//void skipWhitespace();

	IBufferedStream* stream_;

	u32 depth_;
};


}
}


#endif//__HRENGIN_FILESYSTEM_CHndfParser_H__