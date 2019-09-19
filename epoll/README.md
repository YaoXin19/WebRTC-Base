### 基础
- muduo采用水平触发
- epoll : event poll
- interest list(兴趣列表)和ready list(就序列表)，后者是前者的子集
### 接口
#### epoll_create
```
#include <sys/epoll.h>
int epoll_create(int size);
epoll_create1
```

#### epoll_ctl
```
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev);
```

#### epoll_wait
```
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *evlist, int maxevents, int timeout);
```