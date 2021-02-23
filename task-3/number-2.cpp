#include<iostream>

using namespace std;

std::size_t hashsh(float x)
{
    
    return static_cast<std::size_t>(x * 100) % 10000;
}

int main()
{
    std::cout << hashsh(3423.2345) << std::endl;

    return 0;
}

