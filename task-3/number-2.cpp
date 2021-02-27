#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>


using namespace std;

std::size_t hashsh(float x)
{
    
    return static_cast<std::size_t>(x * 100) % 10000;
}

float generate_f()
{
    return static_cast<float>(rand()) *  static_cast<float>(rand()) / static_cast<float>(rand());
}

void time_of_vec(const int n);
void time_of_elem(float& elem);
void check_time_vec();
void check_time_elem();
void check_ravn();

int main()
{
    //const int N = 10;
    //srand(static_cast<unsigned int>(time(0)));
    srand(23);
    //std::cout << hashsh(3423.2345) << std::endl;
    //std::cout << hashsh(generate_f()) << std::endl;

    //check_time_vec();
    //check_time_elem();

    check_ravn();



    return 0;
}

//ни иму тетин??

void check_time_vec()
{
    const int N = 3000001;
    for(auto i = 100000; i < N; i += 50000)
    {
        std::cout << i << " ";
        time_of_vec(i);
    }
}

void time_of_vec(const int n)
{
    auto t_start1 = std::chrono::system_clock::now();
    std::vector<float> cont;

    for(auto i = 1; i < n; ++i)
    {
        cont.push_back(generate_f());
    }
    for(auto i : cont)
    {
        i = hashsh(i);
    }


    auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<chrono::microseconds>(t_end1 - t_start1);
    std::cout << result1.count() << "\n";
}

void check_time_elem()
{
    const int N = 100;
    for(auto i = 1; i < N; ++i)
    {
        float f = generate_f();
        std::cout << f << " ";
        time_of_elem(f);
    }
}

void time_of_elem(float& elem)
{
    auto t_start1 = std::chrono::system_clock::now();
    std::vector<float> cont;

    auto i = hashsh(elem);
    
    auto t_end1 = std::chrono::system_clock::now();
    auto result1 =
    std::chrono::duration_cast<chrono::nanoseconds>(t_end1 - t_start1);
    std::cout << result1.count() << "\n";

}

void check_ravn()
{
    const int N = 1001;
    for(auto i = 1; i < N; ++i)
    {
        float f = generate_f();
        std::cout << i << " " << hashsh(f) << std::endl;
    }
}



