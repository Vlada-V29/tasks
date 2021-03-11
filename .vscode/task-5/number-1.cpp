#include <iostream>
#include <iomanip>

#include <locale>
#include <sstream>

//#include <boost/locale.hpp>



long double convert_us_to_locale(const long double & mon)
{
    const double DOLL = 70.0;
	return DOLL * mon * 100;
}

 
int main()
{
    long double mon = 0;//123.45; 
    
    //std::cin.imbue(std::locale("en_US.UTF-8"));
    std::cout << "Please enter the price in dollars: ";
    //std::cin >> std::get_money(mon, true);
    std::cin >> mon;
    std::cout << std::endl;

    /*std::ostringstream sout0;
	sout0.imbue(std::locale("en_US.utf8"));
    std::cout << "Your value is ";
    sout0 << std::showbase << std::put_money(mon, false) << std::endl;
	std::cout << sout0.str() << std::endl;
  */
    long double mon_loc = convert_us_to_locale(mon);

    std::ostringstream sout;
	sout.imbue(std::locale("ru_RU.utf8"));
    std::cout << "In rubbles it is ";
	sout << std::showbase << std::put_money(mon_loc, false) << std::endl;
	std::cout << sout.str() << std::endl;


    
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