### 基础
- epoll : event poll
- interest list(兴趣列表)和ready list(就序列表)，后者是前者的子集
#### 非阻塞式I/O
- 如果在打开文件时设定了`O_NONBLOCK`标志，会以非阻塞方式打开文件
- 如果I/O系统调用不能立刻完成，则会返回错误而不是阻塞进程
- 需要周期性地检查(“轮询poll”)某个文件描述符上是否可执行I/O操作
#### IO模型
- I/O多路复用 select/poll
- 信号驱动IO
- epoll
#### 触发
- 水平触发通知:muduo采用此模式
- 边缘触发通知：

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
| :----  | :-------------------:| :----------------: | :-- |
| EPOLLIN(0x001) | y | y | 可读取非高优先级的数据 |
| EPOLLPRI(0x002) | y | y | 可读取高优先级数据 |
| EPOLLRDHUP | y | y | 套接字对端关闭 |
| EPOLLOUT(0x004) | y | y | 普通数据可写 |
| EPOLLET | y |  | 采用边缘触发事件通知 |
| EPOLLONESHOT | y |  | 在完成事件通知之后禁用检查 |
| EPOLLERR |  | y | 有错误发生 |
| EPOLLHUP(0x010) |  | y | 出现挂断 |
