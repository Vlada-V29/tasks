#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
//#include <future>
#include<chrono>
//#include <execution>

//#include <ppl.h>

//using namespace concurrency;
using namespace std;
void inc(int& n) {n+=5;}

struct Functor{
   int operator() (const int& n) {return n+5;}
};


template<class Func, typename Alg, typename T>
void time_of_sort1(T cont, Alg alg)//<class InputIt, class Func>)
{
    
    auto t_start1 = std::chrono::system_clock::now();
    
	auto ki = alg(std::begin(cont), std::end(cont), Func()); 
	
	auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<std::chrono::microseconds>(t_end1 - t_start1);
    std::cout << result1.count() << " mcs" << "\t\n";

}


template<class Func, typename Alg, typename T>
void time_of_sort2(T cont, T cont2, Alg alg)//<class InputIt, class Func>)
{
    
    auto t_start1 = std::chrono::system_clock::now();
    
	auto ki = alg(std::begin(cont), std::end(cont), std::begin(cont2), Func()); 
	
	auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<std::chrono::microseconds>(t_end1 - t_start1);
    std::cout << result1.count() << " mcs" << "\t\n";

}




int main(int argc, char ** argv)
{
	std::vector < int > v(100);
	std::iota(v.begin(), v.end(), 1);
    std::vector < int > v2(100);

    std::cout << "Let's look time " << std::endl;
	
    std::cout << "std::for_each " << std::endl;
	time_of_sort1<Functor >(v, std::for_each<std::vector<int>::const_iterator, Functor>);
	std::cout << "std::parallel_for_each " << std::endl;
    //time_of_sort<Functor >(v, std::for_each<std::execution::par, std::vector<int>::const_iterator, Functor>);
	//time_of_sort(v, inc, parallel_for_each);

    std::cout << std::endl;

    std::cout << "std::for_each " << std::endl;
	time_of_sort2<Functor >(v, v2, std::transform<std::vector<int>::const_iterator, 
        std::vector<int>::const_iterator, Functor>);
	std::cout << "std::parallel_for_each " << std::endl;
    //time_of_sort<Functor >(v, std::for_each<std::execution::par, std::vector<int>::const_iterator, Functor>);
	
    std::cout << std::endl;

    
    

    
	system("pause");

	return EXIT_SUCCESS;
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