#include "benchmark/benchmark.h"

void BM_Branched(benchmark::State& state)
{
    const unsigned int num = state.range(0);
    unsigned long* p1;
    unsigned long* p2;
    bool* b1;
    unsigned long a1 = 0, a2 = 0;
    for(size_t i = 0; i < num; ++i)
    {
        if(b1[i])
        {
            a1 += p1[i] - p2[i];
        }
        else
        {
            a2 += p1[i] * p2[i];
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(num * state.iterations());
}
BENCHMARK(BM_Branched)->Arg(1<<22);
BENCHMARK_MAIN();