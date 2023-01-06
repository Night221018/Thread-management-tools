/*************************************************************************
	> File Name: thread_pool.h
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Thu 08 Dec 2022 07:38:56 PM CST
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>

#define BEGIN(x) namespace x {
#define END(x) }

BEGIN(lin)

class Task {
public:
    template<typename Func_T, typename... ARGS>
    Task(Func_T f, ARGS... args) {
        func = std::bind(f, std::forward<ARGS>(args)...);    
    }
    void run() {
        func();
    }
private:
    std::function<void()> func;
};

class thread_pool {
public:
    thread_pool(int thread_size = 5) 
    : thread_size(thread_size), is_started(false), m_mutex(), m_cond(m_mutex) {}
    
    void start();
    void stop();
    ~thread_pool() {
        stop();
    }
private:
    void thread_loop();
    Task *get_one_task();
    void add_one_task(Task *);

    int thread_size;
    bool is_started;
    std::vector<std::thread *> Threads;
    std::queue<Task *> Tasks;

    std::mutex m_mutex;
    std::condition_variable m_cond;
};

void thread_pool::start() {
    std::unique_lock<std::mutex> lock(m_mutex);
    is_started = true;
    for (int i = 0; i < thread_size; ++i) {
        Threads.push_back(new std::thread(&thread_pool::thread_loop, this));
    }
    return ;
}

void thread_pool::stop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    is_started = false;
    for (int i = 0; i < Threads.size(); ++i) {
        Threads[i]->join();
        delete Threads[i];
    }
    Threads.clear();
    return ;
}

void thread_pool::thread_loop() {
    while (is_started) {
        Task *t = get_one_task();
        if (t != nullptr) {
            std::cout << "thread_loop tid : " << CurrentThread::tid() << std::endl;
            t->run();
        }
    }
    return ;
}

Task* thread_pool::get_one_task() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (Tasks.empty() && is_started) {
        m_cond.wait(lock);
    }
    Task *t = nullptr;
    if (Tasks.empty() && is_started) {
        t = Tasks.front();
        Tasks.pop();
    }
    return t;
}

void thread_pool::add_one_task(Task *t) {
    std::unique_lock<std::mutex> lock(m_mutex);
    Tasks.push(t);
    m_cond.notify();
    return ;
}

END(lin)

#endif
