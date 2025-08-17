#include "benchmark/benchmark.h"
#include <vector>

void BM_add(benchmark::State& state)
{
    srand(1);
    const unsigned int num = state.range(0);
    std::vector<unsigned long> vec1(num);
    std::vector<unsigned long> vec2(num);

    for(size_t i = 0; i < num;++i)
    {
        vec1[i] = rand();
        vec2[i] = rand();
    }
    unsigned long* p1 = vec1.data();
    unsigned long* p2 = vec2.data();
    for(auto _ : state)
    {
        unsigned long a1 = 0;
        for(size_t i = 0; i < num;++i)
        {
            a1 += p1[i] + p2[i];
        }
        benchmark::DoNotOptimize(a1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(num * state.iterations());
}

BENCHMARK(BM_add)->Arg(1<<22);
BENCHMARK_MAIN();