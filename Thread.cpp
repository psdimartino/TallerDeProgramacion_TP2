#include "Thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::run,  this);
}

void Thread::join() {
    thread.join();
}

Thread::~Thread() {}

Thread::Thread(Thread&& other) {
    if (this == &other) {
        this->thread = std::move(other.thread);
    }
}

Thread& Thread::operator=(Thread&& other) {
    if (this == &other) {
        this->thread = std::move(other.thread);
    }
    return *this;
}
