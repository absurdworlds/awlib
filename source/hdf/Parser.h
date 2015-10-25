/*
 * Copyright (C) 2014-2105  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_hdf_Parser_impl_
#define _awrts_hdf_Parser_impl_
#include <string>
#include <vector>

#include <awengine/hdf/Value.h>
#include <awengine/hdf/Parser.h>

namespace awrts {
namespace hdf {
namespace impl_ {
enum TokenType {
	HDF_TOKEN_NVALID,
	HDF_TOKEN_EOF,
	HDF_TOKEN_NAME,
	HDF_TOKEN_NUMBER,
	HDF_TOKEN_STRING,
};

struct Token {
	TokenType type;
	std::string value;
};

class Parser : public hdf::Parser {
public:
	Parser(io::InputStream* stream);
	virtual ~Parser();

	virtual void skipNode();
	virtual void skipValue();

	virtual bool read();

	virtual ObjectType getObjectType();
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
	void convertValue(Token& token, T& val);

	bool parseType(Token& token);

	void readToken(Token& token);

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
	template<bool (*condition)(char)> 
	void skip();

	enum class State {
		Idle = 0,
		Object,
		Node,
		Command,
		Value,
		Data,
		Panic
	} state;

	std::vector<std::string> errors;

	void processCommand();

	io::CharacterStream* stream;

	u32 depth;
};
} // namespace impl_
} // namespace io
} // namespace awrts
#endif//_awrts_hdf_Parser_impl_
