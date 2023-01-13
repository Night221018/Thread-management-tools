/*************************************************************************
	> File Name: logger.cpp
	> Author: luzelin
	> Mail: luzelin1024@163.com
	> Created Time: Fri 13 Jan 2023 01:48:05 PM UTC
 ************************************************************************/

#include <iostream>
#include <sstream>

#define LOG ze::Logger::LoggerStream()

#define BEGIN(x) namespace x {
#define END(x) }
 
BEGIN(ze)

class Logger {
public:
    class LoggerStream : public std::ostringstream {
        public:
        LoggerStream() {

        }
        ~LoggerStream() {
            std::cout << this->str() << std::endl;
        }
    };
};

END(ze)

int main() {
    /*
    std::ostringstream s;
    s << "hello world" << " " << 123 << std::endl;
    std::cout << s.str() << std::endl;
    */
    LOG << "hello world " << 123 << " " << 12.45 << std::endl; 
    return 0;
}
