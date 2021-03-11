#include <iostream>
#include <iomanip>

#include <locale>
#include <sstream>



long double convert_us_to_locale(const long double & mon)
{
    const double DOLL = 70.0;
	return DOLL * mon * 100;
}

 
int main()
{
    long double mon = 0; 
    
    std::cout << "Please enter the price in dollars: ";
    std::cin >> mon;
    std::cout << std::endl;

    long double mon_loc = convert_us_to_locale(mon);

    std::ostringstream sout;
	sout.imbue(std::locale("ru_RU.utf8"));
    std::cout << "In rubbles it is ";
	sout << std::showbase << std::put_money(mon_loc, false) << std::endl;
	std::cout << sout.str() << std::endl;


    
    return 0;
 
}

