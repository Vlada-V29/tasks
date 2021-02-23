#include<iostream>
#include<vector>
#include<set>

#include<algorithm>
#include<chrono>

using namespace std;

void time_of_sort1(int);
void time_of_sort2(int);


int main()
{
    const int N = 100; //~25 -- changes
    time_of_sort1(N); 
    time_of_sort2(N);

    return 0;
}

void time_of_sort1(const int n)
{
    auto t_start1 = std::chrono::system_clock::now();
    std::vector<int> cont;

    auto rand_val = std::chrono::duration_cast<chrono::nanoseconds>(t_start1 - 
        std::chrono::system_clock::now());
    srand(rand_val.count());

    for(auto i = 1; i < n; ++i)
    {
        cont.push_back(rand());
    }
    sort(std::begin(cont), std::end(cont));

    auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<chrono::microseconds>(t_end1 - t_start1);
    std::cout << "vector: " << result1.count() << " mc" << "\n";

}

void time_of_sort2(const int n)
{
    auto t_start2 = chrono::system_clock::now();
    std::set<int> cont;

    auto rand_val = std::chrono::duration_cast<chrono::microseconds>(t_start2 - 
        std::chrono::system_clock::now());
    srand(rand_val.count());

    for(auto i = 1; i < n; ++i)
    {
        cont.insert(rand());
    }

    auto t_end2 = chrono::system_clock::now();
    auto result2 =
    std::chrono::duration_cast<chrono::microseconds>(t_end2 - t_start2);
    std::cout << "set: " << result2.count() << " mc" << "\n";

}
