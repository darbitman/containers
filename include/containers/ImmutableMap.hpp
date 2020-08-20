#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

namespace helpers::containers {

/// @brief ImmutableMap is an ordered associative container (ie stores key/value pairs) that cannot be modified.
/// Constructed from either a std::map or std::unordered_map that have already been populated
/// @tparam _Key key type
/// @tparam _Tp value type
/// @tparam _Compare functor to use for comparison
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>>
class ImmutableMap {
 public:
  using key_type        = _Key;
  using mapped_type     = _Tp;
  using key_compare     = _Compare;
  using value_type      = std::pair<_Key, _Tp>;
  using size_type       = size_t;
  using const_reference = const mapped_type&;

  class const_iterator {
   public:
    const_iterator(const value_type* v) noexcept;
    const_iterator(const const_iterator&) = default;
    const_iterator(const_iterator&&)      = default;
    const_iterator& operator=(const const_iterator&) = default;
    const_iterator& operator=(const_iterator&&) = default;
    ~const_iterator() noexcept                  = default;

    bool operator!=(const const_iterator& rhs) const noexcept;

    const value_type& operator*() const noexcept;
    const value_type* operator->() const noexcept;
    const_iterator&   operator++() noexcept;

   private:
    const value_type* p_value_;
  };

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

  const_reference at(const key_type& key) const;
  const_reference operator[](const key_type& key) const;

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
  const_reference FindElement(size_type lo, size_type hi, const key_type& key) const;

  /// @brief
  /// @param
  /// @param
  /// @param
  /// @return
  bool DoesElementExist(size_type lo, size_type hi, const key_type& key) const noexcept;

  _Compare comp_;

  std::vector<value_type> map_;
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
              [&](const value_type& lhs, const value_type& rhs) -> bool { return comp_(lhs.first, rhs.first); });
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
            [&](const value_type& lhs, const value_type& rhs) -> bool { return comp_(lhs.first, rhs.first); });
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::begin() const noexcept -> const_iterator {
  return const_iterator(map_.data());
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::end() const noexcept -> const_iterator {
  return const_iterator(map_.data() + map_.size());
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::at(const key_type& key) const -> const_reference {
  return FindElement(0, map_.size(), key);
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::operator[](const key_type& key) const -> const_reference {
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
    -> const_reference {
  if (hi == lo) {
    throw std::out_of_range("");
  }

  const auto mid = (lo + hi) / 2;

  if (map_[mid].first == key) {
    return map_[mid].second;
  }

  if (comp_(key, map_[mid].first)) {
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

  if (comp_(key, map_[mid].first)) {
    return DoesElementExist(lo, mid, key);
  } else {
    return DoesElementExist(mid + 1, hi, key);
  }
}

template <typename _Key, typename _Tp, typename _Compare>
ImmutableMap<_Key, _Tp, _Compare>::const_iterator::const_iterator(const value_type* p_value) noexcept
    : p_value_(p_value) {}

template <typename _Key, typename _Tp, typename _Compare>
bool ImmutableMap<_Key, _Tp, _Compare>::const_iterator::operator!=(const const_iterator& rhs) const noexcept {
  return this->p_value_ != rhs.p_value_;
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::const_iterator::operator*() const noexcept -> const value_type& {
  return *p_value_;
}

template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::const_iterator::operator->() const noexcept -> const value_type* {
  return p_value_;
}
template <typename _Key, typename _Tp, typename _Compare>
auto ImmutableMap<_Key, _Tp, _Compare>::const_iterator::operator++() noexcept -> const_iterator& {
  ++p_value_;
  return *this;
}

}  // namespace helpers::containers