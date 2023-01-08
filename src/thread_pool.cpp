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

private:
    std::vector<std::thread *> threads;
    std::queue<Task *> tasks;
};

END(lin)

void func(int a, int b, int c) {
    std::cout << a + b + c << std::endl;
    return ;
}

int main() {
    lin::Task t1(func, 1, 2, 3);
    std::cout << "hello world" << std::endl;
    t1.run();
    return 0;
}
