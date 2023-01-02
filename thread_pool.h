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

END(lin)

#endif
