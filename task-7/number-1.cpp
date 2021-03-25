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
    return 4 * k / N;
}

void pi_22(double xm, const int N, double &K)
{
    double k = 0;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> un_distrib(0, 1);
    std::uniform_real_distribution<> un_distrib_x(xm, xm + 0.25);
    
    for(auto i = 0; i < N; ++i)
    {
        double x = un_distrib_x(mersenne);
        double y = un_distrib(mersenne);
        if( x*x + y*y <= 1)
        {
            ++k;
        }
    }
    
    g_mutex.lock();
    K += k;
    g_mutex.unlock();
}

double pi_2()
{
    const int N = 100000;
    int n = N / 4;
    double k = 0;

    thread thr1(pi_22, 0.0, n, std::ref(k));
	thread thr2(pi_22, 0.25, n, std::ref(k));
    thread thr3(pi_22, 0.5, n, std::ref(k));
    thread thr4(pi_22, 0.75, n, std::ref(k));

    thr1.join();
	thr2.join();
    thr3.join();
	thr4.join();

    return 4 * k / N;
}


int main()
{
    cout << "not parallel:  pi_1 = " << pi_1() << endl;
    cout << "parallel:      pi_2 = " << pi_2() << endl;

    return EXIT_SUCCESS;
}