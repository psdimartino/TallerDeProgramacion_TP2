#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <thread>

#include "url.h"
#include "Fetcher.h"
#include "SafeQueue.h"

int main (int argc, char *argv[]) {
    std::map<std::string, URL> index;
    SafeQueue targets;
    std::string str;
    std::vector<URL> result;
    int offset, length;

    std::ifstream ftargets(argv[1]);
    if (!ftargets.is_open()) {
        std::cout << "Se abrió mal el archivo targets: " << argv[1] << std::endl;
        return 1;
    }

    std::ifstream findex(argv[4]);
    if (!findex.is_open()) {
        std::cout << "Se abrió mal el archivo index" << std::endl;
        return 1;
    }

    std::ifstream fpages(argv[5]);
    if (!fpages.is_open()) {
        std::cout << "Se abrió mal el archivo pages" << std::endl;
        return 1;
    }

    while (findex >> str >> std::hex >> offset >> std::hex >> length) {
        index.emplace(str, std::move(URL(str, offset, length)));
    }

    while (ftargets >> str) {
        targets.emplace(str);
    }

    std::vector<Thread*> threads;
    for (int i = 0; i < atoi(argv[3]); ++i) {
        Thread *t = new Fetcher(index, targets, result, fpages, argv[2]);
        t->start();
        threads.push_back(t);
    }

    for (Thread  *thread : threads) {
        thread->join();
        delete thread;
    }

    std::sort(result.begin(), result.end());

    for (URL &url : result) {
        std::cout << url << std::endl;
    }

    return 0;
}
