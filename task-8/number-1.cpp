#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include <ctime>

#include <thread>
#include <mutex>

using namespace std;
std::mutex g_mutex;

double pi_1()
{
    static double k = 0;
    const int N = 100000;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> un_distrib(0, 1);
    for(auto i = 0; i < N; ++i)
    {
        double x = un_distrib(mersenne);
        double y = un_distrib(mersenne);
        if( (x*x + y*y) <= 1.0)
        {
            ++k;
        }
    }
    return 4 * static_cast<double>(k) / static_cast<double>(N);
}

void pi_22(double xm, double xM, const int N, double &K)
{
    double k = 0;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> un_distrib(0, 1);
    std::uniform_real_distribution<> un_distrib_x(xm, xM);
    
    for(auto i = 0; i < N; ++i)
    {
        double x = un_distrib_x(mersenne);
        double y = un_distrib(mersenne);
        if( x*x + y*y <= 1)
        {
            ++k;
        }
    }
    
    std::lock_guard < std::mutex > lock(mutex);
    K += k;
}

double pi_2()
{
    const int N = 100000;
    int num_core = std::thread::hardware_concurrency();
    int num_tr = num_core != 0 ? num_core : 2;
    int n = N / num_tr;
    double k = 0;
    std::vector < std::thread > th(num_tr);

    for (std::size_t i = 0; i < num_tr; ++i)
	{
		th[i] = std::thread(
			pi_22, static_cast<double>(i) / static_cast<double>(num_tr), 
            static_cast<double>(i + 1) / static_cast<double>(num_tr), 
            n, std::ref(k)); 

	}

	for(int i = 0; i < num_tr; ++i)
    {
        th[i].join();
    }
    
    return 4 * static_cast<double>(k) / static_cast<double>(N);
}


int main()
{
    cout << "not parallel:  pi_1 = " << pi_1() << endl;
    cout << "parallel:      pi_2 = " << pi_2() << endl;

    return EXIT_SUCCESS;
}