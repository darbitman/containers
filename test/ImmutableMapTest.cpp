#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>

#include "containers/ImmutableMap.hpp"

namespace helpers::containers {
namespace {

TEST(ImmutableMapTest, StdMap) {
  const std::map<int32_t, int32_t> input_map = {{1, 2}, {3, 7}, {19, 5}, {2, 12}, {7, 99}};

  ImmutableMap<int32_t, int32_t> immutable_map(input_map);

  EXPECT_EQ(immutable_map.size(), input_map.size());

  EXPECT_EQ(immutable_map.count(1), 1);
  EXPECT_EQ(immutable_map.count(0), 0);

  EXPECT_EQ(immutable_map.at(1), 2);
  EXPECT_EQ(immutable_map.at(19), 5);
  EXPECT_THROW(immutable_map.at(12), std::out_of_range);

  auto intput_map_iter = input_map.begin();
  for (const auto& [k, v] : immutable_map) {
    EXPECT_EQ(k, intput_map_iter->first);
    EXPECT_EQ(v, intput_map_iter->second);
    ++intput_map_iter;
  }
}

TEST(ImmutableMapTest, EmptyStdMap) {
  const std::map<int32_t, int32_t> input_map;

  ImmutableMap<int32_t, int32_t> immutable_map(input_map);

  EXPECT_EQ(immutable_map.size(), input_map.size());
  EXPECT_TRUE(immutable_map.empty());

  EXPECT_EQ(immutable_map.count(0), 0);

  EXPECT_THROW(immutable_map.at(12), std::out_of_range);
}

TEST(ImmutableMapTest, SingleElementStdMap) {
  const std::map<int32_t, int32_t> input_map{{1, 2}};

  ImmutableMap<int32_t, int32_t> immutable_map(input_map);

  EXPECT_EQ(immutable_map.size(), input_map.size());
  EXPECT_FALSE(immutable_map.empty());

  EXPECT_EQ(immutable_map.count(1), 1);
  EXPECT_EQ(immutable_map.count(0), 0);

  EXPECT_EQ(immutable_map.at(1), 2);
  EXPECT_THROW(immutable_map.at(12), std::out_of_range);
}

TEST(ImmutableMapTest, GreaterThanCompareStdMap) {
  const std::map<int32_t, int32_t, std::greater<int32_t>> input_map = {{1, 2}, {3, 7}, {19, 5}, {2, 12}, {7, 99}};

  ImmutableMap<int32_t, int32_t> immutable_map(input_map);

  ASSERT_EQ(immutable_map.size(), input_map.size());

  EXPECT_EQ(immutable_map.count(1), 1);
  EXPECT_EQ(immutable_map.count(0), 0);

  EXPECT_EQ(immutable_map.at(1), 2);
  EXPECT_EQ(immutable_map.at(19), 5);
  EXPECT_THROW(immutable_map.at(12), std::out_of_range);

  auto intput_map_iter = input_map.rbegin();
  for (const auto& [k, v] : immutable_map) {
    EXPECT_EQ(k, intput_map_iter->first);
    EXPECT_EQ(v, intput_map_iter->second);
    ++intput_map_iter;
  }
}

}  // namespace
}  // namespace helpers::containers