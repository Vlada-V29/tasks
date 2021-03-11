#include <iostream>
#include <iomanip>

#include <boost/locale.hpp>



long double convert_us_to_locale(const long double & mon)
{
    const double DOLL = 70.0;
	return DOLL * mon;
}

 
int main()
{
    long double mon = 0;//123.45; 
    std::cin.imbue(std::locale("en_US.UTF-8"));
    std::cout << "Please enter the price in dollars: ";
    std::cin >> std::get_money(mon, true);
  
    long double mon_loc = convert_us_to_locale(mon);

    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase << "ru_RU: " 
            << std::put_money(mon) << '\n';

    
    return 0;
 
}


/*std::string convert_us_to_locale(const std::string & string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_us?????????????????? ;
}
*/