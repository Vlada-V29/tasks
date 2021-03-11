#include <iostream>
#include <regex>
#include <string>
#include <algorithm>

int main(int argc, char ** argv)
{
	std::regex pattern1(R"((([0-2][0-9])|([3][1]))\.(([0][1-9])|([1][0-2]))\.[0-9][0-9][0-9][0-9])"); //)");
    std::regex pattern2(R"((([0][0-9])|([1][0-2]))\:[0-6][1-9]\:[0-6][1-9])");

    std::string data("kgfckhg 87.233.2397 31.12.2867 dfgvhk@gvj.jhv  02.05.2867  jhnvljh.hgvfh@hfj.fjf 02:03:45 vdjhfh    bkj@fg.sg dfvjo @jn.kjn");
    

    std::sregex_token_iterator pos1 (data.cbegin(), data.cend(), pattern1, {0});
    std::sregex_token_iterator end1;
    std::sregex_token_iterator pos2 (data.cbegin(), data.cend(), pattern2, {0});
    std::sregex_token_iterator end2;

    std::cout << "Data:"<< std::endl; 
    for(; pos1 != end1; ++pos1)
    {
        std::cout << pos1->str() << " | " ;
        //++pos2;
    }
    std::cout << "\n" << std::endl;

    std::cout << "Time:"<< std::endl; 
    for(; pos2 != end2; ++pos2)
    {
        std::cout << pos2->str() << " | " ;
        //++pos2;
    }
    std::cout << std::endl;

	
	system("pause");

	return EXIT_SUCCESS;
}