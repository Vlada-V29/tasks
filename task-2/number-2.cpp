#include<iostream>
#include<vector>
#include<array>
#include<deque>
#include<list>
//#include<queue>

#include<algorithm>
#include<chrono>

using namespace std;

template<typename T>
void time_of_sort1(T cont);

template<typename T>
void time_of_sort2(T cont);

void not_sort();

int main(){
    std::vector<int> cont1 {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::array<int, 10> cont2 {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::deque<int> cont3 {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::list<int> cont4 {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    //std::queue<int> cont5 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    std::cout << "\nvector\t";
    time_of_sort1(cont1);
    //time_of_sort2(cont1);
    not_sort();
    

    std::cout << "\narray\t";
    time_of_sort1(cont2);
    //time_of_sort2(cont2);
    not_sort();

    std::cout << "\ndeque\t";
    time_of_sort1(cont3);
    //time_of_sort2(cont3);
    not_sort();

    std::cout << "\nlist\t";
    //time_of_sort1(cont4);
    not_sort();
    time_of_sort2(cont4);
    
    cout << "\n\nLeader is an array.\n";

    return 0;
}

template<typename T>
void time_of_sort1(T cont)
{
    
    auto t_start1 = std::chrono::system_clock::now();
    sort(std::begin(cont), std::end(cont));
    auto t_end1 = chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<chrono::nanoseconds>(t_end1 - t_start1);
    std::cout << result1.count() << " nc" << "\t\t";

}

template<typename T>
void time_of_sort2(T cont)
{
    
    auto t_start2 = chrono::system_clock::now();
    cont.sort();
    auto t_end2 = chrono::system_clock::now();
    auto result2 =
    std::chrono::duration_cast<chrono::nanoseconds>(t_end2 - t_start2);
    std::cout << result2.count() << " nc" << "\t\t";

}

void not_sort(){
    std::cout << "- - -" << "\t\t";
}