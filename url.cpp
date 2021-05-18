#include <regex>

#include "url.h"

URL::URL(std::string url, unsigned int offs, unsigned int l) :
    url(url), offset(offs), length(l)
{}

bool URL::isUrl(std::string url) {
    return std::regex_match(url, std::regex("http://.*"));
}

std::ostream& operator<<(std::ostream& os, const URL& url) {
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

bool URL::isSubdomainOf(std::string url, std::string domain) {
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