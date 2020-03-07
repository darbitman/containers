#include <gtest/gtest.h>

#include "math/Distance.hpp"

namespace helpers::math {
namespace {

TEST(DistanceTest, TestMeters) {
    constexpr Distance distance(1609.344, Distance::Unit::kMeter);

    constexpr auto miles = distance.Get(Distance::Unit::kMile);
    EXPECT_EQ(miles, 1.0);
}

}  // namespace
}  // namespace helpers::math
