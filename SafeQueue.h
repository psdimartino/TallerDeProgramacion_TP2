#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class SafeQueue {
private:
    std::queue<std::string> q;
    std::mutex m;
    std::condition_variable cv;
    std::atomic<bool> isAlive;
public:
    bool pop(std::string &value);
    void emplace(std::string value);
    void kill();

    SafeQueue& operator=(const SafeQueue&) = delete;
    SafeQueue& operator=(SafeQueue&& other);
    SafeQueue(SafeQueue&& other);
    SafeQueue();
};

#endif  // SAFEQUEUE_H_
