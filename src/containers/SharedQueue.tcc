#include "SharedQueue.hpp"

namespace ctr {

template <typename _Tp, bool b_blocking>
SharedQueue<_Tp, b_blocking>::SharedQueue() noexcept {}

template <typename _Tp, bool b_blocking>
SharedQueue<_Tp, b_blocking>::~SharedQueue() noexcept {}

template <typename _Tp, bool b_blocking>
bool SharedQueue<_Tp, b_blocking>::empty() const {
    std::unique_lock<std::mutex> mlock(mtx_);

    return queue_.empty();
}

template <typename _Tp, bool b_blocking>
size_t SharedQueue<_Tp, b_blocking>::size() const {
    std::unique_lock<std::mutex> mlock(mtx_);

    return queue_.size();
}

template <typename _Tp, bool b_blocking>
_Tp& SharedQueue<_Tp, b_blocking>::front() {
    std::unique_lock<std::mutex> mlock(mtx_);

    // if this is a blocking queue, wait to be notified when when a new object is added
    if constexpr (b_blocking) {
        while (queue_.empty()) {
            cv_.wait(mlock);
        }
    }

    return queue_.front();
}

template <typename _Tp, bool b_blocking>
const _Tp& SharedQueue<_Tp, b_blocking>::front() const {
    std::unique_lock<std::mutex> mlock(mtx_);

    // if this is a blocking queue, wait to be notified when when a new object is added
    if constexpr (b_blocking) {
        while (queue_.empty()) {
            cv_.wait(mlock);
        }
    }

    return queue_.front();
}

template <typename _Tp, bool b_blocking>
_Tp& SharedQueue<_Tp, b_blocking>::back() {
    std::unique_lock<std::mutex> mlock(mtx_);

    if constexpr (b_blocking) {
        while (queue_.empty()) {
            cv_.wait(mlock);
        }
    }

    queue_.back();
}

template <typename _Tp, bool b_blocking>
const _Tp& SharedQueue<_Tp, b_blocking>::back() const {
    std::unique_lock<std::mutex> mlock(mtx_);

    if constexpr (b_blocking) {
        while (queue_.empty()) {
            cv_.wait(mlock);
        }
    }

    queue_.back();
}

template <typename _Tp, bool b_blocking>
void SharedQueue<_Tp, b_blocking>::push(const _Tp& value) {
    std::unique_lock<std::mutex> mlock(mtx_);

    if constexpr (std::is_copy_constructible_v<_Tp>) {
        queue_.push(value);
    } else {
        throw std::invalid_argument("Type _Tp can't be copy constructed");
    }

    if constexpr (b_blocking) {
        if (queue_.size() == 1) {
            cv_.notify_all();
        }
    }
}

template <typename _Tp, bool b_blocking>
void SharedQueue<_Tp, b_blocking>::push(_Tp&& value) {
    std::unique_lock<std::mutex> mlock(mtx_);

    queue_.push(std::move(value));

    if constexpr (b_blocking) {
        if (queue_.size() == 1) {
            cv_.notify_all();
        }
    }
}

template <typename _Tp, bool b_blocking>
template <typename... ArgTypes>
void SharedQueue<_Tp, b_blocking>::emplace(ArgTypes&&... args) {
    std::unique_lock<std::mutex> mlock(mtx_);

    queue_.emplace(std::forward<ArgTypes>(args)...);

    if constexpr (b_blocking) {
        if (queue_.size() == 1) {
            cv_.notify_all();
        }
    }
}

template <typename _Tp, bool b_blocking>
void SharedQueue<_Tp, b_blocking>::pop() {
    std::unique_lock<std::mutex> mlock(mtx_);

    if (!queue_.empty()) {
        queue_.pop();
    }
}

}  // namespace ctr
