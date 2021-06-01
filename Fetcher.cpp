#include <fstream>
#include <string>
#include <utility>

#include "Fetcher.h"
#include "url.h"

Fetcher::Fetcher(const char *filename) {
    std::string url;
    int offset, length;
    std::ifstream findex(filename);

    if (!findex.is_open()) {
        std::cout << "Se abrió mal el archivo index" << std::endl;
    }

    while (findex >> url >> std::hex >> offset >> std::hex >> length) {
        index.emplace(std::piecewise_construct,
          std::forward_as_tuple(url),
          std::forward_as_tuple(url, offset, length));
    }
}

URL& Fetcher::fetch(std::string url) {
    std::lock_guard<std::mutex> lock(m);
    if (!index.count(url)) {
        index.emplace(std::piecewise_construct,
          std::forward_as_tuple(url),
          std::forward_as_tuple(url, status::DEAD));
    }
    return index.at(url);
}

std::ostream& operator<<(std::ostream &os, const Fetcher &other) {
    for (auto &url : other.index) {
        if (!url.second.isReady()) {
            std::cout << url.second << std::endl;
        }
    }
    return os;
}

Fetcher::Fetcher(Fetcher&& other) {
    if (this == &other) {
        index = std::move(other.index);
    }
}

Fetcher& Fetcher::operator=(Fetcher&& other) {
    if (this == &other) {
        index = std::move(other.index);
    }
    return *this;
}
