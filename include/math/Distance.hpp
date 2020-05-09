#pragma once

#include <array>

#include "CommonTypes.hpp"

namespace helpers::math {

class Distance {
  static constexpr double kMetersPerInch       = 0.0254;
  static constexpr double kMetersPerFoot       = 0.3048;
  static constexpr double kMetersPerMillimeter = 0.001;
  static constexpr double kMetersPerCentimeter = 0.01;
  static constexpr double kMetersPerMile       = kMetersPerFoot * 5280.0;
  static constexpr double kMetersPerKilometer  = 1000.0;

 public:
  enum class Unit : UnderlyingEnumType {
    kInch       = 0,
    kFoot       = 1,
    kMillimeter = 2,
    kCentimeter = 3,
    kMeter      = 4,
    kMile       = 5,
    kKilometer  = 6
  };

  constexpr Distance() noexcept;

  constexpr Distance(double value, Unit unit) noexcept;

  ~Distance() noexcept = default;

  constexpr double Get(Unit to_unit) const noexcept;

  constexpr void Set(double value, Unit unit) noexcept;

  constexpr Distance operator+(const Distance& rhs) const noexcept;

  constexpr Distance operator-(const Distance& rhs) const noexcept;

 private:
  constexpr double GetMetersPerUnit(Unit unit) const noexcept;

  constexpr double GetRatio(Unit to_unit) const noexcept;

  double value_;
  Unit   unit_;

  static constexpr std::array<std::pair<Distance::Unit, double>, 7> meters_per_unit_{
      {{Distance::Unit::kInch, kMetersPerInch},
       {Distance::Unit::kFoot, kMetersPerFoot},
       {Distance::Unit::kMillimeter, kMetersPerMillimeter},
       {Distance::Unit::kCentimeter, kMetersPerCentimeter},
       {Distance::Unit::kMeter, 1.0},
       {Distance::Unit::kMile, kMetersPerMile},
       {Distance::Unit::kKilometer, kMetersPerKilometer}}};
};

constexpr Distance::Distance() noexcept : value_(0.0), unit_(Distance::Unit::kMeter) {}

constexpr Distance::Distance(double value, Unit unit) noexcept : value_(value), unit_(unit) {}

constexpr double Distance::Get(Distance::Unit to_unit) const noexcept {
  if (to_unit == unit_) {
    return value_;
  } else {
    return value_ * GetRatio(to_unit);
  }
}

constexpr void Distance::Set(double value, Distance::Unit unit) noexcept {
  value_ = value;
  unit_  = unit;
}

constexpr Distance Distance::operator+(const Distance& rhs) const noexcept {
  if (unit_ == rhs.unit_) {
    return Distance(value_ + rhs.value_, unit_);
  } else {
    return Distance(Get(Unit::kMeter) + rhs.Get(Unit::kMeter), Unit::kMeter);
  }
}

constexpr Distance Distance::operator-(const Distance& rhs) const noexcept {
  if (unit_ == rhs.unit_) {
    return Distance(value_ - rhs.value_, unit_);
  } else {
    return Distance(Get(Unit::kMeter) - rhs.Get(Unit::kMeter), Unit::kMeter);
  }
}

constexpr double Distance::GetMetersPerUnit(Unit unit) const noexcept {
  return meters_per_unit_.at(ToIndex(unit)).second;
}

constexpr double Distance::GetRatio(Unit to_unit) const noexcept {
  return GetMetersPerUnit(unit_) / GetMetersPerUnit(to_unit);
}

}  // namespace helpers::math
