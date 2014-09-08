#ifndef _hrengin_CHDFParser_
#define _hrengin_CHDFParser_

#include <string>
#include <vector>

#include <hrengin/common/types.h>
#include <hrengin/core/hdf_value.h>
#include <hrengin/core/IHDFParser.h>

namespace hrengin {
namespace hdf {

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

enum HdfType {
	HDF_INTEGER,
	HDF_FLOAT,
	HDF_BOOLEAN,
	HDF_STRING,
	HDF_VECTOR2,
	HDF_VECTOR3,
	HDF_UNKNOWN_TYPE
};

class CHDFParser : public IHDFParser {
public:
	CHDFParser(io::ICharacterStream* stream);
	virtual ~CHDFParser();
	
	virtual void skipNode();
	virtual void skipValue();

	virtual bool read();

	virtual HdfObjectType getObjectType();
	virtual void getObjectName(std::string& name);
	
	virtual void readFloat(float& val);
	virtual void readFloat(double& val);
	virtual void readInt(u32& val);
	virtual void readInt(i32& val);
	virtual void readBool(bool& val);
	virtual void readString(std::string& val);
	virtual void readVector3d(Vector3d<f32>& val);

	void error(hdf::ParserMessage type, std::string msg);
private:
	template<typename T> 
	void readValue(T& val);
	template<typename T> 
	void convertValue(HdfToken& token, T& val);
	
	bool parseType(HdfToken& token);

	void readToken(HdfToken& token);

	void readStringToken(std::string& val);
	void readNumber(std::string& val);
	void readName(std::string& name, char stop = 0);

	void readValueName(std::string& name);
	void readTypeName(std::string& name);

	void fastForward();
	void skipLine();
	void skipWhitespace();
	void skipInlineWhitespace();
	//void skip(bool (*condition)(u8));
	template<bool (*condition)(u8)> 
	void skip();

	enum HdfParserState {
		HDF_S_IDLE = 0,
		HDF_S_OBJECT,
		HDF_S_NODE_BEGIN,
		HDF_S_CMD_BEGIN,
		HDF_S_VALUE_BEGIN,
		HDF_S_VALUE_DATA,
		HDF_S_PANIC
	} state_;

	std::vector<std::string> errors_;

	void processCommand();

	io::ICharacterStream* stream_;

	u32 depth_;
};

} //namespace io
} //namespace hrengin

#endif//_hrengin_CHDFParser_
