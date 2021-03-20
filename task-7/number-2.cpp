#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
// #include<algorithm>
#include<chrono>


template < typename Iterator, typename T >
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T & result)
	{
		result = std::accumulate(first, last, result); // !
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, const int n)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	// const std::size_t min_per_thread = 25;
	// const std::size_t max_threads =
		// (length + min_per_thread - 1) / min_per_thread;

	// const std::size_t hardware_threads =
	// 	std::thread::hardware_concurrency();

	// const std::size_t num_threads =
	// 	std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / n;

	std::vector < T > results(n);
	std::vector < std::thread > th(n);// - 1);

	Iterator block_start = first;

	for (std::size_t i = 0; i < n; ++i)//(num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		th[i] = std::thread(
			accumulate_block < Iterator, T > (),
			block_start, block_end, std::ref(results[i])); // !

		block_start = block_end;
	}

	accumulate_block < Iterator, T > ()(block_start, last, results[n - 1]);

	// std::for_each(threads.begin(), threads.end(),
	// 	std::mem_fn(&std::thread::join));
    for(int i = 0; i < n; ++i)
    {
        th[i].join();
    }

	return std::accumulate(results.begin(), results.end(), init);
	//std::cout <<  << std::endl;
}

template<typename T>
void time_of_sort1(T cont, int n)
{
    
    auto t_start1 = std::chrono::system_clock::now();
    // sort(std::begin(cont), std::end(cont));
    //std::cout << 
	auto ki = parallel_accumulate(cont.begin(), cont.end(), 0, n); 
	//<< std::endl;
    auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<std::chrono::microseconds>(t_end1 - t_start1);
    std::cout << result1.count() << " mcs" << "\t\n";

}


int main(int argc, char ** argv)
{
	std::vector < int > v(100);
	std::iota(v.begin(), v.end(), 1);

    int n = 0;
    std::cout << "Enter number: ";// << std::endl;
    std::cin >> n;
	/*for(int i = 1; i <= 10; ++i)
	{
		std::cout << i << "\t";
		time_of_sort1(v, i);
	}*/
	time_of_sort1(v, n);
	// std::cout << parallel_accumulate(v.begin(), v.end(), 0, n) << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}