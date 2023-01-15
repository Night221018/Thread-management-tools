/*************************************************************************
	> File Name: logger.cpp
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Fri 13 Jan 2023 01:48:05 PM UTC
 ************************************************************************/

#include <iostream>
#include <sstream>
#include <map>
#include "thread_pool.h"

#define LOG(level) lin::Logger::LoggerStream(level, __FILE__, __LINE__, lin::lin_log)
#define LOG_INFO LOG(lin::LogLevel::INFO)
#define LOG_WARNING LOG(lin::LogLevel::WARNING)
#define LOG_DEBUG LOG(lin::LogLevel::DEBUG)
#define LOG_ERROR LOG(lin::LogLevel::ERROR)
#define LOG_FATAL LOG(lin::LogLevel::FATAL)
#define SET_LEVEL(level) lin::lin_log.set_level(level)


// #define BEGIN(x) namespace x {
//  #define END(x) }


BEGIN(lin)


class LogLevel {
public:
    static const int INFO;
    static const int WARNING;
    static const int DEBUG;
    static const int ERROR;
    static const int FATAL;
};
const int LogLevel::INFO = 1;
const int LogLevel::WARNING = 2;
const int LogLevel::DEBUG = 3;
const int LogLevel::ERROR = 4;
const int LogLevel::FATAL = 5;


static std::map<int, std::string> LevelString = {
    {LogLevel::INFO, "INFO"},
    {LogLevel::WARNING, "WARNING"},
    {LogLevel::DEBUG, "DEBUG"},
    {LogLevel::ERROR, "ERROR"},
    {LogLevel::FATAL, "FATAL"}
};

class Logger {
public:
    Logger() : LOG_LEVEL(LogLevel::INFO) {}

    class LoggerStream : public std::ostringstream {
    public:
        LoggerStream(int level, const char *file_name, int line_no, Logger &raw_log) 
        : line_no(line_no), level(level), raw_log(raw_log) {
            std::ostringstream &now = *this;
            now << "[" << file_name << " : " << LevelString[level] << "] ";
        }
        ~LoggerStream() {
            if (level < raw_log.LOG_LEVEL)  return ;
            std::unique_lock<std::mutex> lock(raw_log.m_mutex);
            std::cout << this->str() << " (" << line_no << ")" << std::endl;
        }
    private:
        int line_no, level;
        Logger &raw_log;
    };

    void set_level(int level) {
        this->LOG_LEVEL = level;
    } 
    int LOG_LEVEL;
    std::mutex m_mutex;
};

Logger lin_log;


END(lin)


void func(int a, int b, int c) {
    LOG_INFO << a << " " << b << " " << c;
    return ;
}

int main() {
    SET_LEVEL(lin::LogLevel::DEBUG);
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
