#include <iostream>
#include <regex>
#include <string>
#include <algorithm>

int main(int argc, char ** argv)
{
	std::regex pattern(R"(\w+\@\w+\.\w+)");
    std::regex pattern_2(R"((\w+\.?\w+\@)(\w+\.\w+))");

    std::string data("kgfckhg dfgvhk@gvj.jhv jhnvljh.hgvfh@hfj.fjf vdjhfh bkj@fg.sg dfvjo @jn.kjn");
    std::string data_2;

    std::smatch matches;
    std::smatch matches_2;
	//for (std::string line; getline(data, line); )
	//{
    //std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	//std::sregex_iterator end;

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

	/*std::for_each(begin, end, [](const std::smatch & m)
	{
		std::cout << m[0] << " | "; 
	});
    std::cout << std::endl;
    */
	/*	if (std::regex_search(data, matches, pattern))
		{
			for (std::size_t i = 0; i < matches.size(); ++i)
			{
				std::cout << matches[i] << " | ";
			}

			std::cout << std::endl;
		}*/
	//}


    //std::regex_search(matches.str(), matches_2, pattern_2);
    
    /*std::copy(
		std::sregex_token_iterator(std::begin(matches.str()), 
            std::end(matches.str()), pattern_2, { -1 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));


*/
	system("pause");

	return EXIT_SUCCESS;
}