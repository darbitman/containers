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
    size_type  next_node_idx = _N;
  };

  void Initialize(const _Tp& default_value);

  void ReturnToAvailableNodesList(size_type node_idx);

  std::array<Node, _N> list_;

  // when the list is empty, this points at the end
  size_type start_node_idx_;

  // will always point one past the last element in the list_ container; "tail" will always be the
  // last element in the list_ container
  const size_type end_node_idx_;

  size_type next_available_node_idx_;

  size_type num_nodes_;
};

}  // namespace helpers::containers

// *********************************************************************************************************************
// *********************************************************************************************************************
// *********************************************************************************************************************

namespace helpers::containers {

template <typename _Tp, size_t _N>
FastLinkedList<_Tp, _N>::FastLinkedList() : FastLinkedList(0) {}

template <typename _Tp, size_t _N>
FastLinkedList<_Tp, _N>::FastLinkedList(const _Tp& default_value)
    : list_{}, start_node_idx_(_N), end_node_idx_(_N), next_available_node_idx_(_N - 1), num_nodes_(0) {
  static_assert(_N != 0);
  Initialize(default_value);
}

template <typename _Tp, size_t _N>
auto FastLinkedList<_Tp, _N>::front() -> reference {
  return list_.at(start_node_idx_).value;
}

template <typename _Tp, size_t _N>
auto FastLinkedList<_Tp, _N>::front() const -> const_reference {
  return list_.at(start_node_idx_).value;
}

template <typename _Tp, size_t _N>
bool FastLinkedList<_Tp, _N>::empty() const noexcept {
  return start_node_idx_ == end_node_idx_;
}

template <typename _Tp, size_t _N>
bool FastLinkedList<_Tp, _N>::full() const noexcept {
  return num_nodes_ == _N;
}

template <typename _Tp, size_t _N>
auto FastLinkedList<_Tp, _N>::size() const noexcept -> size_type {
  return num_nodes_;
}

template <typename _Tp, size_t _N>
auto FastLinkedList<_Tp, _N>::max_size() const noexcept -> size_type {
  return _N;
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::clear() noexcept {
  clear(_Tp{});
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::clear(const _Tp& default_value) noexcept {
  Initialize(default_value);

  start_node_idx_          = _N;
  next_available_node_idx_ = _N - 1;
  num_nodes_               = 0;
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::push_front(const _Tp& value) {
  if (!full()) {
    // save the next available node after the current one has been used up
    auto new_next_available_node_idx = list_.at(next_available_node_idx_).next_node_idx;

    // assign value
    // then update the pointer of the current node to point at the node that start_node_idx_ was previously pointing at
    // finally, update the start_node_idx_ pointer to point at the new node
    list_.at(next_available_node_idx_).value         = value;
    list_.at(next_available_node_idx_).next_node_idx = start_node_idx_;
    start_node_idx_                                  = next_available_node_idx_;

    // the new next_available_node will now be assigned the saved value
    next_available_node_idx_ = new_next_available_node_idx;

    ++num_nodes_;
  }
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::push_front(_Tp&& value) {
  if (!full()) {
    // save the next available node after the current one has been used up
    auto new_next_available_node_idx = list_.at(next_available_node_idx_).next_node_idx;

    // assign value
    // then update the pointer of the current node to point at the node that start_node_idx_ was previously pointing at
    // finally, update the start_node_idx_ to point at the new node
    list_.at(next_available_node_idx_).value         = std::move(value);
    list_.at(next_available_node_idx_).next_node_idx = start_node_idx_;
    start_node_idx_                                  = next_available_node_idx_;

    // the new next_available_node will now be assigned the saved value
    next_available_node_idx_ = new_next_available_node_idx;

    ++num_nodes_;
  }
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::pop_front() {
  if (!empty()) {
    // save the pointer to the node to be removed
    auto node_to_remove_idx = start_node_idx_;

    // update the pointer to the start node to point at the next node in the list
    start_node_idx_ = list_.at(start_node_idx_).next_node_idx;

    ReturnToAvailableNodesList(node_to_remove_idx);
  }
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::remove(const _Tp& value) {
  if (empty()) {
    return;
  }

  // save pointer to starting node; need a copy because this pointer will be modified while searching
  auto* p_memory_that_stores_idx_to_current_node = &start_node_idx_;

  // checked if list is empty already, so there's at least one node in the list
  do {
    if (list_.at(*p_memory_that_stores_idx_to_current_node).value == value) {
      // save the pointer to the node that will be removed
      // this node will then be added back to list of available nodes for reuse
      auto node_to_remove_idx = (*p_memory_that_stores_idx_to_current_node);

      // update pointer to point at the object AFTER the one that is being removed
      *p_memory_that_stores_idx_to_current_node = list_.at(node_to_remove_idx).next_node_idx;

      // add the node back to the free store
      ReturnToAvailableNodesList(node_to_remove_idx);
    } else {
      // update double pointer
      // this will now store the memory address of the next node's next_node_idx
      p_memory_that_stores_idx_to_current_node = &list_.at(*p_memory_that_stores_idx_to_current_node).next_node_idx;
    }
  } while (*p_memory_that_stores_idx_to_current_node != end_node_idx_);
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::Initialize(const _Tp& default_value) {
  list_.front().value         = default_value;
  list_.front().next_node_idx = end_node_idx_;

  // current node at reverse_index sets its next_node_idx to the node to its left
  // this will initialize the free store
  for (auto reverse_index = _N - 1; reverse_index != 0; --reverse_index) {
    list_.at(reverse_index).value         = default_value;
    list_.at(reverse_index).next_node_idx = reverse_index - 1;
  }
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::ReturnToAvailableNodesList(size_type node_idx) {
  list_.at(node_idx).next_node_idx = next_available_node_idx_;
  next_available_node_idx_         = node_idx;

  --num_nodes_;
}

}  // namespace helpers::containers
