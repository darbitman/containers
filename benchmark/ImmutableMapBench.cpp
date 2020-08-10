#include <benchmark/benchmark.h>

#include <cstring>
#include <iostream>
#include <map>
#include <type_traits>

#include "containers/ImmutableMap.hpp"

void StdMapLastKeyAccess(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  const auto last_key = input_map.size() - 1;
  for (auto _ : state) {
    benchmark::DoNotOptimize(input_map.at(last_key));
  }

  state.SetBytesProcessed(state.iterations() * sizeof(decltype(input_map)::value_type));
}

void ImmMapLastKeyAccess(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  helpers::containers::ImmutableMap<int32_t, int32_t> imm_map(input_map);

  const auto last_key = imm_map.size() - 1;
  for (auto _ : state) {
    benchmark::DoNotOptimize(imm_map.at(last_key));
  }

  state.SetBytesProcessed(state.iterations() * sizeof(decltype(imm_map)::value_type));
}

void StdMapIteration(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  for (auto _ : state) {
    int64_t key_sum = 0;
    int64_t val_sum = 0;

    for (auto [k, v] : input_map) {
      key_sum += k;
      val_sum += v;
    }
    benchmark::DoNotOptimize(key_sum);
    benchmark::DoNotOptimize(val_sum);
  }

  state.SetBytesProcessed(state.iterations() * sizeof(decltype(input_map)::value_type));
}

void ImmMapIteration(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  helpers::containers::ImmutableMap<int32_t, int32_t> imm_map(input_map);

  for (auto _ : state) {
    int64_t key_sum = 0;
    int64_t val_sum = 0;

    for (auto [k, v] : imm_map) {
      key_sum += k;
      val_sum += v;
    }
    benchmark::DoNotOptimize(key_sum);
    benchmark::DoNotOptimize(val_sum);
  }

  state.SetBytesProcessed(state.iterations() * sizeof(decltype(imm_map)::value_type));
}

BENCHMARK(StdMapLastKeyAccess)->RangeMultiplier(10)->Range(1, 1000000);
BENCHMARK(ImmMapLastKeyAccess)->RangeMultiplier(10)->Range(1, 1000000);

BENCHMARK(StdMapIteration)->RangeMultiplier(10)->Range(1, 1000000);
BENCHMARK(ImmMapIteration)->RangeMultiplier(10)->Range(1, 1000000);

BENCHMARK_MAIN();