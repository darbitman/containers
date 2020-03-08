#pragma once

#include <array>

namespace helpers::math {

class Distance {
    static constexpr double kMetersPerInch = 0.0254;
    static constexpr double kMetersPerFoot = 0.3048;
    static constexpr double kMetersPerMillimeter = 0.001;
    static constexpr double kMetersPerCentimeter = 0.01;
    static constexpr double kMetersPerMile = kMetersPerFoot * 5280.0;
    static constexpr double kMetersPerKilometer = 1000.0;

  public:
    enum class Unit { kInch, kFoot, kMillimeter, kCentimeter, kMeter, kMile, kKilometer };

    constexpr Distance() noexcept;

    constexpr Distance(double value, Unit unit) noexcept;

    ~Distance() noexcept = default;

    constexpr double Get(Unit to_unit) const noexcept;

    constexpr void Set(double value, Unit unit) noexcept;

  private:
    constexpr double GetMetersPerUnit(Unit unit) const noexcept;

    constexpr double GetRatio(Unit to_unit) const noexcept;

    double value_;
    Unit unit_;

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
    unit_ = unit;
}

constexpr double Distance::GetMetersPerUnit(Unit unit) const noexcept {
    for (auto& meters_per : meters_per_unit_) {
        if (meters_per.first == unit) {
            return meters_per.second;
        }
    }

    return 1.0;
}

constexpr double Distance::GetRatio(Unit to_unit) const noexcept {
    return GetMetersPerUnit(unit_) / GetMetersPerUnit(to_unit);
}

}  // namespace helpers::math
