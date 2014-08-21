#ifndef __hrengin_CHndfParser_H__
#define __hrengin_CHndfParser_H__

#include <string>
#include <vector>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/filesystem/IHndfParser.h>


#include "HdfTypes.h"

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
	HDF_TOKEN_EOF = 0,
	HDF_TOKEN_NAME,
	HDF_TOKEN_NUMBER,
	HDF_TOKEN_STRING,
	HDF_TOKEN_WHITESPACE,
	HDF_TOKEN_COMMENT,
	HDF_TOKEN_OBJECT_BEGIN,
	HDF_TOKEN_OBJECT_END,
	HDF_TOKEN_SEPARATOR,
	HDF_TOKEN_TYPE_SEPARATOR,
	HDF_TOKEN_DIRECTIVE,
	HDF_TOKEN_ARRAY_ELEMENT,
	HDF_TOKEN_VALUE,
	HDF_TOKEN_INVALID
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
	
	template<typename T> 
	void readValue(T& val);


private:
	template<typename T> 
	void convertValue(T& val);


	void readToken(HdfToken& token);

	void readString(std::string& val);
	void readNumber(std::string& val);
	void readName(std::string& name, char stop = 0);

	void readValueName(std::string& name);
	void readTypeName(std::string& name);

	void fastForward();
	void skipLine();
	void skipWhitespace();

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

	void error(HdfParserMessage type, std::string msg);


	void readDirective();

	//void skipWhitespace();

	IBufferedStream* stream_;

	u32 depth_;
};



} //namespace io
} //namespace hrengin


#endif//__HRENGIN_FILESYSTEM_CHndfParser_H__