### Pthreads数据类型
数据类型|描述
---|---
pthread_t|线程ID
pthread_mutex_t|互斥对象
pthread_cond_t|条件变量
pthread_attr_t|线程的属性对象

### 接口
#### 共享线程储存
- pthread_key_t
- pthread_key_create
- pthread_setspecific
- pthread_getspecific
#### 创建线程
```
int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void *(*start)(void*), void* arg);
- thread
- attr
- start:新线程要执行的函数
- arg:函数start的参数
```
#### 终止线程
```
void pthread_exit(void* retval);
```
#### 线程ID
```
// 获取自己的线程ID
pthread_t pthread_self(void);
```
```
// 检查两个线程ID是否相同
int pthread_equal(pthread_t t1, pthread_t t2);
```
#### 连接(joining)已终止的线程
```
// 如果由thread标识的线程终止，则pthread_join会立即返回，这种操作叫做连接(joining)
// 即可以通过连接(joining)来获取线程的返回状态
int pthread_join(pthread_t thread, void** retval);
```
#### 线程的分离
```
// 分离之后的线程不能进行连接
int pthread_detach(pthread_t thread);
```
#### 线程属性
- 线程栈的位置和大小
- 线程调度策略和优先级
- 线程是否处于可连接或分离状态

### 线程同步
- 临界区(critical section)
- 原子操作(atomic)
- 自动变量(automatic variable)
### 互斥量
#### 静态分配的互斥量
```
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
```

#### 加锁和解锁互斥量
```
// 对于互斥量的默认类型而言，同一线程第二次调用，线程会陷入死锁(linux默认)；或调用失败，返回EDEADLK错误
int pthread_mutex_lock(pthread_mutex_t* mutex);
```

```
// 如果有多个线程等待unlock，不确定线程获取互斥量的顺序
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```

#### 互斥量的死锁
- 两个线程都持有一个互斥量，并请求对方的互斥量
- 总是应该以相同的顺序对该组互斥量进行锁定

### 条件变量
#### 静态分配条件变量
```
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```

#### 通知和等待条件变量
```
// 通过cond发送信号
int pthread_cond_signal(pthread_cond_t* cond); // 保证至少唤醒一条线程
int pthread_cond_broadcast(pthread_cond_t* cond); // 唤醒所有线程

// 阻塞，直到收到条件变量cond的通知
int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);

// 
int pthread_cond_timewait(pthread_cond_t* cond, pthread_mutex_t* mutex, const struct timespec* abstime);
```