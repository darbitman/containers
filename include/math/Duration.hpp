#pragma once

#include <array>

#include "CommonTypes.hpp"

namespace helpers::math {

class Duration {
  static constexpr double kSecondsPerMillisecond = 0.001;
  static constexpr double kSecondsPerMinute      = 60.0;
  static constexpr double kSecondsPerHour        = 3600.0;

 public:
  enum class Unit : UnderlyingEnumType { kMilliseconds = 0, kSeconds = 1, kMinutes = 2, kHours = 3 };

  constexpr Duration() noexcept;

  constexpr Duration(double value, Unit unit) noexcept;

  ~Duration() noexcept = default;

  constexpr double Get(Unit to_unit) const noexcept;

  constexpr void Set(double value, Unit unit) noexcept;

 private:
  constexpr double GetConversionRatio(Unit unit) const noexcept;

  constexpr double GetRatio(Unit to_unit) const noexcept;

  double value_;
  Unit   unit_;

  static constexpr std::array<std::pair<Duration::Unit, double>, 4> seconds_per_unit_{
      {{Duration::Unit::kMilliseconds, Duration::kSecondsPerMillisecond},
       {Duration::Unit::kSeconds, 1.0},
       {Duration::Unit::kMinutes, Duration::kSecondsPerMinute},
       {Duration::Unit::kHours, Duration::kSecondsPerHour}}};
};

constexpr Duration::Duration() noexcept : value_(0.0), unit_(Duration::Unit::kSeconds) {}

constexpr Duration::Duration(double value, Duration::Unit unit) noexcept : value_(value), unit_(unit) {}

constexpr double Duration::Get(Unit to_unit) const noexcept {
  if (to_unit == unit_) {
    return value_;
  } else {
    auto ratio = GetRatio(to_unit);
    return value_ * ratio;
  }
}

constexpr void Duration::Set(double value, Duration::Unit unit) noexcept {
  value_ = value;
  unit_  = unit;
}

constexpr double Duration::GetConversionRatio(Duration::Unit unit) const noexcept {
  return seconds_per_unit_.at(ToIndex(unit)).second;
}

constexpr double Duration::GetRatio(Duration::Unit to_unit) const noexcept {
  return GetConversionRatio(unit_) / GetConversionRatio(to_unit);
}

}  // namespace helpers::math
