/*************************************************************************
	> File Name: main.cpp
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Mon 02 Jan 2023 01:08:22 PM UTC
 ************************************************************************/

#include "thread_pool.h" 

using namespace std;

void func(int x, int &n) {
    n += 2;
    cout << "func : " << x << " " << n << endl;
    return ;
}

int main() {
    int n = 123;
    lin::Task t(func, 23, ref(n));
    t.run();
    cout << n << endl;
    return 0;
}
