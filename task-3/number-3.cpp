#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

#include <iomanip>
#include <iterator>
#include <typeinfo>
#include <utility>

template <typename T>
void hash_combine(std::size_t &seed, const T &value) noexcept
{
	seed ^= std::hash<T>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T>
void hash_value(std::size_t &seed, const T &value) noexcept
{
	hash_combine(seed, value);
}

template <typename T, typename... Types>
void hash_value(std::size_t &seed, const T &value, const Types &...args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template <typename... Types>
std::size_t hash_value(const Types &...args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}

class MyClass
{
private:
	friend struct MyClass_Hash;
	friend struct MyClass_Equal;

public:
	explicit MyClass(const std::string &m1, const std::size_t m2, float m3) : m_1(m1), m_2(m2), m_3(m3)
	{
	}

	explicit MyClass()
	{

		for (auto i = 1; i < 6; ++i)
		{
			m_1 += static_cast<char>('a' + rand() % ('z' - 'a'));
		}
		
		m_2 = static_cast<std::size_t>(rand() % 1000);
		m_3 = static_cast<float>(rand()) / static_cast<float>(rand());
	}

	~MyClass() noexcept = default;

public:
	friend std::ostream &operator<<(std::ostream &stream, const MyClass &MyClass)
	{
		return (stream << MyClass.m_1 << ", " << MyClass.m_2 << ", " << MyClass.m_3 << "; ");
	}

private:
	std::string m_1;
	std::size_t m_2;
	float m_3;
};

struct MyClass_Hash
{
	std::size_t operator()(const MyClass &MyClass) const noexcept
	{
		return hash_value(MyClass.m_1, MyClass.m_2);
	}
};

struct MyClass_Equal
{
	bool operator()(const MyClass &lhs, const MyClass &rhs) const noexcept
	{
		return ((lhs.m_1 == rhs.m_1) & (lhs.m_2 == rhs.m_2) & (lhs.m_3 == rhs.m_3));
	}
};

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::pair<T1, T2> p)
{
	return (stream << "[" << p.first << "," << p.second << "]");
}

void print_hash_table_state(const std::unordered_set<MyClass,
													 MyClass_Hash, MyClass_Equal> &unordered_set)
{
	std::cout << "size:            " << unordered_set.size() << std::endl;
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

	std::cout << "data: " << std::endl;

	for (auto index = 0U; index != unordered_set.bucket_count(); ++index)
	{
		std::cout << " b[" << std::setw(3) << index << "]: ";

		for (auto iterator = unordered_set.begin(index);
			 iterator != unordered_set.end(index); ++iterator)
		{
			std::cout << *iterator << ' ';
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	srand(23);
	std::unordered_set<MyClass, MyClass_Hash, MyClass_Equal> MyClasss;

	for (auto i = 1; i < 11; ++i)
	{
		MyClasss.insert(MyClass());
	}
	//MyClasss.insert(MyClass("Ivan", 42, 23.5));
	//MyClasss.insert(MyClass("Jens", 66, 34.6));

	/*for (const auto & MyClass : MyClasss)
	{
		std::cout << MyClass << std::endl;
	}*/

	print_hash_table_state(MyClasss);

	system("pause");

	return EXIT_SUCCESS;
}
