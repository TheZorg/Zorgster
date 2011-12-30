#ifndef ZORGSTER_LOGGER_HPP
#define ZORGSTER_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <Singleton.hpp>

const int LOG_APP = 1;

class Logger : public Singleton<Logger> {
public:
    Logger();
    virtual ~Logger();

    bool Init();

    void Write(int target, const char* msg, ...);

protected:
    std::ofstream mLogStream;
};
#endif
