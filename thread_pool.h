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
    thread_pool(int thread_size = 5) : thread_size(thread_size) {

    }
    void start();
    void stop();
    ~thread_pool() {
        stop();
    }
private:
    void thread_loop();
    int thread_size;
    std::vector<std::thread *> Threads;
};

void thread_pool::start() {
    for (int i = 0; i < thread_size; ++i) {
        Threads.push_back(new std::thread(&thread_pool::thread_loop, this));
    }
    return ;
}

void thread_pool::stop() {
    return ;
}

void thread_pool::thread_loop() {
    std::cout << "hello world" << std::endl << std::flush;
    return ;
}

END(lin)

#endif
