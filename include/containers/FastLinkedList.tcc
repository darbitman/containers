#include "FastLinkedList.hpp"

namespace helpers::containers {

template <typename _Tp, size_t _N>
FastLinkedList<_Tp, _N>::FastLinkedList() : FastLinkedList(0) {}

template <typename _Tp, size_t _N>
FastLinkedList<_Tp, _N>::FastLinkedList(const _Tp& default_value)
    : list_{},
      p_start_node_(list_.end()),
      p_end_node_(list_.end()),
      p_next_available_node_(&list_.back()),
      num_nodes_(0) {
  static_assert(_N != 0);
  Initialize(default_value);
}

template <typename _Tp, size_t _N>
auto FastLinkedList<_Tp, _N>::front() -> reference {
  return *p_next_available_node_;
}

template <typename _Tp, size_t _N>
auto FastLinkedList<_Tp, _N>::front() const -> const_reference {
  return *p_next_available_node_;
}

template <typename _Tp, size_t _N>
bool FastLinkedList<_Tp, _N>::empty() const noexcept {
  return p_start_node_ == p_end_node_;
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
  p_start_node_          = list_.end();
  p_end_node_            = list_.end();
  p_next_available_node_ = &list_.back();
  num_nodes_             = 0;
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::push_front(const _Tp& value) {
  // only add element if list isn't full
  if (p_next_available_node_ != p_end_node_) {
    // save the next available node after the current one has been used up
    auto* p_next_available_node = p_next_available_node_->p_next_node;

    // assign value, then update the pointer of the current node to point at the node that p_start_node_ was previously
    // pointing at
    p_next_available_node_->value       = value;
    p_next_available_node_->p_next_node = p_start_node_;

    // update the p_start_node_ pointer to point at the new node
    p_start_node_ = p_next_available_node_;

    // the next available available node will now be assigned the saved value
    p_next_available_node_ = p_next_available_node;

    ++num_nodes_;
  }
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::push_front(_Tp&& value) {
  // only add element if list isn't full
  if (p_next_available_node_ != p_end_node_) {
    // save the next available node after the current one has been used up
    auto* p_next_available_node = p_next_available_node_->p_next_node;

    // assign value, then update the pointer of the current node to point at the node that p_start_node_ was previously
    // pointing at
    p_next_available_node_->value       = std::move(value);
    p_next_available_node_->p_next_node = p_start_node_;

    // update the p_start_node_ pointer to point at the new node
    p_start_node_ = p_next_available_node_;

    // the next available available node will now be assigned the saved value
    p_next_available_node_ = p_next_available_node;

    ++num_nodes_;
  }
}

template <typename _Tp, size_t _N>
template <typename... _Args>
auto FastLinkedList<_Tp, _N>::emplace_front(_Args&&... __args) ->
#if __cplusplus > 201402L
    reference
#else
    void
#endif
{
  // TODO
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::pop_front() {
  if (p_start_node_ != p_end_node_) {
    // save the pointer to the node currently set to be used as the next available node
    auto* p_previous_available_node = p_next_available_node_;

    // the node at the front is the one that will be the next available, so update the pointer
    p_next_available_node_ = p_start_node_;

    // update the pointer to the start node to the next node in the list
    p_start_node_ = p_start_node_->p_next_node;

    // update the pointer in the newly freed node to point to the node that was saved as the 'next available node'
    p_next_available_node_->p_next_node = p_previous_available_node;

    --num_nodes_;
  }
}

template <typename _Tp, size_t _N>
void FastLinkedList<_Tp, _N>::Initialize(const _Tp& default_value) {
  list_.front().value       = default_value;
  list_.front().p_next_node = p_end_node_;

  for (auto reverse_iter = list_.rbegin(), reverse_end = list_.rend(); reverse_iter != (reverse_end - 1);
       ++reverse_iter) {
    reverse_iter->value       = default_value;
    reverse_iter->p_next_node = &(*(reverse_iter + 1));
  }
}

}  // namespace helpers::containers
