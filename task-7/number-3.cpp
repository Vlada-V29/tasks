#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <future>


void inc(int& n) {n+=5;}
	
template < typename Iterator, class Compare >
int parallel_each(Iterator first, Iterator last, Compare fun)
{
    const std::size_t length = std::distance(first, last);
    const std::size_t max_size = 25;

    if (length <= max_size)
	{
		std::for_each(first, last, fun);
	}
    else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < int > first_half_result =
			std::async(parallel_each < Iterator, Compare >, first, middle, fun);

		int second_half_result = parallel_each(middle, last, fun);

		int a = first_half_result.get() + second_half_result;
	}

    return 0;

}

int main(int argc, char ** argv)
{
	std::vector < int > v(100);
	std::iota(v.begin(), v.end(), 1);

    std::cout << "before std::for_each:" << std::endl;
    for(auto i = 0; i < 100; i += 10)
    {
        std::cout << "v[" << i << "] = " << v[i]   << std::endl;
	
    }
    
    parallel_each(v.begin(), v.end(), inc);
    std::cout << "\nafter std::for_each:" << std::endl;
    for(auto i = 0; i < 100; i += 10)
    {
        std::cout << "v[" << i << "] = " << v[i]   << std::endl;
	
    }
    
	system("pause");

	return EXIT_SUCCESS;
}