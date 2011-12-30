#include <Logger.hpp>

Logger::Logger() : mLogStream(NULL)
{
    // Nothing to do here
}

bool Logger::Init()
{
    mLogStream.open("log.txt");
}

Logger::~Logger()
{

}
