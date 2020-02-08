#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <type_traits>

namespace ctr::containers {

template <typename _Tp, bool b_blocking = true>
class SharedQueue {
  public:
    SharedQueue() noexcept;

    ~SharedQueue() noexcept;

    bool empty() const;

    size_t size() const;

    _Tp& front();

    const _Tp& front() const;

    _Tp& back();

    const _Tp& back() const;

    void push(const _Tp& value);

    void push(_Tp&& value);

    template <typename... ArgTypes>
    void emplace(ArgTypes&&... args);

    void pop();

    /// Deleted to prevent misuse
    SharedQueue(const SharedQueue&) noexcept = delete;
    SharedQueue(SharedQueue&&) noexcept = delete;
    SharedQueue& operator=(const SharedQueue&) noexcept = delete;
    SharedQueue& operator=(SharedQueue&&) noexcept = delete;

  private:
    /// Used to protect the queue from multiple thread access
    mutable std::mutex mtx_;

    /// Used to block when accessing an empty queue
    mutable std::condition_variable cv_;

    /// Underlying storage container
    std::queue<_Tp> queue_;
};

}  // namespace ctr::containers

#include "SharedQueue.tcc"
