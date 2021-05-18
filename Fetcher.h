#ifndef FETCHER_H_
#define FETCHER_H_

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

#include "url.h"

class Fetcher {
 private:
    std::map<std::string, URL> &index;
    std::queue<std::string> &targets;
    std::vector<URL> &result;
    std::ifstream &fpages;
    std::string allowed;
 public:
    explicit Fetcher(   std::map<std::string, URL> &index,
                        std::queue<std::string> &targets,
                        std::vector<URL> &result,
                        std::ifstream &fpages,
                        std::string allowed);
    void run();
    
};



#endif  // FETCHER_H_
