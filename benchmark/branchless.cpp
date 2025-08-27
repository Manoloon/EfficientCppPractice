#include "benchmark/benchmark.h"
#include <vector>
/*
branchless computing
*/
static void BM_Branched(benchmark::State& state)
{
    const unsigned int num = state.range(0);
    std::vector<unsigned long> vec1(num);
    std::vector<unsigned long> vec2(num);
    std::vector<bool> cond(num);

    srand(1);
    for(size_t i = 0; i < num;++i)
    {
        vec1[i] = rand();
        vec2[i] = rand();
        cond[i] = rand() & 1;
    }

    for(auto _ : state)
    {
        unsigned long a1 = 0, a2 = 0;
        for(size_t i = 0; i < num; ++i)
        {
            if(cond[i])
            {
                a1 += vec1[i] - vec2[i];
            }
            else
            {
                a2 += vec1[i] * vec2[i];
            }
            benchmark::DoNotOptimize(a1);
            benchmark::DoNotOptimize(a2);
        }
    }
    state.SetItemsProcessed(num * state.iterations());
}

void BM_Branchless(benchmark::State& state)
{
    
    const unsigned int num = state.range(0);
    std::vector<unsigned long> vec1(num);
    std::vector<unsigned long> vec2(num);
    std::vector<bool> cond(num);

    srand(1);
    for(size_t i = 0; i < num;++i)
    {
        vec1[i] = rand();
        vec2[i] = rand();
        cond[i] = rand() & 1;
    }
    
    for(auto _ : state)
    {
        unsigned long a1 = 0, a2 = 0;
        unsigned long* accum[2] = {&a2,&a1};
       
        for(size_t i = 0; i < num; ++i)
        {
        // current overhead is in this two lines
        /*
        unsigned long s[2] = {vec1[i] * vec2[i],vec1[i] - vec2[i]};
        *accum[cond[i]] += s[cond[i]];
        */
        // with bit mask trick
        unsigned long mask = -(unsigned long)cond[i];
        a1 += (vec1[i] - vec2[i]) & mask;
        a2 += (vec1[i] * vec2[i]) & ~mask;
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
    }
    
    state.SetItemsProcessed(num * state.iterations());
}
BENCHMARK(BM_Branched)->Arg(1<<22);
BENCHMARK(BM_Branchless)->Arg(1<<22);
BENCHMARK_MAIN();