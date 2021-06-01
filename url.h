#ifndef URL_H_
#define URL_H_

#include <mutex>
#include <string>

enum status { READY, EXPLORED, DEAD };

class URL {
 private:
    std::string url;
    unsigned int offset = 0;
    unsigned int length = 0;
    status stat = READY;
    std::mutex m;

 public:
    static bool isURL(const std::string &url);
    static bool isSubdomainOf(const std::string &url,
                                 const std::string &domain);

    URL(const std::string &url, const unsigned int &offset,
                                 const unsigned int &length);
    URL(const std::string &url, status stat);
    friend std::ostream& operator<<(std::ostream &os, const URL &other);
    bool explore();
    bool isReady() const;
    unsigned int getOffset() const;
    unsigned int getFinalOffset() const;
    bool operator<(const URL &b) const;
    URL& operator=(const URL&) = delete;
    URL& operator=(URL&& other);
    URL(URL&& other);
};

#endif  // URL_H_
