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
            // os << GREEN << "ready" << NC;
            os << "ready";
            break;
        case EXPLORED:
            // os << BLUE << "explored" << NC;
            os << "explored";
            break;
        case DEAD:
            // os << RED << "dead" << NC;
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
    std::cerr << "copy constructor" << std::endl;
    this->url = other.url;
    this->offset = other.offset;
    this->length = other.length;
    this->stat = other.stat;
    // other.url = nullptr;
    // other.offset = other.length = 0;
    std::cerr << "copy constructor end" << std::endl;
}

URL& URL::operator=(URL&& other) {
    std::cerr << "operator=" << std::endl;
    this->url = other.url;
    this->offset = other.offset;
    this->length = other.length;
    this->stat = other.stat;
    // other.url = nullptr;
    // other.offset = other.length = 0;
    return *this;
}