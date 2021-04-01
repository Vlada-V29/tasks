#include <iostream>
//#include <string>
//#include <regex>
//#include <memory>
//#include <atomic>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
#include <random>
#include <vector>
//#include <algorithm>
#include <condition_variable>
#include <memory>

#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp> //boost::lockfree::queue
#include <boost/atomic.hpp>


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
class Threadsafe_Queue
{
public:

	Threadsafe_Queue() = default;

	Threadsafe_Queue(const Threadsafe_Queue & other)
	{
		std::lock_guard < std::mutex > lock(other.m_mutex);
		m_queue = other.m_queue;
	}

	Threadsafe_Queue & operator=(const Threadsafe_Queue & other)
	{
		std::scoped_lock lock(m_mutex, other.m_mutex);
		m_queue = other.m_queue;
	}

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_queue.push(value);
		m_condition_variable.notify_one();
	}

	void wait_and_pop(T & value)
	{
		std::unique_lock < std::mutex > lock(m_mutex);
		
		m_condition_variable.wait(lock, [this] {return !m_queue.empty(); });
		value = m_queue.front();
		m_queue.pop();
	}

	std::shared_ptr < T > wait_and_pop()
	{
		std::unique_lock < std::mutex > lock(m_mutex);
		
		m_condition_variable.wait(lock, [this] {return !m_queue.empty(); });
		auto result = std::make_shared < T > (m_queue.front());
		m_queue.pop();
		
		return result;
	}

	bool try_pop(T & value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		
		if (m_queue.empty())
		{
			return false;
		}

		value = m_queue.front();
		m_queue.pop();

		return true;
	}

	std::shared_ptr < T > try_pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		
		if (m_queue.empty())
		{
			return std::shared_ptr < T > ();
		}
			
		auto result = std::make_shared < T > (m_queue.front());
		m_queue.pop();
		
		return result;
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_queue.empty();
	}

private:

	std::queue < T >		m_queue;
	std::condition_variable m_condition_variable;

private:

	mutable std::mutex m_mutex;
};

const int M = 10;
std::atomic < bool > flag(false);

Threadsafe_Queue<int> queue_our;
boost::lockfree::queue<int> queue_boost;


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
		queue_our.push(uid(generator));
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
		queue_boost.push(uid(generator));
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
        queue_our.push(i);
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
        queue_our.try_pop(i);
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
        queue_boost.push(i);
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
        queue_boost.pop(i);
    }
}



