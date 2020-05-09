#pragma once

#include <cstdint>

namespace helpers::math {

using UnderlyingEnumType = uint32_t;

template <typename E>
constexpr UnderlyingEnumType ToIndex(E enum_value) {
  return static_cast<UnderlyingEnumType>(enum_value);
}

}  // namespace helpers::math
