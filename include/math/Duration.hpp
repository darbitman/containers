#pragma once

#include <array>

namespace helpers::math {

class Duration {
    static constexpr double kSecondsPerMillisecond = 0.001;
    static constexpr double kSecondsPerMinute = 60.0;
    static constexpr double kSecondsPerHour = 3600.0;

  public:
    enum class Unit { kHours, kMinutes, kSeconds, kMilliseconds };

    constexpr Duration() noexcept : value_(0.0), unit_(Unit::kSeconds) {}

    constexpr Duration(double value, Unit unit) noexcept : value_(value), unit_(unit) {}

    ~Duration() noexcept = default;

    constexpr double Get(Unit to_unit) const noexcept;

    constexpr void Set(double value, Unit unit) noexcept {
        value_ = value;
        unit_ = unit;
    }

  private:
    constexpr double GetConversionRatio(Unit unit) const {
        for (auto& ratios : seconds_per_unit_) {
            if (ratios.first == unit) {
                return ratios.second;
            }
        }

        return 1.0;
    }

    constexpr double GetRatio(Unit to_unit) const {
        return GetConversionRatio(unit_) / GetConversionRatio(to_unit);
    }

    double value_;
    Unit unit_;

    static constexpr std::array<std::pair<Duration::Unit, double>, 4> seconds_per_unit_{
        {{Duration::Unit::kMilliseconds, Duration::kSecondsPerMillisecond},
         {Duration::Unit::kSeconds, 1.0},
         {Duration::Unit::kMinutes, Duration::kSecondsPerMinute},
         {Duration::Unit::kHours, Duration::kSecondsPerHour}}};
};

constexpr double Duration::Get(Unit to_unit) const noexcept {
    if (to_unit == unit_) {
        return value_;
    } else {
        auto ratio = GetRatio(to_unit);
        return value_ * ratio;
    }
}

}  // namespace helpers::math
