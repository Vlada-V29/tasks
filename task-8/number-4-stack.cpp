#include <iostream>
//#include <string>
//#include <regex>
//#include <memory>
//#include <atomic>
#include <thread>
#include <chrono>
#include <stack>
#include <mutex>
#include <random>
#include <vector>
//#include <algorithm>
#include <boost/thread/thread.hpp>
#include<boost/lockfree/stack.hpp> //boost::lockfree::stack


class Timer
{
public:

	Timer() : 
		tp(std::chrono::steady_clock::now())
	{}

	~Timer()
	{
		std::cout << "Time: " <<
			std::chrono::microseconds(
				std::chrono::duration_cast < std::chrono::microseconds > (
					std::chrono::steady_clock::now() - tp)).count() << " microseconds." << std::endl;
	}

private:

	std::chrono::steady_clock::time_point tp;
};

template < typename T >
class threadsafe_stack
{
private:

	std::stack < T > data;
	mutable std::mutex mutex;

public:

	threadsafe_stack() 
	{}

	threadsafe_stack(const threadsafe_stack & other)
	{
		std::lock_guard < std::mutex > lock(other.mutex);
		data = other.data;
	}

	threadsafe_stack & operator=(const threadsafe_stack &) = delete;

	void push(T new_value)
	{
		std::lock_guard < std::mutex > lock(mutex);
		data.push(new_value);
	}

	std::shared_ptr < T > pop()
	{
		std::lock_guard < std::mutex > lock(mutex);
		// if (data.empty()) { /**/ };
		const std::shared_ptr < T > result(std::make_shared < T > (data.top()));
		data.pop();
		return result;
	}

	void pop(T & value)
	{
		std::lock_guard < std::mutex > lock(mutex);
		// if (data.empty()) { /**/ };
		value = data.top();
		data.pop();
	}
};


const int M = 10;
std::atomic < bool > flag(false);

threadsafe_stack<int> stack_our;
boost::lockfree::stack<int> stack_boost;


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution <> uid(0, 100);

void product_our(const int M);
void consume_our(const int M);
void product_boost();//const int M);
void consume_boost();//const int M);






int main()
{
    const int N = 4;
    //const int M = 10;

    std::cout << "N = " << N << std::endl;
    std::cout << "N/2 = " << N/2 << std::endl;
    std::cout << "M = " << M << std::endl;
    std::cout << std::endl;

//our
{   for (std::size_t i = 0; i < N*M; ++i)
	{
		stack_our.push(uid(generator));
	}

	std::vector < std::thread > product_threads(N / 2);
	std::vector < std::thread > consume_threads (N / 2);

	for (std::size_t i = 0; i < N / 2; ++i)
	{
		product_threads[i] = std::thread(product_our, M);
		consume_threads [i] = std::thread(consume_our,  M);
	}

	{
		Timer t;

		flag.store(true);
		
        for (int i = 0; i < N/2; ++i)
	    {
		    product_threads[i].join();

	    }
        for (int i = 0; i < N/2; ++i)
	    {
		    consume_threads[i].join();

	    }

	}
}

//boost
{    for (std::size_t i = 0; i < N*M; ++i)
	{
		stack_boost.push(uid(generator));
	}
	
    boost::thread_group product_threads_b, consume_threads_b;

	for (std::size_t i = 0; i < N / 2; ++i)
	{
		product_threads_b.create_thread(product_boost);
		consume_threads_b.create_thread(consume_boost);
	}
	
	{
		Timer t;

		flag.store(true);
		
        product_threads_b.join_all();
        consume_threads_b.join_all();

	}
}


    return 0;
    
}






void product_our(const int M)
{
    while (!flag.load())
	{
		std::this_thread::yield();
	}
    for(auto i = 0; i < M; ++i)
    {
        stack_our.push(i);
    }
}

void consume_our(const int M)
{
    while (!flag.load())
	{
		std::this_thread::yield();
	}
    for(auto i = 0; i < M; ++i)
    {
        stack_our.pop(i);
    }
}

void product_boost()
{
    while (!flag.load())
	{
		std::this_thread::yield();
	}

    for(auto i = 0; i < M; ++i)
    {
        stack_boost.push(i);
    }
}

void consume_boost()
{
    while (!flag.load())
	{
		std::this_thread::yield();
	}
    for(auto i = 0; i < M; ++i)
    {
        stack_boost.pop(i);
    }
}



