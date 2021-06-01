#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include "MultithreadedCrawler.h"
#include "Thread.h"
#include "Crawler.h"

void MultithreadedCrawler::run(const unsigned int nThreads,
                                 const unsigned int nSeconds) {
    std::vector<Thread*> threads;
    for (unsigned i = 0; i < nThreads; ++i) {
        Thread *t = new Crawler(fetcher, targets, pages, allowed);
        t->start();
        threads.push_back(t);
    }

    std::chrono::milliseconds timespan(nSeconds*1000);
    std::this_thread::sleep_for(timespan);
    targets.kill();

    for (Thread  *thread : threads) {
        thread->join();
        delete thread;
    }

    std::cout << fetcher;
}

MultithreadedCrawler&
MultithreadedCrawler::operator=(MultithreadedCrawler&& other) {
    if (this == &other) {
        targets = std::move(other.targets);
        fetcher = std::move(other.fetcher);
        allowed = other.allowed;
        pages = other.pages;
    }
    return *this;
}

MultithreadedCrawler::MultithreadedCrawler(const char *target,
                     const char *index,
                     const char *pages,
                     const char *allowed) :
    fetcher(Fetcher(index)),
    allowed(allowed),
    pages(pages) {
    std::ifstream ftargets(target);
    if (!ftargets.is_open()) {
        std::cout << "Se abrió mal el archivo targets" << std::endl;
    }
    std::string str;
    while (ftargets >> str) {
        targets.emplace(str);
    }
}
