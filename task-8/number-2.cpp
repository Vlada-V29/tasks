#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>
#include <mutex>

std::mutex g_mutex;

class Threads_Guard
{
public:

	explicit Threads_Guard(std::vector < std::thread > & threads) :
		m_threads(threads)
	{}

	Threads_Guard(Threads_Guard const &) = delete;

	Threads_Guard& operator=(Threads_Guard const &) = delete;

	~Threads_Guard() noexcept
	{
		try
		{
			for (std::size_t i = 0; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::vector < std::thread > & m_threads;
};


	
	
void Searcher(std::vector <std::size_t>& v, 
		std::string str, std::string str0, std::size_t start)
{
		const std::size_t length = str.length();
		
			for(std::size_t i = 0; (i < length); ++i)
			{	
				if(str.find(str0, i) != std::string::npos)
				{
					//std::cout << std::endl;
					std::size_t j = str.find(str0, i);
					//std::lock_guard < std::mutex > lock(mutex);
					g_mutex.lock();
					v.push_back(j + start);
					g_mutex.unlock();
					i = (j);
					
				}
				else{
					i += (length);
				}
			}
			
}

void parallel_find(std::vector<std::size_t>& v, std::string str, std::string str0)
{
	const std::size_t length = str.length();
	const std::size_t length0 = str0.length();

	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / num_threads;


	for(auto i = 1; i < num_threads; ++i)
	{
		std::string sub = str.substr(i*block_size - length0 + 2, 2*length0 - 2);
		std::size_t iter = sub.find(str0);
		if(iter != std::string::npos)
		{
			v.push_back(i*block_size - length0 + 2 + iter);
		}
	}

	std::vector < std::thread > threads(num_threads - 1);

	{
		Threads_Guard guard(threads);

		std::size_t start = 0;

		for (std::size_t i = 0; i < (num_threads - 1); ++i)
		{
			
			std::size_t end = start;
			end += block_size;

			threads[i] = std::thread(Searcher, 
			 	std::ref(v), str.substr(start, block_size), str0, i*block_size);
			//Searcher(v, str.substr(start, block_size), str0, i*block_size);
			start = end;
		}

	}

	
}

int main(int argc, char ** argv)
{
	std::string str ("AGTCCGTCAGCACGTACGCTACTGCTATCAGTACTGATAGCTGTACCCTGTTACGCGTGTCTGCGTGCGTG");
	//std::cout << "Enter your string: ";
	//std::cin >> str;

	std::string str0 ("GTC");
	//std::cout << "Enter your string to find: ";
	//std::cin >> str0;
	std::size_t lenght0 = str0.length();
	std::vector < std::size_t> v;
	
	parallel_find(std::ref(v), str, str0);
	
	if(!(v.empty()))
	{
		std::cout << "Indices: " << std::endl;
		for(auto i : v)
		{
			std::cout << (i) << "\t" << str.substr(i, lenght0) << std::endl;
		}		
	}
	
	system("pause");

	return EXIT_SUCCESS;
}
