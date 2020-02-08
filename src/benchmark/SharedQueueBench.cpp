#include <benchmark/benchmark.h>

#include <atomic>
#include <cstdint>
#include <iostream>

#include "containers/SharedQueue.hpp"

//------------------------------------------------------------------------------

static void BM_PushSharedQueueBlocking(benchmark::State& state) {
    // how many values to push to the queue
    uint32_t num_values = state.range(0);

    for (auto _ : state) {
        ctr::containers::SharedQueue<uint32_t, true> queue;

        for (uint32_t i = 0; i < num_values; ++i) {
            queue.push(i);
        }

        benchmark::DoNotOptimize(queue);
    }
}

BENCHMARK(BM_PushSharedQueueBlocking)->RangeMultiplier(10)->Range(100, 1000000);

//------------------------------------------------------------------------------

static void BM_PushSharedQueueNonblocking(benchmark::State& state) {
    // how many values to push to the queue
    uint32_t num_values = state.range(0);

    for (auto _ : state) {
        ctr::containers::SharedQueue<uint32_t, false> queue;

        for (uint32_t i = 0; i < num_values; ++i) {
            queue.push(i);
        }

        benchmark::DoNotOptimize(queue);
    }
}

BENCHMARK(BM_PushSharedQueueNonblocking)->RangeMultiplier(10)->Range(100, 1000000);

//------------------------------------------------------------------------------

static void BM_PushStdQueue(benchmark::State& state) {
    // how many values to push to the queue
    uint32_t num_values = state.range(0);

    for (auto _ : state) {
        std::queue<uint32_t> queue;

        for (uint32_t i = 0; i < num_values; ++i) {
            queue.push(i);
        }

        benchmark::DoNotOptimize(queue);
    }
}

BENCHMARK(BM_PushStdQueue)->RangeMultiplier(10)->Range(100, 1000000);

//------------------------------------------------------------------------------

BENCHMARK_MAIN();
