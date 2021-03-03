#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <ctime>
//#include<set>

//4 12 16 19


bool prime(const std::vector<int>& v0)
{
    int count = 0;
    for(auto i : v0)
    {
        if((i % 2) && (i > 1))
        {
            for(int j = 3; (j < i)&&(count == 0); j+=2)
            {
                (i%j) == 0 ? ++count : count+=0;
                
            }
            if(!(count))
            {
                std::cout << i << std::endl;
                return false;
            }
        }
        if(i == 2)
        {
            std::cout << i << std::endl;
            return false;
        }
        count = 0;
    }
    return true;
}


void print(const std::vector<int>& v0){
    for(auto i : v0)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v1 (10, 0);//1
    iota(v1.begin(), v1.end(), 1);
    std::cout << "1. Look at this sequence: ";
    print(v1);
/*
    std::cout << "2. Let's add 3 elements! Please, enter 3 values: ";//2
    int cur = 0;
    for(int i = 1; i < 4; ++i)
    {
        std::cin >> cur;
        v1.push_back(cur);
    }
    std::cout << "Look at this sequence now: ";
    print(v1);

    std::cout << "3. Wow! It is mixed: ";//3  ???????????????
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(v1), std::end(v1), rng);
    print(v1);
*/


    std::cout << "4. And the next one: ------------------- \n";//4  35?
    //v1.resize(unique(v1.begin(),v1.end())-v1.begin());
    /*auto i = v1.begin();
    std::set<v1::value_type> exists;
    while(i != v1.end()) {
        if (exists.insert(*i).second == false)  //it's a duplicate:
            i = v1.erase(i);
        else //else not a duplicate
            ++i;
    }
    print(v1);
*/

    /*std::cout << "5. Number of odd numbers: ";//5
    std::cout << std::count_if(v1.begin(), v1.end(), 
        [](int elem){return (elem % 2);}) << std::endl;

    std::cout << "6. Max element: ";//6
    std::cout << *(std::max_element(v1.begin(), v1.end())) << std::endl; 
    std::cout << "   Min element: ";
    std::cout << *(std::min_element(v1.begin(), v1.end())) << std::endl; 
    
    std::cout << "7. Prime number: ";//7
    if(prime(v1))
    {
        std::cout << "no prime number" << std::endl;
    }
    
    std::cout << "8. Squares of numbers: ";//8
    std::for_each(v1.begin(), v1.end(), [](int & elem){ elem *= elem;});
    print(v1);
*/
///////////////////////////////////////////////////////////////////////////////////

    std::cout << "9. Look at new sequence: ";//9
    std::vector<int> v2(v1.size(), 0);
    std::mt19937 engine; 
    engine.seed(std::time(nullptr));
    generate(v2.begin(), v2.end(), engine);
    print(v2);

    std::cout << "10. The sum: ";//10
    std::cout << std::accumulate(v2.begin(), v2.end(), 0, 
        [](int a, int b){return a += b;}) << std::endl;
    
    std::cout << "11. The sequence now: ";//11
    fill(v2.begin(), v2.begin()+3, 1);
    print(v2);

    //12

    std::cout << "13. The sequence again: ";//13
    replace_if(v2.begin(), v2.end(), [](int a){return (a < 0);}, 0);
    print(v2);

    std::cout << "14. The sequence without 0: ";//14 
    v2.erase(remove(v2.begin(), v2.end(), 0), v2.end());
    print(v2);

    std::cout << "15. Reversed sequence 3: ";//15
    reverse(v2.begin(), v2.end());
    print(v2);

    //16

    std::cout << "17. Sorted sequences: \n";//17
    std::sort(std::begin(v1), std::end(v1));
    print(v1);
    std::sort(std::begin(v2), std::end(v2));
    print(v2);
    
    std::cout << "18. The 4th sequence: \n";//18
    std::vector<int> v4(v1.size() + v2.size(), 0);
    std::merge(std::begin(v1), std::end(v1),
        std::begin(v2), std::end(v2), std::begin(v4));
    print(v4);

    //19

    std::cout << "20. All sequences: \n";//20
    print(v1);
    print(v2);
    //print(v3);
    print(v4);


    return 0;
}