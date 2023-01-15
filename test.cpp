/*************************************************************************
	> File Name: test.cpp
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Fri 13 Jan 2023 01:45:15 PM UTC
 ************************************************************************/

#include "head.h"

void func(int a, int b, int c) {
    LOG_INFO << a << " " << b << " " << c;
    return ;
}

int main() {
    // SET_LEVEL(lin::LogLevel::DEBUG);
    LOG_INFO << "hello world" << 123 << " " << 12.45;
    LOG_WARNING << "hello world" << 123 << " " << 12.45;
    LOG_DEBUG << "hello world" << 123 << " " << 12.45;
    LOG_ERROR << "hello world" << 123 << " " << 12.45;
    LOG_FATAL << "hello world" << 123 << " " << 12.45;
    lin::ThreadPool tp;
    for (int i = 0; i < 10; ++i) {
        tp.addOneTask(func, i, 2 * i, 3 * i);
    }
    tp.stop();
    return 0;
}

