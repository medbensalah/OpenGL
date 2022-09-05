#include "Logger.h"

#include <fstream>
#include <future>

#include "Localtime.h"
#include <iostream>
#include <sstream>

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
    SetLogMode(LOG_MODE_ALL, "log.txt");
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

void Logger::SetLogMode(uint8_t logMode, const std::string& path)
{
    GetInstance()->m_LogMode = logMode;
    GetInstance()->m_filePath = path;
}

void Logger::SetLogLevelColor(uint8_t logLevel, uint8_t r, uint8_t g, uint8_t b)
{
    GetInstance()->m_LogLevelColors[logLevel] = RGB{r, g, b};
}

void Logger::RequestLog(const std::string& message, uint8_t logLevel, const std::string& file, int line)
{
    LogData data{message, logLevel, file, line};
    if (data.loglevel & m_LogLevel)
    {
        const char* levelName = "";
        switch (data.loglevel)
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

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::string end_time = time_stamp("%T");


        if (m_LogMode & LOG_MODE_CONSOLE)
        {
            std::stringstream ss;
            ss << "\033[38;2;" << (int)m_LogLevelColors[data.loglevel].r << ";" <<
                (int)m_LogLevelColors[data.loglevel].g << ";" <<
                (int)m_LogLevelColors[data.loglevel].b << "m" <<
                "[" << levelName << "] at " << end_time <<
                " ( elapsed time " << elapsed_seconds.count() <<
                " s ) : in \"" << data.file << "\" in line : " << data.line << " : " << std::endl <<
                data.message << "\033[0m" << std::endl;
            LogMessage(ss);
        }

        if (m_LogMode & LOG_MODE_FILE)
        {
            std::stringstream ss;
            ss << "[" << levelName << "] at " << end_time <<
                " ( elapsed time " << elapsed_seconds.count() <<
                " s ) : in \"" << data.file << "\" in line : " <<
                data.line << " : " << std::endl <<
                data.message << std::endl;
            LogMessageToFile(ss);
        }
    }
}

void Logger::LogMessageToFile(const std::stringstream& logMessage)
{
    std::ofstream file;
    file.open(m_filePath, std::ios::app);
    file << logMessage.str() << std::endl;
    file.close();
}

void Logger::LogMessage(const std::stringstream& ss)
{
    std::cout << ss.str();
}
