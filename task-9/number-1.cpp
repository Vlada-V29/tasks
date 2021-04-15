//#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>
#include <utility>
#include <chrono>
#include<thread>
#include <mutex>


#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/pair.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;
int quan_message = 0;
std::mutex m_mutex;

typedef int KeyType;
typedef std::string MappedType;
typedef std::pair<const int, std::string> ValueType;
typedef allocator<ValueType, managed_shared_memory::segment_manager>
		ShmemAllocator;
typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;


void print_mes(MyMap *mymap, int* flag)
{
	while (true)
	{
		if(*flag != quan_message)
		{
			std::lock_guard < std::mutex > lock(m_mutex);
			std::cout << (mymap->end())->first << ":\t" <<
				(mymap->end())->second << std::endl;
			++quan_message;
		}

		using std::chrono::operator""s;
		std::this_thread::sleep_until(std::chrono::system_clock::now() + 1s);


	}
	
}


void enter_mes(MyMap *mymap, const std::chrono::system_clock::time_point *tp, int* flag)
{
	while (true)
	{
		//std::cout << "Your messege: ";
		std::string mess;
		std::cin >> mess;

		auto tn = std::chrono::system_clock::now();
		auto time =
    	std::chrono::duration_cast<std::chrono::seconds>(tn - *tp);

		std::lock_guard < std::mutex > lock(m_mutex);
		mymap->insert(std::pair<KeyType, MappedType>(time.count(), mess));
		++(*flag);

		// m_mutex.lock();
		// m_mutex.unlock();
	}
	
}







int main(int argc, char ** argv)
{
	
	const std::string shared_memory_name = "vk";
	
	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());//?
	
	managed_shared_memory segment(
		open_or_create, shared_memory_name.c_str(), 1024);
	
	
	ShmemAllocator alloc_inst (segment.get_segment_manager());

	MyMap *mymap =
			segment.find_or_construct<MyMap>("MyMap") //object name
			(std::less<int>() //first ctor parameter
			,alloc_inst); //second ctor parameter

	// print_map("Updated map: ", mymap);
	
	int *flag = segment.find_or_construct<int>("Integer")(0);
	//int *number_of_users = segment.find_or_construct<int>("Integer")(1);
	const std::chrono::system_clock::time_point *tp = segment.find_or_construct
		<std::chrono::system_clock::time_point>("clock")(std::chrono::system_clock::now());
	
	auto iterator =  mymap->begin();
	for(auto i = 0; i < *flag; ++i)
	{
		std::cout << (++iterator)->first << ":\t" <<
				(++iterator)->second << std::endl;
	}
	

	
	// 	shared_memory.get_segment_manager());



	std::thread th_enter;
	std::thread th_print;

	th_enter = std::thread(enter_mes, mymap, tp, flag); 
	th_print = std::thread(print_mes, mymap, flag); 




	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}






