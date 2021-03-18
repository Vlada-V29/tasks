#include<iostream>
#include<fstream>
#include<cstdlib>

int main()
{
    using namespace std;

    const int L = 9;
    const int N = 20;
    ofstream outf("MyF.txt");
    if(!outf)
    {
        cerr << "Oh no!" << endl;
        exit(1);
    }

    for(char j = '0'; j <= '1'; ++j)
    {
        for(char i = '0'; i <= '9'; ++i)
        {
            outf << "line #" << j << i << endl;
        }
    }


    int n = 0;
    cout << "Insert line number: ";
    cin >> n;
    if(!((n < N)&&(n >= 0)))
    {
        cout << "I'm sorry, I haven't this line" << endl;
        return EXIT_FAILURE;
    }


    ifstream inf("MyF.txt");    
    inf.seekg(L * (n), ios::beg);

    string strInput;
	getline(inf, strInput);
	cout << strInput << endl;
    cout << endl;

    return EXIT_SUCCESS;
}