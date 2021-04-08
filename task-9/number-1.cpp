//#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>//std::pair<int, std::string>
#include <utility>

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

	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());//?

	managed_shared_memory segment(
		open_or_create, shared_memory_name.c_str(), 1024);

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


	// auto s = segment.find_or_construct < cont > ("lala")
	// 	//(std::pair<int, std::string>(1, "kvbkb"),
	// 	pair<int, std::string>(1, "kvbkb"),
	// 	shared_memory.get_segment_manager());

	//s->push_back(cont(2, "jhg"));

	//std::cout << 45 << std::endl;

	//Insert data in the map
	for(int i = 0; i < 10; ++i)
	{
		mymap->insert(std::pair<KeyType, MappedType>(i, "bfbkj"));
	}











	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

	system("pause");

	return EXIT_SUCCESS;
}






