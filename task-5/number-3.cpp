#include <iostream>
#include <regex>
#include <string>
#include <algorithm>

int main(int argc, char ** argv)
{
	std::regex pattern(R"(\w+\@\w+\.\w+)");
    std::regex pattern_2(R"((\w+\.?\w+\@)(\w+\.\w+))");

    std::string data("kgfckhg dfgvhk@gvj.jhv    jhnvljh.hgvfh@hfj.fjf vdjhfh    bkj@fg.sg dfvjo @jn.kjn");
    

    std::sregex_token_iterator pos0 (data.cbegin(), data.cend(), pattern_2, {0});
    std::sregex_token_iterator end0;
    std::sregex_token_iterator pos2 (data.cbegin(), data.cend(), pattern_2, {2});
    std::sregex_token_iterator end2;
    std::cout << "Emails & domens:"<< std::endl; 
    for(; pos0 != end0; ++pos0)
    {
        std::cout << pos0->str() << " | " << pos2->str() << std::endl;
        ++pos2;
    }
    std::cout << std::endl;

	
	system("pause");

	return EXIT_SUCCESS;
}