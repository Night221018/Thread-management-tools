/*************************************************************************
	> File Name: head.h
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Fri 13 Jan 2023 01:42:15 PM UTC
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

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

#include "task.h"
#include "thread_pool.h"

#endif
