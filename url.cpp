#include <regex>
#include <iostream>
#include <utility>

#include "url.h"

URL::URL(const std::string &url, const unsigned int &offs,
                                    const unsigned int &l) :
    url(url), offset(offs), length(l)
{}

URL::URL(const std::string &url, status stat) :
    url(url), stat(stat)
{}

bool URL::isURL(const std::string &url) {
    std:: string prefix("http://");
    return url.compare(0, prefix.size(), prefix) == 0;
}

std::ostream& operator<<(std::ostream &os, const URL &url) {
    os << url.url << " -> ";
    switch (url.stat) {
        case READY:
            os << "ready";
            break;
        case EXPLORED:
            os << "explored";
            break;
        case DEAD:
            os << "dead";
    }
    return os;
}

bool URL::isSubdomainOf(const std::string &url, const std::string &domain) {
    return std::regex_match(url,
            std::regex("(^|^[^:]+:\\/\\/|[^\\.]+\\.)" + domain + ".*"));
}

unsigned int URL::getOffset() const {
    return this->offset;
}

unsigned int URL::getFinalOffset() const {
    return this->offset + this->length;
}

bool URL::explore() {
    {
        std::lock_guard<std::mutex> lock(m);
        if (this->stat == READY) {
            this->stat = EXPLORED;
        }
        return true;
    }
    return false;
}

bool URL::isReady() const {
    return this->stat == READY;
}

bool URL::operator<(const URL& other) const {
    return this->url < other.url;
}

URL::URL(URL&& other) {
    if (this == &other) {
        url = std::move(other.url);
        offset = other.offset;
        length = other.length;
        stat = other.stat;
    }
}

URL& URL::operator=(URL&& other) {
    if (this == &other) {
        url = std::move(other.url);
        offset = other.offset;
        length = other.length;
        stat = other.stat;
    }
    return *this;
}
