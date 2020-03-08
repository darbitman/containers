#pragma once

#include <array>

#include "Distance.hpp"
#include "Duration.hpp"

namespace helpers::math {

class Speed {
  public:
    enum class Unit { kMPH, kMetersPerSecond, kKPH, kFeetPerSecond };

    constexpr Speed() noexcept;

    constexpr Speed(double value, Unit unit) noexcept;

    ~Speed() noexcept = default;

    constexpr double Get(Unit to_unit) const noexcept;

    constexpr void Set(double value, Unit unit) noexcept;

  private:
    struct Units {
        Unit speed_unit;
        Distance::Unit distance_unit;
        Duration::Unit time_unit;
    };

    constexpr Distance::Unit GetDistanceUnits(Unit unit) const noexcept;

    constexpr Duration::Unit GetDurationUnit(Unit unit) const noexcept;

    Distance distance_;
    Duration time_;
    double value_;
    Unit unit_;

    static constexpr std::array<Units, 4> units_{
        {{Unit::kMetersPerSecond, Distance::Unit::kMeter, Duration::Unit::kSeconds},
         {Unit::kMPH, Distance::Unit::kMile, Duration::Unit::kHours},
         {Unit::kKPH, Distance::Unit::kKilometer, Duration::Unit::kHours},
         {Unit::kFeetPerSecond, Distance::Unit::kFoot, Duration::Unit::kSeconds}}};
};

constexpr Speed::Speed() noexcept
    : distance_(0.0, Distance::Unit::kMeter),
      time_(1.0, Duration::Unit::kSeconds),
      value_(0.0),
      unit_(Unit::kMetersPerSecond) {}

constexpr Speed::Speed(double value, Unit unit) noexcept
    : distance_(value, GetDistanceUnits(unit)),
      time_(1.0, GetDurationUnit(unit)),
      value_(value),
      unit_(unit) {}

constexpr double Speed::Get(Unit to_unit) const noexcept {
    if (to_unit == unit_) {
        return value_;
    } else {
        auto distance_value = distance_.Get(GetDistanceUnits(to_unit));
        auto duration_value = time_.Get(GetDurationUnit(to_unit));
        return distance_value / duration_value;
    }
}

constexpr void Speed::Set(double value, Speed::Unit unit) noexcept {
    distance_.Set(value, GetDistanceUnits(unit));
    time_.Set(1.0, GetDurationUnit(unit));
    value_ = value;
    unit_ = unit;
}

constexpr Distance::Unit Speed::GetDistanceUnits(Speed::Unit unit) const noexcept {
    for (auto& units : units_) {
        if (units.speed_unit == unit) {
            return units.distance_unit;
        }
    }

    return Distance::Unit::kMeter;
}

constexpr Duration::Unit Speed::GetDurationUnit(Speed::Unit unit) const noexcept {
    for (auto& units : units_) {
        if (units.speed_unit == unit) {
            return units.time_unit;
        }
    }

    return Duration::Unit::kSeconds;
}

}  // namespace helpers::math
