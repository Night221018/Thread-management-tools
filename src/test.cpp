/*************************************************************************
	> File Name: test.cpp
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Fri 13 Jan 2023 01:45:15 PM UTC
 ************************************************************************/

#include "head.h"

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
