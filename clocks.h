#include <chrono>
#include <cmath>
#include <iostream>
#include <future>

double duration(timespec a, timespec b)
{
    return a.tv_sec - b.tv_sec + 1e-9* (a.tv_nsec - b.tv_nsec);
}

void clock_test()
{
    timespec rt0, ct0, tt0;
    clock_gettime(CLOCK_REALTIME,&rt0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ct0);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID,&tt0);
    constexpr double x = 1e6;
    double s = 0;
    auto f = std::async(std::launch::async,[&]
        {
            for(double i = 0; i < x; i += 0.1)
            {
                s += std::sin(i);
            }
        });
    f.wait();
    timespec rt1, ct1, tt1;
    clock_gettime(CLOCK_REALTIME,&rt1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ct1);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID,&tt1);
    std::cout << "Real time: " << duration(rt1,rt0) << "s, "
                 "CPU time: " << duration(ct1,ct0) << "s, "
                 "Thread time: " << duration(tt1,tt0) << "s" << std::endl;
}