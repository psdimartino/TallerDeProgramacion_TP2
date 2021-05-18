#include <regex>
#include <iostream>

#include "url.h"

URL::URL(const std::string &url, const unsigned int &offs, const unsigned int &l) :
    url(url), offset(offs), length(l)
{}

bool URL::isURL(const std::string &url) {
    return std::regex_match(url, std::regex("http://.*"));
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
    return std::regex_match(url, std::regex("(^|^[^:]+:\\/\\/|[^\\.]+\\.)" + domain + ".*"));
}

unsigned int URL::getOffset() {
    return this->offset;
}

unsigned int URL::getFinalOffset() {
    return this->offset + this->length;
}

void URL::setDead() {
    this->stat = DEAD;
}
void URL::setExplored() {
    this->stat = EXPLORED;
}

bool operator<(const URL& a, const URL& b) {
    return a.url < b.url;
}

URL::URL(URL&& other) {
    this->url = other.url;
    this->offset = other.offset;
    this->length = other.length;
    this->stat = other.stat;
}

URL& URL::operator=(URL&& other) {
    this->url = other.url;
    this->offset = other.offset;
    this->length = other.length;
    this->stat = other.stat;
    return *this;
}