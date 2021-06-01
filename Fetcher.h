#ifndef FETCHER_H_
#define FETCHER_H_

#include <iostream>
#include <map>
#include <mutex>
#include <condition_variable>
#include <string>

#include "url.h"

class Fetcher {
 private:
    std::map<std::string, URL> index;
    std::mutex m;
    std::condition_variable cv;
 public:
    explicit Fetcher(const char *filename);
    friend std::ostream& operator<<(std::ostream &os, const Fetcher &other);
    URL& fetch(std::string url);

    Fetcher& operator=(const Fetcher&) = delete;
    Fetcher& operator=(Fetcher&& other);
    Fetcher(Fetcher&& other);
};

#endif  // FETCHER_H_
