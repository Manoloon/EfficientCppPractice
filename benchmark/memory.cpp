#include "benchmark/benchmark.h"
#include <cstdint>
#include <limits>

template<int N, typename F>
inline void repeat(F&& f)
{
    if constexpr (N >0)
    {
        f();
        repeat<N-1>(std::forward<F>(f));
    }
}

void BM_read_cache(benchmark::State& state)
{
    const unsigned int size = state.range(0);
    void* mem = malloc(size);
    void* end = static_cast<char*>(mem) + size;

    volatile int16_t* p0 = static_cast<int16_t*>(mem);
    int16_t* p1 = static_cast<int16_t*>(end);

    for(auto _ : state)
    {
        for(volatile int16_t* p = p0; p != p1;)
        {
            repeat<16>([&]{benchmark::DoNotOptimize(*p++);});
        }
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(size * state.iterations());
    state.SetItemsProcessed((p1 - p0) * state.iterations());
    free(mem);
}

void BM_write_cache(benchmark::State& state)
{
    const unsigned int size = state.range(0);
    void* mem = malloc(size);
    void* end = static_cast<char*>(mem) + size;

    volatile int16_t* p0 = static_cast<int16_t*>(mem);
    int16_t* p1 = static_cast<int16_t*>(end);
    int16_t fill = std::numeric_limits<int16_t>::max();
    for(auto _ : state)
    {
        for(volatile int16_t* p = p0; p != p1;)
        {
            repeat<16>([&]{benchmark::DoNotOptimize(*p++ = fill);});
        }
        benchmark::ClobberMemory();
    }
    state.SetBytesProcessed(size * state.iterations());
    state.SetItemsProcessed((p1 - p0) * state.iterations());
    free(mem);
}
BENCHMARK(BM_read_cache)->Arg(1<<22);
BENCHMARK(BM_write_cache)->Arg(1<<22);
BENCHMARK_MAIN();