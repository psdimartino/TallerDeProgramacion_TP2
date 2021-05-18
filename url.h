#ifndef URL_H_
#define URL_H_

#include <string>

#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define NC "\033[0m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"

enum status { READY, EXPLORED, DEAD };

class URL {
 private:
    std::string url;
    unsigned int offset;
    unsigned int length;
    status stat = READY;
 public:
    explicit URL(std::string url, unsigned int offset, unsigned int length);
    static bool isUrl(std::string url);
    static bool isSubdomainOf(std::string url, std::string domain);
    friend std::ostream& operator<<(std::ostream& os, const URL& other);
    void setDead();
    void setExplored();
    unsigned int getOffset();
    unsigned int getFinalOffset();
    friend bool operator<(const URL& a, const URL& b);
};

#endif  // URL_H_
