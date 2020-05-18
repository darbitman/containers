#pragma once

#include <array>
#include <cstddef>
#include <forward_list>

namespace helpers::containers {

template <typename _Tp, size_t _N>
class FastLinkedList {
 public:
  using value_type      = _Tp;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using size_type       = size_t;

  FastLinkedList();

  explicit FastLinkedList(const _Tp& default_value);

  reference front();

  const_reference front() const;

  bool empty() const noexcept;

  bool full() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  void clear() noexcept;

  void clear(const _Tp& default_value) noexcept;

  void push_front(const _Tp& value);

  void push_front(_Tp&& value);

  void pop_front();

  void remove(const _Tp& value);

 private:
  struct Node {
    value_type value;
    size_type  p_next_node = _N;
  };

  void Initialize(const _Tp& default_value);

  void ReturnToAvailableNodesList(size_type p_new_available_node);

  std::array<Node, _N> list_;

  // when the list is empty, this points at the end
  size_type p_start_node_;

  // will always point one past the last element in the list_ container; "tail" will always be the
  // last element in the list_ container
  const size_type p_end_node_;

  size_type p_next_available_node_;

  size_type num_nodes_;
};

}  // namespace helpers::containers

#include "FastLinkedList.tcc"