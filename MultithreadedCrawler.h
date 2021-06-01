#ifndef MULTITHREADEDCRAWLER_H_
#define MULTITHREADEDCRAWLER_H_

#include "Fetcher.h"
#include "SafeQueue.h"

class MultithreadedCrawler {
private:
    SafeQueue targets;
    Fetcher fetcher;
    const char *allowed;
    const char *pages;

public:
    void run(const unsigned int nThreads, const unsigned int nSeconds);

    MultithreadedCrawler& operator=(const MultithreadedCrawler&) = delete;
    MultithreadedCrawler& operator=(MultithreadedCrawler&& other);
    MultithreadedCrawler(const char *target,
                         const char *index,
                         const char *pages,
                         const char *allowed);
};

#endif  // MULTITHREADEDCRAWLER_H_
