#include <aw/utility/unicode/convert.h>


#include <iostream>
int main()
{
	std::string utf8 = u8"I am an unicode string å — °o АБВ αβγ Δ";
	std::u16string utf16 = aw::unicode::widen(utf8);

	for (char16_t ch : utf16)
		std::cout << ch << "\n";

	std::string utf8_2 = aw::unicode::narrow(utf16);
	std::cout << utf8 << "\n";
	std::cout << utf8_2 << "\n";
}
