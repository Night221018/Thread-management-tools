/*************************************************************************
	> File Name: task.h
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Fri 13 Jan 2023 01:38:16 PM UTC
 ************************************************************************/

#ifndef _TASK_H
#define _TASK_H

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
    func();
    return ;
}

#endif
