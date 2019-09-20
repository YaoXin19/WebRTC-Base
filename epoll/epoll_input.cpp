
#include <cstdio>

#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 1000    // Maximum bytes fetched by a single read()
#define MAX_EVENTS 5    // Maximum number of events to be returned from a single epoll_wait() call

int main(int argc, char* argv[]) {
    int fd;
    int numOpenFds = argc - 1;

    struct epoll_event ev;
    struct epoll_event evlist[MAX_EVENTS];

    char buf[MAX_BUF];

    // Step 1 : 创建一个epoll实例
    int epfd = epoll_create(argc - 1);
    // if (-1 == epfd)

    // Step 2 : 打开命令行参数指定的每个文件
    for (int j=0; j<argc; ++j) {
        fd = open(argv[j], O_RDONLY);
        // if (-1 == fd)
        printf("Opened \"%s\" on fd %d\n", argv[j], fd);

        // Setp 3 : 添加到Epoll的兴趣列表中
        ev.events = EPOLLIN;
        ev.data.fd = fd;
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        }
    }

    // Step 4 : epoll_wait从兴趣列表中获取就绪列表
    int ready = -1;
    while (0 < numOpenFds) {
        printf("About to epoll_wait()\n");
        ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        if (-1 == ready) {
            if (errno == EINTR) {
                continue; // Restart if interrupted by signal
            } else {
            }
        }
        printf("Ready: %d\n", ready);

        // Step 7
        for (int j=0; j<ready; ++j) {
            //printf("");
            // Step 8
            if (evlist[j].events & EPOLLIN) {

            } else if (evlist[j].events & (EPOLLHUP | EPOLLERR)) { // Step 9

            }
        }
    }

    printf("All file descriptors closed; bye\n");
    return 0;
}