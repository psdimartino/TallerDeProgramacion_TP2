#include <thread>
#include <utility>

class Thread {
    private:
        std::thread thread;
 
    public:
        Thread() {}

        void start() {
            thread = std::thread(&Thread::run,  this);
        }

        void join() {
            thread.join();
        }

        virtual void run() = 0; 
 
        virtual ~Thread() {} 
                             
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;
        
        Thread(Thread&& other) {
            this->thread = std::move(other.thread);
        }

        Thread& operator=(Thread&& other) {
            this->thread = std::move(other.thread);
            return *this;
        }
};
