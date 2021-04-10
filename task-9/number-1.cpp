//#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>//std::pair<int, std::string>
#include <utility>
#include <chrono>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/pair.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;

int main(int argc, char ** argv)
{
	//using allocator = boost::interprocess::allocator < std::pair<int, std::string>,
	//	boost::interprocess::managed_shared_memory::segment_manager > ;

	//using cont = boost::interprocess::basic_string < , 
	//	std::char_traits < char >, allocator> ;

	//using cont = map<int, std::string>;

	const std::string shared_memory_name = "vk";
	const std::string flag_name = "flag";

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());//?
	boost::interprocess::shared_memory_object::remove(flag_name.c_str());

	managed_shared_memory segment(
		open_or_create, shared_memory_name.c_str(), 1024);
	//managed_shared_memory seg_flag(
	//	open_or_create, flag_name.c_str(), 10);

	//typedef int KeyType;
	typedef int KeyType;
	typedef std::string MappedType;
	typedef std::pair<const int, std::string> ValueType;

	typedef allocator<ValueType, managed_shared_memory::segment_manager>
		ShmemAllocator;
	typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

	ShmemAllocator alloc_inst (segment.get_segment_manager());

	MyMap *mymap =
			segment.find_or_construct<MyMap>("MyMap") //object name
			(std::less<int>() //first ctor parameter
			,alloc_inst); //second ctor parameter

	//print_map("Updated map: ", m);
	
	int *flag = segment.find_or_construct<int>("Integer")(0);
	auto tp = std::chrono::system_clock::now();


	// auto s = segment.find_or_construct < cont > ("lala")
	// 	//(std::pair<int, std::string>(1, "kvbkb"),
	// 	pair<int, std::string>(1, "kvbkb"),
	// 	shared_memory.get_segment_manager());

	//s->push_back(cont(2, "jhg"));

	//std::cout << 45 << std::endl;

	//Insert data in the map
	/*
	for(int i = 0; i < 10; ++i)
	{
		mymap->insert(std::pair<KeyType, MappedType>(i, "bfbkj"));
	}
*/
	



//something is as wrong as possible, but I don't understand what to do
	while(1)
	{
		if(*flag)
		{
			std::cout << (mymap->end())->first << ":\t" <<
				(mymap->end())->second << std::endl;
		}
		MappedType str;
		std::cin >> str;
		*flag = 1;
		// std::getline(std::in, str);
		auto tp2 = std::chrono::duration_cast<std::chrono::seconds>
			(std::chrono::system_clock::now() - tp);
		mymap->insert(std::pair<KeyType, MappedType>(tp2.count(), str));
		//mymap->
		std::cout << (mymap->end())->first << ":\t" <<
			(mymap->end())->second << std::endl;
		*flag = 0;
	}
	









	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}






