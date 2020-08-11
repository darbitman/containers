#include <benchmark/benchmark.h>

#include <cstring>
#include <iostream>
#include <map>
#include <random>
#include <type_traits>

#include "containers/ImmutableMap.hpp"

void StdMapLastKeyAccess(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int32_t i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  const auto last_key = input_map.size() - 1;
  for (auto _ : state) {
    benchmark::DoNotOptimize(input_map.at(last_key));
  }

  state.SetBytesProcessed(state.iterations() * sizeof(decltype(input_map)::value_type));
}

void ImmutableMapLastKeyAccess(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int32_t i = 0; i < state.range(0); ++i) {
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
  for (int32_t i = 0; i < state.range(0); ++i) {
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

void ImmutableMapIteration(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int32_t i = 0; i < state.range(0); ++i) {
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

void StdMapRandomAccess(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int32_t i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  std::mt19937                           rg{std::random_device{}()};
  std::uniform_int_distribution<int32_t> pick(0, input_map.size() - 1);
  std::vector<int32_t>                   keys(input_map.size());
  for (auto& key : keys) {
    key = pick(rg);
  }

  for (auto _ : state) {
    int64_t val_sum = 0;

    for (auto key : keys) {
      val_sum += input_map.at(key);
    }

    benchmark::DoNotOptimize(val_sum);
  }
}

void StdUnorderedMapRandomAccess(benchmark::State& state) {
  std::unordered_map<int32_t, int32_t> input_map;
  for (int32_t i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  std::mt19937                           rg{std::random_device{}()};
  std::uniform_int_distribution<int32_t> pick(0, input_map.size() - 1);
  std::vector<int32_t>                   keys(input_map.size());
  for (auto& key : keys) {
    key = pick(rg);
  }

  for (auto _ : state) {
    int64_t val_sum = 0;

    for (auto key : keys) {
      val_sum += input_map.at(key);
    }

    benchmark::DoNotOptimize(val_sum);
  }
}

void ImmutableMapRandomAccess(benchmark::State& state) {
  std::map<int32_t, int32_t> input_map;
  for (int32_t i = 0; i < state.range(0); ++i) {
    input_map.insert(std::pair<int32_t, int32_t>(i, i + 1));
  }

  helpers::containers::ImmutableMap<int32_t, int32_t> imm_map(input_map);

  std::mt19937                           rg{std::random_device{}()};
  std::uniform_int_distribution<int32_t> pick(0, imm_map.size() - 1);
  std::vector<int32_t>                   keys(imm_map.size());
  for (auto& key : keys) {
    key = pick(rg);
  }

  for (auto _ : state) {
    int64_t val_sum = 0;

    for (auto key : keys) {
      val_sum += imm_map.at(key);
    }

    benchmark::DoNotOptimize(val_sum);
  }
}

BENCHMARK(StdMapLastKeyAccess)->RangeMultiplier(10)->Range(1, 1000000);
BENCHMARK(ImmutableMapLastKeyAccess)->RangeMultiplier(10)->Range(1, 1000000);

BENCHMARK(StdMapIteration)->RangeMultiplier(10)->Range(1, 1000000);
BENCHMARK(ImmutableMapIteration)->RangeMultiplier(10)->Range(1, 1000000);

BENCHMARK(StdMapRandomAccess)->RangeMultiplier(10)->Range(1, 1000000);
BENCHMARK(StdUnorderedMapRandomAccess)->RangeMultiplier(10)->Range(1, 1000000);
BENCHMARK(ImmutableMapRandomAccess)->RangeMultiplier(10)->Range(1, 1000000);

BENCHMARK_MAIN();