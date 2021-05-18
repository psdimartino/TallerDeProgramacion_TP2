#ifndef FETCHER_H_
#define FETCHER_H_

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <string>

#include "url.h"
#include "Thread.h"
#include "SafeQueue.h"

class Fetcher : public Thread {
 private:
    std::map<std::string, URL> &index;
    SafeQueue &targets;
    std::vector<URL> &result;
    std::ifstream &fpages;
    const std::string &allowed;
 public:
    explicit Fetcher(std::map<std::string, URL> &index,
                        SafeQueue &targets,
                        std::vector<URL> &result,
                        std::ifstream &fpages,
                        const std::string &allowed);
    virtual void run() override;
};

#endif  // FETCHER_H_
