#include <gtest/gtest.h>

#include "math/Speed.hpp"

namespace helpers::math {
namespace {

TEST(SpeedTest, TestMetersPerSecond) {
    constexpr Speed speed(100.0, Speed::Unit::kMetersPerSecond);

    constexpr auto miles_per_hour = speed.Get(Speed::Unit::kMPH);
    constexpr auto kilometers_per_hour = speed.Get(Speed::Unit::kKPH);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(miles_per_hour, 223.6937);
    EXPECT_GT(miles_per_hour, 223.6936);

    EXPECT_LT(kilometers_per_hour, 360.0001);
    EXPECT_GT(kilometers_per_hour, 359.9999);
}

TEST(SpeedTest, TestMilesPerHour) {
    constexpr Speed speed(100.0, Speed::Unit::kMPH);

    constexpr auto meters_per_second = speed.Get(Speed::Unit::kMetersPerSecond);
    constexpr auto kilometers_per_hour = speed.Get(Speed::Unit::kKPH);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(meters_per_second, 44.7045);
    EXPECT_GT(meters_per_second, 44.7035);

    EXPECT_LT(kilometers_per_hour, 160.935);
    EXPECT_GT(kilometers_per_hour, 160.934);
}

TEST(SpeedTest, TestKilometersPerHour) {
    constexpr Speed speed(100.0, Speed::Unit::kKPH);

    constexpr auto meters_per_second = speed.Get(Speed::Unit::kMetersPerSecond);
    constexpr auto miles_per_hour = speed.Get(Speed::Unit::kMPH);

    // Floating point error might occur, so ensure value is between upper and lower bound
    EXPECT_LT(meters_per_second, 27.77778);
    EXPECT_GT(meters_per_second, 27.77777);

    EXPECT_LT(miles_per_hour, 62.1372);
    EXPECT_GT(miles_per_hour, 62.1371);
}

}  // namespace
}  // namespace helpers::math
