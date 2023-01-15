/*************************************************************************
	> File Name: logger.h
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Sun 15 Jan 2023 03:13:34 PM UTC
 ************************************************************************/

#ifndef _LOGGER_H
#define _LOGGER_H

#define LOG(level) lin::Logger::LoggerStream(level, __FILE__, __LINE__, lin::lin_log)
#define LOG_INFO LOG(lin::LogLevel::INFO)
#define LOG_WARNING LOG(lin::LogLevel::WARNING)
#define LOG_DEBUG LOG(lin::LogLevel::DEBUG)
#define LOG_ERROR LOG(lin::LogLevel::ERROR)
#define LOG_FATAL LOG(lin::LogLevel::FATAL)
#define SET_LEVEL(level) lin::lin_log.set_level(level)


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
    void set_level(int level) {
        this->LOG_LEVEL = level;
    }
    int LOG_LEVEL;
    std::mutex m_mutex;

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
};

Logger lin_log;


END(lin)


#endif
