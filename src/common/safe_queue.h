// safe_queue.h   21/08/2022
/* ========================================================================== */
#pragma once

/* ========================================================================== */
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

/* ========================================================================== */
template <class T>
class SafeQueue {
 public:
  SafeQueue() : values_(), mutex_(), cv_() {}
  ~SafeQueue() {}

 public:
  /* ======================================================================= */
  void push(T t) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      values_.push(t);
    }

    cv_.notify_one();
  }

  /* ======================================================================= */
  std::optional<T> pop() {
    std::unique_lock<std::mutex> lock(mutex_);

    if (cv_.wait_for(lock, std::chrono::milliseconds(500),
                     [this] { return !values_.empty(); })) {
      auto value = std::move(values_.front());
      values_.pop();
      return value;

    } else {
      return std::nullopt;
    }
  }

  /* ======================================================================= */
  bool is_empty() { return values_.empty(); }

 private:
  std::queue<T> values_;
  mutable std::mutex mutex_;
  std::condition_variable cv_;
};

/* ========================================================================== */
