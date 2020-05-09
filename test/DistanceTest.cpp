#include <gtest/gtest.h>

#include "math/Distance.hpp"

namespace helpers::math {
namespace {

TEST(DistanceTest, TestMeters) {
    Distance distance(1609.344, Distance::Unit::kMeter);

    auto miles = distance.Get(Distance::Unit::kMile);
    EXPECT_EQ(miles, 1.0);
}

TEST(DistanceTest, TestAdditionOperator) {
    Distance distance_a(100.0, Distance::Unit::kFoot);
    Distance distance_b(100.0, Distance::Unit::kInch);

    Distance distance_sum = distance_a + distance_b;
    auto distance_sum_value = distance_sum.Get(Distance::Unit::kFoot);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(distance_sum_value, 108.33334);
    EXPECT_GT(distance_sum_value, 108.33333);
}

TEST(DistanceTest, TestSubtractionOperator) {
    Distance distance_a(100.0, Distance::Unit::kFoot);
    Distance distance_b(100.0, Distance::Unit::kInch);

    Distance distance_difference = distance_a - distance_b;
    auto distance_difference_value = distance_difference.Get(Distance::Unit::kFoot);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(distance_difference_value, 91.66667);
    EXPECT_GT(distance_difference_value, 91.66666);
}

TEST(DistanceTest, TestSubtractionOperatorNegativeResult) {
    Distance distance_a(100.0, Distance::Unit::kFoot);
    Distance distance_b(100.0, Distance::Unit::kInch);

    Distance distance_difference = distance_b - distance_a;
    auto distance_difference_value = distance_difference.Get(Distance::Unit::kFoot);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(distance_difference_value, -91.66666);
    EXPECT_GT(distance_difference_value, -91.66667);
}

}  // namespace
}  // namespace helpers::math
