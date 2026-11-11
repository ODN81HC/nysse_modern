#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() = default;

    bool push(T item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (shutdown_flag_)
        {
            return false;
        }
        queue_.push(std::move(item));
        cv_.notify_one();
        return true;
    };

    std::optional<T> pop()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() {
            return !queue_.empty() || shutdown_flag_;
        });
        if (!queue_.empty())
        {
            auto item = std::move(queue_.front());
            queue_.pop();
            return item;
        }
        else if (shutdown_flag_)
        {
            return std::nullopt;
        }
        return std::nullopt;
    };

    void request_stop()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        shutdown_flag_ = true;
        cv_.notify_all();
    };

    [[nodiscard]] bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    };

    [[nodiscard]] size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    };

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    bool shutdown_flag_ = false;
};