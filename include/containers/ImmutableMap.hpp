#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

namespace helpers::containers {

/// @brief ImmutableMap is an associative container (ie stores key/value pairs) that cannot be modified. Constructed
/// from either a std::map or std::unordered_map that have already been populated
/// @tparam _Key key type
/// @tparam _Tp value type
/// @tparam _Compare functor to use for comparison
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>>
class ImmutableMap {
 public:
  using key_type       = _Key;
  using mapped_type    = _Tp;
  using key_compare    = _Compare;
  using value_type     = std::pair<const _Key, _Tp>;
  using size_type      = size_t;
  using container      = std::vector<std::pair<key_type, mapped_type>>;
  using const_iterator = typename container::const_iterator;

  /// @brief
  /// @tparam _MapCompare Functor used for comparisons in a std::map
  /// @param input_map A populated std::map
  template <typename _MapCompare>
  explicit ImmutableMap(const std::map<key_type, mapped_type, _MapCompare>& input_map);

  /// @brief
  /// @tparam _Hash Functor used for computing the has in a std::unordered_map
  /// @param input_map A populated std::unordered_map
  template <typename _Hash>
  explicit ImmutableMap(const std::unordered_map<_Key, _Tp, _Hash>& input_map);

  ImmutableMap(const ImmutableMap&) = delete;
  ImmutableMap(ImmutableMap&&)      = delete;
  ImmutableMap& operator=(const ImmutableMap&) = delete;
  ImmutableMap& operator=(ImmutableMap&&) = delete;

  ~ImmutableMap() = default;

  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  const mapped_type& at(const key_type& key) const;
  const mapped_type& operator[](const key_type& key) const;

  bool      empty() const noexcept;
  size_type size() const noexcept;
  size_type count(const key_type& key) const noexcept;

 private:
  /// @brief
  /// @param
  /// @param
  /// @param
  /// @return
  /// @throw
  const mapped_type& FindElement(size_type lo, size_type hi, const key_type& key) const;

  /// @brief
  /// @param
  /// @param
  /// @param
  /// @return
  bool DoesElementExist(size_type lo, size_type hi, const key_type& key) const noexcept;

  container map_;
};

template <typename _Key, typename _Tp, typename _Compare>
template <typename _MapCompare>
ImmutableMap<_Key, _Tp, _Compare>::ImmutableMap(const std::map<key_type, mapped_type, _MapCompare>& input_map) {
  map_.reserve(input_map.size());

  for (const auto& value : input_map) {
    map_.push_back(value);
  }

  if constexpr (!std::is_same<key_compare, typename std::map<_Key, _Tp, _MapCompare>::key_compare>::value) {
    std::sort(map_.begin(), map_.end(),
              [](const value_type& lhs, const value_type& rhs) -> bool { return _Compare()(lhs.first, rhs.first); });
  }
}

template <typename _Key, typename _Tp, typename _Compare>
template <typename _Hash>
ImmutableMap<_Key, _Tp, _Compare>::ImmutableMap(const std::unordered_map<_Key, _Tp, _Hash>& input_map) {
  map_.reserve(input_map.size());

  for (const auto& value : input_map) {
    map_.push_back(value);
  }

  std::sort(map_.begin(), map_.end(),
            [](const value_type& lhs, const value_type& rhs) -> bool { return _Compare()(lhs.first, rhs.first); });
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::begin() const noexcept -> const_iterator {
  return map_.begin();
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::end() const noexcept -> const_iterator {
  return map_.end();
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::at(const key_type& key) const -> const mapped_type& {
  return FindElement(0, map_.size(), key);
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::operator[](const key_type& key) const -> const mapped_type& {
  return this->at(key);
}

template <typename _Key, typename _Tp, typename _Compare>
bool ImmutableMap<_Key, _Tp, _Compare>::empty() const noexcept {
  return map_.empty();
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::size() const noexcept -> size_type {
  return map_.size();
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::count(const key_type& key) const noexcept -> size_type {
  return static_cast<size_type>(DoesElementExist(0, map_.size(), key));
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::FindElement(size_type lo, size_type hi, const key_type& key) const
    -> const mapped_type& {
  if (hi == lo) {
    throw std::out_of_range("");
  }

  const auto mid = (lo + hi) / 2;

  if (map_[mid].first == key) {
    return map_[mid].second;
  }

  if (_Compare()(key, map_[mid].first)) {
    return FindElement(lo, mid, key);
  } else {
    return FindElement(mid + 1, hi, key);
  }
}

template <typename _Key, typename _Tp, typename _Compare>
bool ImmutableMap<_Key, _Tp, _Compare>::DoesElementExist(size_type lo, size_type hi,
                                                         const key_type& key) const noexcept {
  if (hi == lo) {
    return false;
  }

  const auto mid = (lo + hi) / 2;

  if (map_[mid].first == key) {
    return true;
  }

  if (_Compare()(key, map_[mid].first)) {
    return DoesElementExist(lo, mid, key);
  } else {
    return DoesElementExist(mid + 1, hi, key);
  }
}

}  // namespace helpers::containers