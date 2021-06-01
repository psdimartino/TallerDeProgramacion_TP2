#include <string>
#include <utility>
#include <iostream>
#include "SafeQueue.h"

SafeQueue::SafeQueue() : isAlive(true) {}

bool SafeQueue::pop(std::string &value) {
    std::unique_lock<std::mutex> lg(m);
    while (q.empty()) {
        cv.wait(lg);
        if (!isAlive) return false;
    }
    value = std::move(q.front());
    q.pop();
    return true;
}

void SafeQueue::emplace(std::string value) {
    {
        std::lock_guard<std::mutex> lock(m);
        q.emplace(value);
    }
    cv.notify_one();
}

void SafeQueue::kill() {
    isAlive = false;
    cv.notify_all();
}

SafeQueue::SafeQueue(SafeQueue&& other) {
    if (this == &other) {
        q = std::move(other.q);
    }
}

SafeQueue& SafeQueue::operator=(SafeQueue&& other) {
    if (this == &other) {
        q = std::move(other.q);
    }
    return *this;
}
