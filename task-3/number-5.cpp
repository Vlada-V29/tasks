#include<iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

#include <iomanip>

using namespace std;
using namespace boost::multi_index;


struct Rec 
{ 
    std::string name, phone, addr; 
    struct ByName {}; struct ByPhone {}; struct ByAddr {};
};

typedef boost::multi_index_container<Rec,
	indexed_by<
        hashed_non_unique<
			tag<Rec::ByName>, member<Rec, std::string, &Rec::name>
		>, 
		hashed_non_unique<
			tag<Rec::ByPhone>, member<Rec, std::string, &Rec::phone>
		>,
		hashed_non_unique<
			tag<Rec::ByAddr>, member<Rec, std::string, &Rec::addr>
		>,
        random_access<>
	>
> Store;
std::size_t hash_value(std::string x) { return hash<string>{}(x); }


int main()
{
    Store store;
	Rec r1 = { "Basilio Pupkinio", "024", "Neron st" };
    Rec r2 = { "Vasya Pupkin",     "022", "Around st" };
    Rec r3  = { "Vasilisa Pupkina", "022", "Around st" };
	Rec r4  = { "David Tennant", "010", "Abby Road" };
	Rec r5  = { "Michael Sheen", "399", "Carnaby st" };
	store.insert(r1);
	store.insert(r2);
    store.insert(r3);
	store.insert(r4);
	store.insert(r5);


	for (auto it:store)	
	{
		std::cout << it.name << ", " << (it).phone << ", " 
			<< (it).addr << "; " << std::endl;
	}
	std::cout << "\n" << std::endl;


	std::string find_id = "David Tennant"; 
	typedef Store::index<Rec::ByName>::type List;
	const List& ls1 = store.get<Rec::ByName>();
	List::const_iterator it1 = ls1.find(find_id);
	if (it1 != ls1.end())
	{
		std::cout << "David Tennant\t" << it1->phone << "\t" 
			<< it1->addr << std::endl;
	}
	std::cout << "\n" << std::endl;
	 
    
    return 0;
}