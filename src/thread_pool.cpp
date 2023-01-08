/*************************************************************************
	> File Name: thread_pool.cpp
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Sun 08 Jan 2023 10:44:40 AM UTC
 ************************************************************************/

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <unistd.h>
#include <unordered_map>

#define BEGIN(x) namespace x {
#define END(x) }

BEGIN(lin)

class Task {
public:
    template<typename FUNCTION, typename... ARGS>
    Task(FUNCTION &&func, ARGS... args) {
        this->func = std::bind(func, std::forward<ARGS>(args)...);
    }
    void run() {
        std::cout << "Task run : ";
        func();
        return ;
    }
private:
    std::function<void()> func;
};

class ThreadPool {
public:
    ThreadPool(int n = 5) {
        for (int i = 0; i < n; ++i) {
            threads.push_back(new std::thread(&ThreadPool::workerThread, this));
        }
    }
    template<typename FUNCTION, typename... ARGS>
    void addOneTask(FUNCTION &&, ARGS...);
    
private:
    std::vector<std::thread *> threads;
    std::queue<Task *> tasks;
    std::unordered_map<std::thread::id, bool> running;

    void workerThread() {
        std::thread::id id = std::this_thread::get_id();
        // std::cout << id << std::endl;
        running[id] = true;
        while (running[id]) {
            // get Task
            Task *t = this->getOneTask();
            // run Task
            t->run();
            // del Task
            delete t;
        }
        return ;
    }
    Task *getOneTask() {
        // TODO
        return nullptr;
    }
};

template<typename FUNCTION, typename... ARGS>
void ThreadPool::addOneTask(FUNCTION &&func, ARGS... args) {
    // TODO
    return ;
}

END(lin)

void func(int a, int b, int c) {
    std::cout << a + b + c << std::endl;
    return ;
}

int main() {
    lin::Task t1(func, 1, 2, 3);
    lin::ThreadPool tp;
    sleep(1);
    std::cout << "hello world" << std::endl;
    t1.run();
    return 0;
}
