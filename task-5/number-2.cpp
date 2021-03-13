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


char hashsh(char l)
{
    if(l == 'а') return 'a';
    if(l == 'б') return 'b';
    if(l == 'в') return 'v';
    if(l == 'г') return 'g';
    if(l == 'д') return 'd';
	if(l == 'е') return 'e';
	if(l == 'ж') return 'z';
	if(l == 'з') return 'z';
	if(l == 'и') return 'i';
	if(l == 'й') return 'i';
	if(l == 'к') return 'k';
	if(l == 'л') return 'l';
	if(l == 'м') return 'm';
	if(l == 'н') return 'n';
	if(l == 'о') return 'o';
	if(l == 'п') return 'p';
	if(l == 'р') return 'r';
	if(l == 'с') return 's';
	if(l == 'т') return 't';
	if(l == 'у') return 'u';
	if(l == 'ф') return 'f';
	if(l == 'х') return 'h';
	if(l == 'ц') return 'c';
	if(l == 'ч') return 'c';
	if(l == 'ш') return 's';
	if(l == 'щ') return 's';
	if(l == 'ы') return 'i';
	if(l == 'э') return 'a';
	if(l == 'ю') return 'u';
	if(l == 'я') return 'a';
    //if(l == '') return '';
}


int main()
{
    std::string string;
	std::cin >> string;

	std::cout << string << " " << string.length() << std::endl;

	std::string u8string = convert_locale_to_utf(string);

	//	SetConsoleCP      (65001);
	//	SetConsoleOutputCP(65001);

	std::cout << std::endl;

	std::u32string u32string1 = 
		boost::locale::conv::utf_to_utf < char32_t, char > (u8string);
		
    for (auto c : u32string1)
	{
		c = hashsh(c);
	}
    std::cout << std::endl;

    
    std::string u8string2 = 
		boost::locale::conv::utf_to_utf < char, char32_t > (u32string1);
	

    std::string string2 = convert_utf_to_locale(u8string2);

		//system("chcp 1251");
	std::cout << string << ' ' << string2.length() << std::endl;

	
		
	system("pause");

	return EXIT_SUCCESS;
}