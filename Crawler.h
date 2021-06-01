#ifndef CRAWLER_H_
#define CRAWLER_H_

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <string>

#include "url.h"
#include "Thread.h"
#include "Fetcher.h"
#include "SafeQueue.h"

class Crawler : public Thread {
 private:
    Fetcher &fetcher;  // map
    SafeQueue &targets;   // queue
    std::ifstream fpages;  // file
    const char *allowed;
 public:
    Crawler(Fetcher &fetcher,
            SafeQueue &targets,
            const char *filename,
            const char *allowed);
    void run() override;
    void explore(const URL& url);

    Crawler& operator=(const Crawler&) = delete;
    Crawler& operator=(Crawler&& other) = delete;
    Crawler(Crawler&& other) = delete;
};

#endif  // CRAWLER_H_
