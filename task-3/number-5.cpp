#include<iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

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
			tag<Rec::ByAddr>, member<Rec, std::string, &Rec::addr>
		>,
        random_access<>
	>
> Store;
std::size_t hash_value(std::string x) { return hash<string>{}(x); }


int main()
{
    Store store;
	Rec r1 = { "Basilio Pupkinio", "022", "Neron st" };
    Rec r2 = { "Vasya Pupkin",     "022", "Around st" };
    Rec r3  = { "Vasilisa Pupkina", "022", "Around st" };
	store.insert(r1);
	store.insert(r2);
    store.insert(r3);

	//???
    
    
    
    return 0;
}