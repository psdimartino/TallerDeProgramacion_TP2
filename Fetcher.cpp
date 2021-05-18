#include <string>
#include <utility>
#include "Fetcher.h"

Fetcher::Fetcher(   std::map<std::string, URL> &index,
                    SafeQueue &targets,
                    std::vector<URL> &result,
                    std::ifstream &fpages,
                    const std::string allowed) :
    index(index),
    targets(targets),
    result(result),
    fpages(fpages),
    allowed(allowed)
{}

void Fetcher::run() {
    std::string actual;
    while (targets.pop(actual)) {
        if (index.count(actual) == 0) {  // Si no esta, DEAD y salteo
            URL url(actual, 0, 0);
            url.setDead();
            result.push_back(std::move(url));
            continue;
        }
        URL url = std::move(index.at(actual));  // Si esta, proceso
        fpages.seekg(url.getOffset());
        std::string str;
        while (fpages.tellg() < url.getFinalOffset() && fpages >> str) {
            if (URL::isURL(str) && URL::isSubdomainOf(str, allowed)) {
                targets.emplace(std::move(str));
            }
        }
        url.setExplored();   
        result.push_back(std::move(url));
    }
}

