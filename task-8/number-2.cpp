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
	
	
	void Searcher(std::vector <std::size_t>& v, 
		std::string str, std::string str0)//, //T element,
		//std::promise < std::string::iterator > & result, std::atomic < bool > & flag) noexcept
		
	{
		std::cout<<&v<<std::endl;
		//using Iterator = std::string::iterator;
		const std::size_t length = str.length();
		//Iterator first = str.begin();
		//Iterator last = str.end();
		//try
		//{
			for(std::size_t i = 1; (i <= length); ++i)
			{	
				if(str.find(str0, i) != std::string::npos)
				{
					std::cout << std::endl;
					//std::cout << i << std::endl;
					std::size_t j = str.find(str0, i);
					//std::cout << str.find(str0,i) << std::endl;
					//std::lock_guard < std::mutex > lock(mutex);
					//Iterator ferst = first;
					// for(auto ki = 0; ki < j; ++ki){
					// 	ferst++;
					// }
					//std::cout << *ferst << std::endl;
					v.push_back(j);
					//std::cout << *(v[v.size()-1]) << std::endl;
					i = (j);
					//std::cout << i << std::endl;
					
				}
				else{
					i += (length);
				}
			}
			std::cout << std::endl;
			v.push_back(100);
			/*for(auto i : v)
		{
			std::cout << i << std::endl;
		}*/
			//std::cout<<&v<<std::endl;

		std::cout << std::endl;
			/*for (; (first != last) && !flag.load(); ++first)
			{
				if (*first == element)
				{
					result.set_value(first);
					flag.store(true);
					return;
				}
			}*/
		//}
		/*
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
		}*/
	//return v;
	}
//};

//template < typename Iterator, typename T >
/*void parallel_find(std::vector<std::string::iterator>& v, std::string str, std::string str0)
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


	for(auto i = 1; i < num_threads; ++i)
	{
		//for(auto i = )
		//00  std::string sub = str.substr(i*block_size - length0 + 2, i*block_size + length0 - 2);
		std::string sub = str.substr(i*block_size - length0, i*block_size + length0);
		std::size_t iter = sub.find(str0);
		if(iter != std::string::npos)
		{
			//
			//v.push_back(first + i*block_size - length0 + 2);
			v.push_back(first + iter);//static_cast<Iterator>(iter));
		}
	}

	//std::promise < Iterator > result;
	//std::atomic < bool > flag(false);
	//00 std::vector < std::thread > threads(num_threads - 1);

	{
		//00Threads_Guard guard(threads);

		Iterator block_start = first;
		std::size_t start = 0;

		for (std::size_t i = 0; i < (num_threads - 1); ++i)
		{
			Iterator block_end = block_start;
			std::size_t end = start;
			std::advance(block_end, block_size);
			//std::advance(end, block_size);
			end += block_size;


			//00 threads[i] = std::thread(Searcher, //< Iterator > (),
			//00 	std::ref(v), str.substr(start, end), str0);//,
				////block_start, block_end, element, 
				//std::ref(result), std::ref(flag));
//00  Searcher(std::ref(v), str.substr(start, end), str0);//00
Searcher(std::ref(v), str, str0);//00
			block_start = block_end;
			start = end;
		}

		//Searcher(v, str.substr(start, length), str0);//,
				//std::ref(result), std::ref(flag));
        //Searcher();
				//< Iterator, T > ()(block_start, last, element, result, flag);
	}

	//if (!flag.load())
	//{
		//return last;
	//}

	//return result.get_future().get();
}
*/
int main(int argc, char ** argv)
{
	//std::vector < int > v(100);

	//std::iota(v.begin(), v.end(), 1);

	std::string str ("chjbaviigdcjbvsdc");
	// std::string str0 ("gd");
	std::string str0 ("d");

	//std::string str0 = "dс";
	std::vector < std::size_t> v;
	v.push_back(100);//static_cast<std::size_t>(123));
	//v.clear();
	//std::cout<<&v<<std::endl;
	std::cout << 1 << std::endl;
	//auto result = parallel_find(v, str, str0);
	//parallel_find(std::ref(v), str, str0);
	//std::vector <std::string::iterator> ROMALOH = Searcher(v, str, str0);
	Searcher(v, str, str0);
	//std::cout<<&v<<std::endl;

	std::cout << 2 << std::endl;
	
	
	//std::cout << 22 << std::endl;
	if(!(v.empty()))
	{
		for(auto i : v)
		{
			std::cout << (i) << std::endl;
		}


		// for(auto i : v)
		// {
		// 	std::cout << *(i) << std::endl;
		// }
		
		
	}
std::cout << 4 << std::endl;
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
//std::cout << (v[v.size()-1]) << std::endl;
	system("pause");

	return EXIT_SUCCESS;
}
