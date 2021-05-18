#ifndef URL_H_
#define URL_H_

#include <string>

enum status { READY, EXPLORED, DEAD };

class URL {
 private:
    std::string url;
    unsigned int offset;
    unsigned int length;
    status stat = READY;
 public:
    explicit URL(const std::string &url, const unsigned int &offset,
                                          const unsigned int &length);
    URL(URL&& other);
    static bool isURL(const std::string &url);
    static bool isSubdomainOf(const std::string &url,
                                 const std::string &domain);
    friend std::ostream& operator<<(std::ostream &os, const URL &other);
    void setDead();
    void setExplored();
    unsigned int getOffset();
    unsigned int getFinalOffset();
    friend bool operator<(const URL &a, const URL &b);
    URL& operator=(URL&& other);
};

#endif  // URL_H_

