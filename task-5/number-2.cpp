#include <bitset>
#include <chrono>
#include <codecvt>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>

#include <boost/locale.hpp>



std::string convert_locale_to_utf(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

/*
bool is_little_endian_system() 
{
	char16_t test = 0x0102;
	return (reinterpret_cast < char * > (&test))[0] == 0x02;
}

std::u16string convert_utf8_to_utf16(const std::string & string) 
{
	static bool little_endian_system = is_little_endian_system();

	if (little_endian_system) 
	{
		std::wstring_convert < std::codecvt_utf8_utf32 < 
			char32_t, 0x10ffffU, std::codecvt_mode::little_endian > , char32_t > converter;
		return converter.from_bytes(string);
	}
	else 
	{
		std::wstring_convert < std::codecvt_utf8_utf16 < char16_t > , char16_t > converter;
		return converter.from_bytes(string);
	}
}
*/

char hashsh(char l)
{
    if(l == 'f') return 'a';
    if(l == ',') return 'b';
    //if(l == 'в') return 'v';
    //if(l == 'г') return 'g';
    //if(l == 'д') return 'd';
    //if(l == '') return '';
}


int main()
{
    //try
	{
    std::string string;
//    std::cout << "lala" << std::endl;
		std::cin >> string;

		std::cout << string << string.length() << std::endl;

		//std::cout << std::hex << 
		//	(static_cast < int > (string[0]) & 0xFF) << std::dec << std::endl;

		std::string u8string = convert_locale_to_utf(string);

	//	std::cout << std::hex << 
	//		(static_cast < int > (u8string[0]) & 0xFF) <<
	//		(static_cast < int > (u8string[1]) & 0xFF) << std::dec << std::endl;

	//	SetConsoleCP      (65001);
	//	SetConsoleOutputCP(65001);

	//	std::cout << u8string << ' ' << u8string.length() << std::endl;

	//	for (auto c : u8string)
	//	{
	//		std::cout << c << ' ';
	//	}

		std::cout << std::endl;
/*
		std::u16string u16string = 
			boost::locale::conv::utf_to_utf < char16_t, char > (u8string);

		for (auto c : u16string)
		{
			std::cout << c << ' ';
		}
			
		std::cout << std::endl;
*/
		std::u32string u32string1 = 
			boost::locale::conv::utf_to_utf < char32_t, char > (u8string);
		
        //std::u32string u32string2(u32string1.size());


		for (auto c : u32string1)
		{
			//std::cout << hashsh(c) << ' ';
            c = hashsh(c);
		}

		std::cout << std::endl;

        std::string u8string2 = 
			boost::locale::conv::utf_to_utf < char, char32_t > (u32string1);
		//**string = boost::locale::conv::utf_to_utf < char, char32_t > (u32string1);

		//std::cout << string << std::endl;

		//std::u16string u32string_cmp = u"������";

        std::string string2 = convert_utf_to_locale(u8string2);

		/*for (auto c : u32string_cmp)
		{
			std::cout << c << ' ';
		}

		std::cout << std::endl;
*/
		//std::cout << std::boolalpha << (u32string == u32string_cmp) << std::endl;

		//string = u8"��� ��������� UNICODE UTF-8! \x00AA \x00BB \x00CC \x00DD \x00EE \x00FF";

		std::cout << string << ' ' << string2.length() << std::endl;

		//string = convert_utf_to_locale(string);

		//system("chcp 1251");

		//std::cout << string << ' ' << string.length() << std::endl;
	}
	/*catch (const std::exception & exception)
	{
		std::cerr << "Exception: " << exception.what() << std::endl;

		return EXIT_FAILURE;
        }

*/
	system("pause");

	return EXIT_SUCCESS;
}