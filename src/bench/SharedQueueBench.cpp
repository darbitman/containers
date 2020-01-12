#include <benchmark/benchmark.h>

#include <atomic>
#include <cstdint>

#include "SharedQueue.hpp"

static void BM_PushSharedQueueBlocking(benchmark::State& state) {
    ctr::SharedQueue<uint32_t> queue;

    uint32_t max = state.range(0);

    for (auto _ : state) {
        for (uint32_t i = 0; i < max; ++i) {
            queue.push(i);
        }
    }
}

BENCHMARK(BM_PushSharedQueueBlocking)->RangeMultiplier(10)->Range(100, 1000000);

static void BM_PushSharedQueueNonblocking(benchmark::State& state) {
    ctr::SharedQueue<uint32_t, false> queue;

    uint32_t max = state.range(0);

    for (auto _ : state) {
        for (uint32_t i = 0; i < max; ++i) {
            queue.push(i);
        }
    }
}

BENCHMARK(BM_PushSharedQueueNonblocking)->RangeMultiplier(10)->Range(100, 1000000);

static void BM_PushStdQueue(benchmark::State& state) {
    std::queue<uint32_t> queue;

    uint32_t max = state.range(0);

    for (auto _ : state) {
        for (uint32_t i = 0; i < max; ++i) {
            queue.push(i);
        }
    }
}

BENCHMARK(BM_PushStdQueue)->RangeMultiplier(10)->Range(100, 1000000);

BENCHMARK_MAIN();
