#include <gtest/gtest.h>

#include "math/Speed.hpp"

namespace helpers::math {
namespace {

TEST(SpeedTest, TestMetersPerSecond) {
    constexpr Speed speed(100.0, Speed::Unit::kMetersPerSecond);

    constexpr auto miles_per_hour = speed.Get(Speed::Unit::kMPH);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(miles_per_hour, 223.6937);
    EXPECT_GT(miles_per_hour, 223.6936);
}

TEST(SpeedTest, TestMilesPerHour) {
    constexpr Speed speed(100.0, Speed::Unit::kMPH);

    constexpr auto meters_per_second = speed.Get(Speed::Unit::kMetersPerSecond);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(meters_per_second, 44.7045);
    EXPECT_GT(meters_per_second, 44.7035);
}

}  // namespace
}  // namespace helpers::math
