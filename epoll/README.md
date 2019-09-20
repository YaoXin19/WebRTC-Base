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

### 数据
#### struct epoll_event
```c++
typedef union epoll_data
{
  void *ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
} epoll_data_t;

struct epoll_event
{
  uint32_t events;	/* Epoll events */
  epoll_data_t data;	/* User data variable */
} __EPOLL_PACKED;
```

#### events
| 位掩码 | 作为epoll_ctl()输入? | 由epoll_wait()返回? | 描述 |
| ---- | -------------------:| :----------------: | :--: |
| 