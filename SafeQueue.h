#ifndef SAFEQUEUE_H_
#define SAFEQUEUE_H_

#include <queue>
#include <mutex>

class SafeQueue {
private:
    std::queue<std::string> q;
    std::mutex m;
public:
    SafeQueue();
    ~SafeQueue();
    bool pop(std::string &value);
    void emplace(std::string value);
};

#endif  // SAFEDQUEUE_H_