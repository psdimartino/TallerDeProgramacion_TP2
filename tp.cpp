#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <thread>

#include "url.h"
#include "Fetcher.h"

int main (int argc, char *argv[]) {
    std::map<std::string, URL> index;
    std::queue<std::string> targets;
    std::string str;
    std::vector<URL> result;
    int offset, length;
    // ./tp test/counters/target free-counters.co.uk 1 test/counters/index test/counters/pages 3
    // ./tp <targets> <allowed> <w> <index> <pages> <n>

    std::cerr << "comenzando..1" << std::endl;
    std::ifstream ftargets(argv[1]);
    if (!ftargets.is_open()) {
        std::cout << "Se abrió mal el archivo targets: " << argv[1] << std::endl;
        return 1;
    }
    std::cerr << "comenzando..2" << std::endl;
    std::ifstream findex(argv[4]);
    if (!findex.is_open()) {
        std::cout << "Se abrió mal el archivo index" << std::endl;
        return 1;
    }
    std::cerr << "comenzando..3" << std::endl;
    std::ifstream fpages(argv[5]);
    if (!fpages.is_open()) {
        std::cout << "Se abrió mal el archivo pages" << std::endl;
        return 1;
    }
    std::cerr << "comenzando..4" << std::endl;
    while (findex >> str >> std::hex >> offset >> std::hex >> length) {
        // URL url(str, offset, length);
        std::cerr << "index: " << str << std::endl;
        index.emplace(str, std::move(URL(str, offset, length)));
    }
    std::cerr << "comenzando..5" << std::endl;
    while (ftargets >> str) {
        targets.emplace(str);
    }

    std::cerr << "main" << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < atoi(argv[3]); i++) {
        Fetcher fetcher(index, targets, result, fpages, argv[2]);
        threads.emplace(std::thread(&Fetcher::run, fetcher));
    }

    std::sort(result.begin(), result.end());

    for (URL &url : result) {
        std::cout << url << std::endl;
    }

    return 0;
}
