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

  EXPECT_NEAR(distance_sum.Get(Distance::Unit::kFoot), 108.333, 0.001);
}

TEST(DistanceTest, TestSubtractionOperator) {
  Distance distance_a(100.0, Distance::Unit::kFoot);
  Distance distance_b(100.0, Distance::Unit::kInch);

  Distance distance_difference = distance_a - distance_b;
  EXPECT_NEAR(distance_difference.Get(Distance::Unit::kFoot), 91.666, 0.001);
}

TEST(DistanceTest, TestSubtractionOperatorNegativeResult) {
  Distance distance_a(100.0, Distance::Unit::kFoot);
  Distance distance_b(100.0, Distance::Unit::kInch);

  Distance distance_difference = distance_b - distance_a;
  EXPECT_NEAR(distance_difference.Get(Distance::Unit::kFoot), -91.666, 0.001);
}

}  // namespace
}  // namespace helpers::math
