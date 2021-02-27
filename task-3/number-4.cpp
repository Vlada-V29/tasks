#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

#include <iomanip>
#include <iterator>
#include <typeinfo>
#include <utility>


unsigned int RSHash(const char* str, unsigned int length)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)//3
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)//6
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
   unsigned int hash = length;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }

   return hash;
}

unsigned int APHash(const char* str, unsigned int length)//9
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}


template< unsigned int (*func)(const char* , unsigned int)>
struct My_Hash
{
	std::size_t operator()(const std::string &str) const noexcept
	{
		return func((char*)(&str), str.length());
	}
};

std::string generate_str()
{
    std::string str = "";
	for (auto i = 1; i < 6; ++i)
	{
		str += static_cast<char>('a' + rand() % ('z' - 'a'));
	}

       return str;
}



template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::pair<T1, T2> p)
{
	return (stream << "[" << p.first << "," << p.second << "]");
}

template< unsigned int (*func)(const char* , unsigned int)>
void print_hash_table_state(const std::unordered_set<std::string, My_Hash<func>> &unordered_set)
{
	/*std::cout << "size:            " << unordered_set.size() << std::endl;
	std::cout << "buckets:         " << unordered_set.bucket_count() << std::endl;
	std::cout << "load factor:     " << unordered_set.load_factor() << std::endl;
	std::cout << "max load factor: " << unordered_set.max_load_factor() << std::endl;

	std::cout << std::endl;

	if (typeid(
			typename std::iterator_traits<
				typename std::unordered_set<int>::iterator>::iterator_category) ==
		typeid(std::bidirectional_iterator_tag))
	{
		std::cout << "chaining style: doubly-linked" << std::endl;
	}
	else
	{
		std::cout << "chaining style: singly-linked" << std::endl;
	}

	std::cout << std::endl;
	*/
	//std::cout << "data: " << std::endl;
	int cur = 0;

	for (auto index = 0U; index != unordered_set.bucket_count(); ++index)
	{
		//std::cout << " b[" << std::setw(3) << index << "]: ";

		for (auto iterator = unordered_set.begin(index);
			 iterator != unordered_set.end(index); )//++iterator)
		{
			//std::cout << *iterator << ' ';
			if (++iterator != unordered_set.end(index)){
				++cur;
			}
			
		}

		//std::cout << std::endl;
	}

	//std::cout << std::endl;

	std::cout << cur << std::endl;
}
template<unsigned int (*func)(const char* , unsigned int)>
void the_check();

int main(int argc, char **argv)
{
	srand(23);//static_cast<unsigned int>(time(0))
	

    the_check<RSHash>();
    //the_check<JSHash>();
    //the_check<PJWHash>();//3
   //the_check<ELFHash>();
    //the_check<BKDRHash>();
    //the_check<SDBMHash>();//6
    //the_check<DJBHash>();
    //the_check<DEKHash>();
    //the_check<APHash>();//9


	system("pause");
	return EXIT_SUCCESS;
}

template<unsigned int (*func)(const char* , unsigned int)>
void the_check()
{
	int N = 2000001;

	for (auto i = 100000; i < N; i += 50000)
	{
		std::unordered_set<std::string, My_Hash<func>> str;
		for (auto j = 1; j < i; ++j)
		{
			str.insert(generate_str());
		}
		std::cout << i << " ";
		print_hash_table_state(str);
	}
    

	
}
