#include "Logger.h"
#include <iostream>

using namespace MedLogger;

Logger* Logger::m_instance;

Logger::Logger()
{
    m_instance = this;

    SetLogLevelColor(LOG_LEVEL_DEBUG, 158, 215, 247);
    SetLogLevelColor(LOG_LEVEL_INFO, 222, 222, 222);
    SetLogLevelColor(LOG_LEVEL_WARNING, 245, 239, 135);
    SetLogLevelColor(LOG_LEVEL_SUCCESS, 126, 240, 120);
    SetLogLevelColor(LOG_LEVEL_ERROR, 255, 94, 94);
    SetLogLevelColor(LOG_LEVEL_FATAL, 255, 0, 0);

    SetLevel(LOG_LEVEL_ALL);
}

Logger::~Logger()
{
    m_instance = nullptr;
}

Logger* Logger::GetInstance()
{
    if (m_instance == nullptr)
    {
        new Logger();
    }
    return m_instance;
}

void Logger::SetLevel(uint8_t logLevel)
{
    GetInstance()->m_LogLevel = logLevel;
}

void Logger::SetLogLevelColor(uint8_t logLevel, uint8_t r, uint8_t g, uint8_t b)
{
    GetInstance()->m_LogLevelColors[logLevel] = RGB{r, g, b};
}

void Logger::LogMessage(const char*& message, uint8_t level, const char* file, int line)
{
    if (level & m_LogLevel)
    {
        const char* levelName = "";
        switch (level)
        {
        case LOG_LEVEL_DEBUG:
            levelName = "DEBUG";
            break;
        case LOG_LEVEL_INFO:
            levelName = "INFO";
            break;
        case LOG_LEVEL_WARNING:
            levelName = "WARNING";
            break;
        case LOG_LEVEL_SUCCESS:
            levelName = "SUCCESS";
            break;
        case LOG_LEVEL_ERROR:
            levelName = "ERROR";
            break;
        case LOG_LEVEL_FATAL:
            levelName = "FATAL";
            break;
        }


        std::cout << "\033[38;2;" << (int)m_LogLevelColors[level].r << ";" << (int)m_LogLevelColors[level].g << ";" << (int)m_LogLevelColors[level].b << "m";
        std::cout << "[" << levelName << "] : in \"" << file << "\" in line : " << line << " : " << std::endl;
        std::cout << message << "\033[0m" << std::endl;
    }
}
void Logger::LogMessage(const std::string& message, uint8_t level, const char* file, int line)
{
    if (level & m_LogLevel)
    {
        const char* levelName = "";
        switch (level)
        {
        case LOG_LEVEL_DEBUG:
            levelName = "DEBUG";
            break;
        case LOG_LEVEL_INFO:
            levelName = "INFO";
            break;
        case LOG_LEVEL_WARNING:
            levelName = "WARNING";
            break;
        case LOG_LEVEL_SUCCESS:
            levelName = "SUCCESS";
            break;
        case LOG_LEVEL_ERROR:
            levelName = "ERROR";
            break;
        case LOG_LEVEL_FATAL:
            levelName = "FATAL";
            break;
        }


        std::cout << "\033[38;2;" << (int)m_LogLevelColors[level].r << ";" << (int)m_LogLevelColors[level].g << ";" << (int)m_LogLevelColors[level].b << "m";
        std::cout << "[" << levelName << "] : in \"" << file << "\" in line : " << line << " : " << std::endl;
        std::cout << message << "\033[0m" << std::endl;
    }
}
