#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <execution>

using namespace std;

void inc(int& n) {n+=5;}

int main()
{
    std::vector <int> v1(100);
	std::iota(v1.begin(), v1.end(), 1);
    std::vector <int> v2(100);

    std::cout << "Let's look time " << std::endl;
    
    std::cout << std::endl;

    auto now = std::chrono::system_clock::now();
    for_each(v1.begin(), v1.end(), inc);
	auto end = std::chrono::system_clock::now();
	auto t11 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - now);
	std::cout << "std::for_each: " << t11.count() << " ns" << std::endl;

    now = std::chrono::system_clock::now();
    for_each(std::execution::par, v1.begin(), v1.end(), inc);
	end = std::chrono::system_clock::now();
	auto t12 = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	std::cout << "parallel_for_each: " << t12.count() << std::endl;

    std::cout << std::endl;

    now = std::chrono::system_clock::now();
    transform(v1.begin(), v1.end(), v2.begin(), inc);
	end = std::chrono::system_clock::now();
	auto t21 = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	std::cout << "std::transform: " << t21.count() << std::endl;

    now = std::chrono::system_clock::now();
    transform(std::execution::par, v1.begin(), v1.end(), v2.begin(), inc);
	end = std::chrono::system_clock::now();
	auto t22 = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	std::cout << "parallel_transform: " << t22.count() << std::endl;

    std::cout << std::endl;

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(v1), std::end(v1), rng);
    //auto rng = std::default_random_engine {};
    std::shuffle(std::begin(v2), std::end(v2), rng);

    now = std::chrono::system_clock::now();
    sort(v1.begin(), v1.end());
	end = std::chrono::system_clock::now();
	auto t31 = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	std::cout << "std::sort: " << t31.count() << std::endl;

    now = std::chrono::system_clock::now(); 
    sort(std::execution::par, v2.begin(), v2.end());
	end = std::chrono::system_clock::now();
	auto t32 = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	std::cout << "parallel_sort: " << t32.count() << std::endl;

    return 0;
}
