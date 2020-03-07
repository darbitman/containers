#pragma once

#include <array>

namespace helpers::math::units {

class Speed {
    static constexpr double kMetersPerSecondPerMPH = 3600.0 / (0.3048 * 5280);
    static constexpr double kMetersPerSecondPerCmPerSecond = 0.01;

  public:
    enum class Unit { kMPH, kMetersPerSecond, kCmPerSecond };

    constexpr Speed() noexcept : value_(0.0), unit_(Unit::kMetersPerSecond) {}

    constexpr Speed(double value, Unit unit) noexcept : value_(value), unit_(unit) {}

    ~Speed() noexcept = default;

    constexpr double Get(Unit to_unit) const noexcept;

  private:
    double value_;
    Unit unit_;

    static constexpr std::array<std::pair<Speed::Unit, double>, 3> meters_per_second_per_unit_{
        {{Speed::Unit::kMetersPerSecond, 1.0},
         {Speed::Unit::kMPH, kMetersPerSecondPerMPH},
         {Speed::Unit::kCmPerSecond, kMetersPerSecondPerCmPerSecond}}};
};

}  // namespace helpers::math::units
