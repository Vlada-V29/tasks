#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>
#include <mutex>

//std::mutex g_mutex;

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

//template < typename Iterator, typename T >
//struct Searcher
//{	
	
	
	void Searcher(std::vector <std::string::iterator>& v, std::string str, std::string str0, //T element,
		std::promise < std::string::iterator > & result, std::atomic < bool > & flag) noexcept

	{
		using Iterator = std::string::iterator;
		const std::size_t length = str.length();
		Iterator first = str.begin();
		Iterator last = str.end();
		try
		{
			for(auto i = 0; (i < length); ++i)
			{	
				if(str.find(str0, i))
				{
					i = str.find(str0);
					//std::lock_guard < std::mutex > lock(mutex);
					v.push_back(first + i);
					
				}
				else{
					i += length;
				}
			}
			/*for (; (first != last) && !flag.load(); ++first)
			{
				if (*first == element)
				{
					result.set_value(first);
					flag.store(true);
					return;
				}
			}*/
		}
		catch (...)
		{
			try
			{
				result.set_exception(std::current_exception());
				flag.store(true);
			}
			catch (...)
			{
				// ...
			}
		}
	}
//};

//template < typename Iterator, typename T >
void parallel_find(std::vector<std::string::iterator>& v, std::string str, std::string str0)
{
	using Iterator = std::string::iterator;
	Iterator first = str.begin();
	Iterator last = str.end();
	const std::size_t length = str.length();
	const std::size_t length0 = str0.length();

	//if (!length)
		//return 0;//??????????????

	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / num_threads;


	for(auto i = 0; i < num_threads; ++i)
	{
		std::string sub = str.substr(i*block_size - length0 + 2, block_size + 2);
		if(sub == str0)
		{
			//
			v.push_back(first + i*block_size - length0 + 2);
		}
	}

	std::promise < Iterator > result;
	std::atomic < bool > flag(false);
	std::vector < std::thread > threads(num_threads - 1);

	{
		Threads_Guard guard(threads);

		Iterator block_start = first;
		std::size_t start = 0;

		for (std::size_t i = 0; i < (num_threads - 1); ++i)
		{
			Iterator block_end = block_start;
			std::size_t end = start;
			std::advance(block_end, block_size);
			std::advance(end, block_size);


			threads[i] = std::thread(Searcher, //< Iterator > (),
				v, str.substr(start, end), str0,
				//block_start, block_end, element, 
				std::ref(result), std::ref(flag));

			block_start = block_end;
			start = end;
		}

		Searcher(v, str.substr(start, length), str0,
				std::ref(result), std::ref(flag));
        //Searcher();
				//< Iterator, T > ()(block_start, last, element, result, flag);
	}

	if (!flag.load())
	{
		//return last;
	}

	//return result.get_future().get();
}

int main(int argc, char ** argv)
{
	//std::vector < int > v(100);

	//std::iota(v.begin(), v.end(), 1);

	std::string str ("chjbv;iigdcsdc");
	std::string str0 = "gdcs";
	std::vector < std::string::iterator > v;
	//auto result = parallel_find(v, str, str0);

/*
	if (result != v.end())
	{
		std::cout << "Element found: " << *result << std::endl;
	}
	else
	{
		std::cout << "Element not found." << std::endl;
	}
*/
	system("pause");

	return EXIT_SUCCESS;
}
