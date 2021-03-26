#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
//#include <future>
#include<chrono>
//#include <ppl.h>

//using namespace concurrency;
using namespace std;
void inc(int& n) {n+=5;}




template<typename T, class Func, class Alg>
void time_of_sort(T cont, Func fun, Alg alg)
{
    
    auto t_start1 = std::chrono::system_clock::now();
    
	auto ki = alg(std::begin(cont), std::end(cont), fun); 
	
	auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<std::chrono::microseconds>(t_end1 - t_start1);
    std::cout << result1.count() << " mcs" << "\t\n";

}

/*template<typename T, class Func, class Alg>
void time_of_sort_par(T cont, Func fun, Alg alg)
{
    
    auto t_start1 = std::chrono::system_clock::now();
    
	auto ki = alg(std::begin(cont), std::end(cont), fun); std::execution::par, 
	
	auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<std::chrono::microseconds>(t_end1 - t_start1);
    std::cout << result1.count() << " mcs" << "\t\n";

}
*/
int main(int argc, char ** argv)
{
	std::vector < int > v(100);
	std::iota(v.begin(), v.end(), 1);

    std::cout << "Let's look time " << std::endl;
	
    std::cout << "std::for_each " << std::endl;
    //auto *fe = std::for_each;
	time_of_sort(v, inc, for_each);
	std::cout << "std::parallel_for_each " << std::endl;
	//time_of_sort(v, inc, parallel_for_each);


    
	system("pause");

	return EXIT_SUCCESS;
}

