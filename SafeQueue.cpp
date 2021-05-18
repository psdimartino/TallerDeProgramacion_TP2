#include "SafeQueue.h"

SafeQueue::SafeQueue(){}

SafeQueue::~SafeQueue() {}

bool SafeQueue::pop(std::string &value) {
    std::lock_guard<std::mutex> lock(m);
    if (q.empty())
        return false;
    value = std::move(q.front());
    q.pop();
    return true;
}

void SafeQueue::emplace(std::string value) {
    std::lock_guard<std::mutex> lock(m);
    q.emplace(std::move(value));
}