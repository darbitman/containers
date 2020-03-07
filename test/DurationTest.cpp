#include <gtest/gtest.h>

#include "math/Duration.hpp"

namespace helpers::math {
namespace {

TEST(DurationTest, TestSeconds) {
    constexpr Duration time(3600.0, Duration::Unit::kSeconds);

    constexpr auto milliseconds = time.Get(Duration::Unit::kMilliseconds);
    EXPECT_EQ(milliseconds, 3600000.0);

    constexpr auto minutes = time.Get(Duration::Unit::kMinutes);
    EXPECT_EQ(minutes, 60.0);

    constexpr auto hours = time.Get(Duration::Unit::kHours);
    EXPECT_EQ(hours, 1.0);
}

}  // namespace
}  // namespace helpers::math
