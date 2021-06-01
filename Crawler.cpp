#include <string>
#include <utility>
#include "Crawler.h"

#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define NC "\033[0m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"

Crawler::Crawler(Fetcher &fetcher,
                    SafeQueue &targets,
                    const char *filename,
                    const char *allowed) :
    fetcher(fetcher), targets(targets), allowed(allowed) {
    this->fpages = std::ifstream(filename);
    if (!fpages.is_open()) {
        std::cout << "Se abrió mal el archivo pages" << std::endl;
    }
}

void Crawler::explore(const URL& url) {
    fpages.seekg(url.getOffset());
    std::string str;
    while (fpages.tellg() < url.getFinalOffset() && fpages >> str) {
        if (URL::isURL(str) && URL::isSubdomainOf(str, allowed)) {
            targets.emplace(std::move(str));
        }
    }
}

void Crawler::run() {
    std::string actual;
    while (targets.pop(actual)) {
        URL &url = fetcher.fetch(actual);
        if (url.explore()) {
            explore(url);
        }
    }
}
