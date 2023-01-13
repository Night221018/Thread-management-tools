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
#include <mutex>
#include <condition_variable>

#define BEGIN(x) namespace x {
#define END(x) }

BEGIN(lin)

/****************************************/
/***********************/

class Task {
public:
    template<typename FUNCTION, typename... ARGS>
    Task(FUNCTION &&, ARGS...); 
    void run(); 
private:
    std::function<void()> func;
};

template<typename FUNCTION, typename... ARGS>
Task::Task(FUNCTION &&func, ARGS... args) {
    this->func = std::bind(func, std::forward<ARGS>(args)...);
}

void Task::run() {
    std::cout << "Task run : ";
    func();
    return ;
}

/***********************/
/****************************************/
/***********************/

class ThreadPool {
public:
    ThreadPool(int n = 5); 
    template<typename FUNCTION, typename... ARGS>
    void addOneTask(FUNCTION &&, ARGS...);
    void stop();

private:
    std::vector<std::thread *> threads;
    std::queue<Task *> tasks;
    std::unordered_map<std::thread::id, bool> running;
    std::mutex m_mutex;
    std::condition_variable m_cond;

    void workerThread(); 
    Task *getOneTask(); 
    void stop_thread();
};

ThreadPool::ThreadPool(int n) {
    for (int i = 0; i < n; ++i) {
        threads.push_back(new std::thread(&ThreadPool::workerThread, this));
    }
}

template<typename FUNCTION, typename... ARGS>
void ThreadPool::addOneTask(FUNCTION &&func, ARGS... args) {
    std::unique_lock<std::mutex> lock(m_mutex);
    tasks.push(new Task(func, std::forward<ARGS>(args)...));
    m_cond.notify_one();
    return ;
}

void ThreadPool::stop() {
    for (int i = 0; i < threads.size(); ++i) {
        this->addOneTask(&ThreadPool::stop_thread, this);
    }
    for (auto t : threads) {
        t->join();
    }
    return ;
}

void ThreadPool::workerThread() {
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

Task* ThreadPool::getOneTask() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (tasks.empty()) {
        m_cond.wait(lock);
    }
    Task *t = tasks.front();
    tasks.pop();
    return t;
}

void ThreadPool::stop_thread() {
    std::thread::id id = std::this_thread::get_id();
    running[id] = false;
    return ;
}

/***********************/
/****************************************/

END(lin)

void func(int a, int b, int c) {
    std::cout << a << ", " << b << ", " << c << std::endl;
    return ;
}

int main() {
    lin::ThreadPool tp;
    for (int i = 0; i < 10; ++i) {
        tp.addOneTask(func, i, 2 * i, 3 * i);
    }
    tp.stop();
    return 0;
}
