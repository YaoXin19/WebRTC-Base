//
// Created by haha on 2019/9/13.
//

#ifndef PTHREAD_THREAD_H
#define PTHREAD_THREAD_H

#include "socket_server.h"
#include "message_queue.h"

#include <memory>

#include <pthread.h>

typedef pthread_t PlatformThreadRef;
class Thread;

class ThreadManager {
public:
    static const int kForever = -1;
    static ThreadManager* Instance();
    Thread* CurrentThread();
    bool IsMainThread();
    void SetCurrentThread(Thread* thread);
private:
    ThreadManager();
    ~ThreadManager();

    pthread_key_t key_;

    const PlatformThreadRef main_thread_ref_;
};

class Thread : public MessageQueue {
public:
    explicit Thread(std::unique_ptr<SocketServer> ss);

    Thread(std::unique_ptr<SocketServer> ss, bool do_init);

    static std::unique_ptr<Thread> Create();
    static Thread* Current();

    bool Start(void* runnable=nullptr);

    void Run();

    bool WrapCurrentWithThreadManager(ThreadManager* thread_manager, bool need_synchronize_access);

private:
    struct ThreadInit {
        Thread* thread;
        void* runnable;
    };

private:
    static void* PreRun(void* pv);
    bool ProcessMessages(int cmsloop);

private:
    pthread_t thread_ = 0;

};


#endif //PTHREAD_THREAD_H
