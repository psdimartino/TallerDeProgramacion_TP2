#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

#include "url.h"

int main (int argc, char *argv[]) {
    std::map<std::string, URL> index;
    std::queue<std::string> targets;
    std::string str;
    std::vector<URL> result;
    int offset, length;
    // ./tp test/counters/target free-counters.co.uk 1 test/counters/index test/counters/pages 3
    // ./tp <targets> <allowed> <w> <index> <pages> <n>

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
        URL _url(str, offset, length);
        index.insert({str, _url});
        // if (_url.isSubdomainOf([2])) {
            // std::cout << index.at(str) << std::endl;
        // }
    }

    while (ftargets >> str) {
        targets.emplace(str);
    }

    while (!targets.empty()) {
        std::string actual = targets.front();
        targets.pop();
        if (index.count(actual) == 0) {  // Si no esta, DEAD y salteo
            URL url(actual, 0, 0);
            url.setDead();
            result.push_back(url);
            continue;
        }
        URL url = index.at(actual);  // Si esta, proceso
        fpages.seekg(url.getOffset());
        while(fpages.tellg() < url.getFinalOffset() && fpages >> str) {
            if (URL::isUrl(str) && URL::isSubdomainOf(str, argv[2])) { // URL validas para buscar
                targets.emplace(str);
            }
        }
        url.setExplored();
        result.push_back(url);
    }

    std::sort(result.begin(), result.end());

    for ( URL url : result) {
        std::cout << url << std::endl;
    }
    return 0;
}
