#include <gtest/gtest.h>

#include "math/Distance.hpp"

namespace helpers::math {
namespace {

TEST(DistanceTest, TestMeters) {
    constexpr Distance distance(1609.344, Distance::Unit::kMeter);

    constexpr auto miles = distance.Get(Distance::Unit::kMile);
    EXPECT_EQ(miles, 1.0);
}

TEST(DistanceTest, TestAdditionOperator) {
    constexpr Distance distance_a(100.0, Distance::Unit::kFoot);
    constexpr Distance distance_b(100.0, Distance::Unit::kInch);

    constexpr Distance distance_sum = distance_a + distance_b;
    constexpr auto distance_sum_value = distance_sum.Get(Distance::Unit::kFoot);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(distance_sum_value, 108.33334);
    EXPECT_GT(distance_sum_value, 108.33333);
}

}  // namespace
}  // namespace helpers::math
