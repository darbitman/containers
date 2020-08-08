#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

namespace helpers::containers {

template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>>
class ImmutableMap {
 public:
  using key_type       = _Key;
  using mapped_type    = _Tp;
  using value_type     = std::pair<const _Key, _Tp>;
  using size_type      = size_t;
  using container      = std::vector<std::pair<key_type, mapped_type>>;
  using const_iterator = typename container::const_iterator;

  explicit ImmutableMap(const std::map<_Key, _Tp>& input_map) {
    sorted_vector_.reserve(input_map.size());

    for (const auto& value : input_map) {
      sorted_vector_.push_back(value);
    }
  }

  explicit ImmutableMap(const std::unordered_map<_Key, _Tp>& input_map) {
    sorted_vector_.reserve(input_map.size());

    for (const auto& value : input_map) {
      sorted_vector_.push_back(value);
    }

    std::sort(sorted_vector_.begin(), sorted_vector_.end(),
              [](const value_type& lhs, const value_type& rhs) -> bool { return _Compare()(lhs.first, rhs.first); });
  }

  const_iterator begin() const noexcept { return sorted_vector_.begin(); }

  const_iterator end() const noexcept { return sorted_vector_.end(); }

  const mapped_type& at(const key_type& key) const {
    if (sorted_vector_.empty()) {
      throw std::out_of_range("");
    }

    return FindElement(0, sorted_vector_.size() - 1, key);
  }

  bool empty() const noexcept { return sorted_vector_.empty(); }

  size_type size() const noexcept { return sorted_vector_.size(); }

  size_type count(const key_type& key) const noexcept {
    return static_cast<size_type>(DoesElementExist(0, sorted_vector_.size() - 1, key));
  }

  ~ImmutableMap() = default;

  ImmutableMap(const ImmutableMap&) = delete;
  ImmutableMap(ImmutableMap&&)      = delete;
  ImmutableMap& operator=(const ImmutableMap&) = delete;
  ImmutableMap& operator=(ImmutableMap&&) = delete;

 private:
  const mapped_type& FindElement(size_type lo, size_type hi, const key_type& key) const {
    if (hi < lo) {
      throw std::out_of_range("");
    }

    const auto mid = (lo + hi) / 2;

    if (sorted_vector_[mid].first == key) {
      return sorted_vector_[mid].second;
    }

    if (_Compare()(key, sorted_vector_[mid].first)) {
      return FindElement(lo, mid - 1, key);
    } else {
      return FindElement(mid + 1, hi, key);
    }
  }

  bool DoesElementExist(size_type lo, size_type hi, const key_type& key) const noexcept {
    if (hi < lo) {
      return false;
    }

    const auto mid = (lo + hi) / 2;

    if (sorted_vector_[mid].first == key) {
      return true;
    }

    if (_Compare()(key, sorted_vector_[mid].first)) {
      return DoesElementExist(lo, mid - 1, key);
    } else {
      return DoesElementExist(mid + 1, hi, key);
    }
  }

  container sorted_vector_;
};

}  // namespace helpers::containers