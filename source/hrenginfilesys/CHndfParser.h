#ifndef __HRENGIN_FILESYSTEM_CHndfParser_H__
#define __HRENGIN_FILESYSTEM_CHndfParser_H__

#include <string>
#include <map>

//#include <hrengin/filesystem/IFileParser.h>

namespace hrengin {
namespace io {

class IReadFile;

enum EHndfType {
	HNDF_INT,
	HNDF_STRING
};

class CHndfParser// : public IFileParser
{
public:
	bool parse(IReadFile& file);

	float getFloat(std::string key);
	std::string getString(std::string key);
private:
	std::string readToken();


	enum EHndfState {
		HNDF_START,
		HNDF_OPEN_BRACE,
		HNDF_CLOSE_BRACE,
		HNDF_COLON,
		HNDF_SEMICOLON,
		HNDF_ASTERISK,
		HNDF_NAME,
		HNDF_TYPE,
		HNDF_VALUE
	};
};


}
}


#endif//__HRENGIN_FILESYSTEM_CHndfParser_H__