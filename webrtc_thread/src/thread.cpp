//
// Created by haha on 2019/9/13.
//

#include "thread.h"
#include "null_socket_server.h"

#include <cassert>

PlatformThreadRef CurrentThreadRef() {
    return pthread_self();
}

bool IsThreadRefEqual(const PlatformThreadRef& a, const PlatformThreadRef& b) {
    return pthread_equal(a, b);
}

ThreadManager::ThreadManager() : main_thread_ref_(CurrentThreadRef()) {
    pthread_key_create(&key_, nullptr);
}

ThreadManager* ThreadManager::Instance() {
    static ThreadManager* const thread_manager = new ThreadManager();
    return thread_manager;
}

Thread* ThreadManager::CurrentThread() {
    return static_cast<Thread*>(pthread_getspecific(key_));
}

bool ThreadManager::IsMainThread() {
    return IsThreadRefEqual(CurrentThreadRef(), main_thread_ref_);
}

void ThreadManager::SetCurrentThread(Thread* thread) {
    pthread_setspecific(key_, thread);
}


Thread::Thread(std::unique_ptr<SocketServer> ss):Thread(std::move(ss), true) {}

Thread::Thread(std::unique_ptr<SocketServer> ss, bool do_init)
    : MessageQueue(std::move(ss), false) {

}


std::unique_ptr<Thread> Thread::Create() {
    return std::unique_ptr<Thread>(
            new Thread(std::unique_ptr<SocketServer>(new NullSocketServer())));
}

Thread* Thread::Current() {
    ThreadManager* manager = ThreadManager::Instance();
    Thread* thread = manager->CurrentThread();

#ifndef NO_MAIN_THREAD_WRAPPING // 只在chromuim中定义
    if (!thread && manager->IsMainThread()) {
        thread = new Thread(SocketServer::CreateDefault());
        thread->WrapCurrentWithThreadManager(manager, true);
    }
#endif

    return thread;
}

bool Thread::Start(void* runnable) {
    ThreadInit* init = new ThreadInit;
    init->thread = this;
    init->runnable = runnable;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    int error_code = pthread_create(&thread_, &attr, PreRun, init);
    if (0 != error_code) {
        thread_ = 0;
        return false;
    }

    return true;
}

void* Thread::PreRun(void* pv) {
    ThreadInit* init = static_cast<ThreadInit*>(pv);

    if (init->runnable) {
        assert(false);
    } else {
        init->thread->Run();
    }
    delete init;
    return nullptr;
}

void Thread::Run() {
    this->ProcessMessages(kForever);
}

bool Thread::WrapCurrentWithThreadManager(ThreadManager* thread_manager, bool need_synchronize_access) {
    thread_ = pthread_self();
    // owned_ = false;
    thread_manager->SetCurrentThread(this);
}


bool Thread::ProcessMessages(int cmsLoop) {
    int cmsNext = cmsLoop;
    while (true) {
        Message msg;
        if (!this->Get(&msg, cmsNext))
            return false;
    }
}

