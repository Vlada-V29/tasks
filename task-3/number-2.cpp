#include<iostream>

using namespace std;

unsigned hashsh(float x)
{
    union
    {
        float f;
        unsigned u;
    };
    f = x;
    return u;
}

int main()
{
    //???
    return 0;
}

