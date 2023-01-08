# 线程管理工具 (pthread_pool)

**线程池(线程管理工具)的作用**

- 提高工作效率

&emsp;&emsp;用C++封装一个线程池类，内部开辟指定个可以重复使用的线程。从而避免实现一个功能就要开辟一个线程的创建销毁时间开销。

- 管理线程的数量

&emsp;&emsp;正常在C/C++环境下，写多线程程序，对于线程的数量只能通过代码逻辑把控。这里我们封装一个线程池类，来控制进程中的线程，如果线程数超过了门限，那就阻塞住。

**设计目标**

- 能够执行传入的任意函数

&emsp;&emsp;对于线程回调函数而言，它们的返回值、参数个数、参数类型都会存在差异。而一个线程池不能仅支持一种类型的函数，要全面兼容。

- 执行过程可以按照优先级顺序

&emsp;&emsp;有的线程可能负责更紧急的任务，此时其应该优先享受资源。

![](https://github.com/Night221018/Thread-management-tools/blob/main/png/概述图.png)
