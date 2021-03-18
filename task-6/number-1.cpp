#include <iostream>
#include<fstream>
#include <cstdio>
#include <string>

using namespace std;

bool test(char c1, char c2);

int main()
{

    fstream iof("Test.txt", ios::in | ios::out);
    if(!iof)
    {
        cerr << "Oh no!" << endl;
        return EXIT_FAILURE;
    }
    
    char c1 = '1';
    char c2;

    while(iof)
    {
		iof.get(c2);
        if(test(c1, c2))
        {
            iof.seekg(-1, ios::cur);
            iof.put(' ');
            iof.put(' ');

        }
        c1 = c2;
    }
    
    return EXIT_SUCCESS;
}


bool test(char c1, char c2){
    static int k = 0;

    if((c2 == '"')&&(c1 != '\\'))
    {
        k? --k : ++k;
    }
    if((c2 == '\\')&&(c1 != '\\')&&(!k))
    {
        return true;
    }

    return false;
}