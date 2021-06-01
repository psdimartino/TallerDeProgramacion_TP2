#include "MultithreadedCrawler.h"

int main(int argc, char *argv[]) {
    // 0./tp 1<targets> 2<allowed> 3<w> 4<index> 5<pages> 6<n>

    MultithreadedCrawler crawler(argv[1], argv[4], argv[5], argv[2]);

    crawler.run(atoi(argv[3]), atoi(argv[6]));

    return 0;
}
