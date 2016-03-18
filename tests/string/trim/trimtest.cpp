#include <cstring>
#include <iostream>
#include <aw/utility/string/trim.h>

int main()
{
	std::string str(" \t  a - b - c \t  ");
	auto isspace = [] (char c) {return std::isspace(c);};
	std::cout << ("|" + aw::string::ltrimmed(str, isspace)+"|")<< std::endl;
	std::cout << ("|" + aw::string::rtrimmed(str, isspace)+"|")<< std::endl;
	std::cout << ("|" + aw::string::trimmed(str, isspace) +"|")<< std::endl;
	std::cout << ("|" + aw::string::trim(str, isspace)    +"|")<< std::endl;
}
