#pragma once
#include <cstdint>
#include <string>
#include <map>

#define     LOG_LEVEL_NONE      0b0
#define     LOG_LEVEL_DEBUG     0b1
#define     LOG_LEVEL_INFO      0b10
#define     LOG_LEVEL_WARNING   0b100
#define     LOG_LEVEL_SUCCESS   0b1000
#define     LOG_LEVEL_ERROR     0b10000
#define     LOG_LEVEL_FATAL     0b100000
#define     LOG_LEVEL_ALL       0b111111

namespace MedLogger
{
#define     Log(message, logLevel)      Logger::GetInstance()->LogMessage(message, logLevel, __FILE__, __LINE__)

    struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    class Logger
    {
    public:
        static Logger* GetInstance();

        static void SetLevel(uint8_t logLevel);

        static void SetLogLevelColor(uint8_t logLevel, uint8_t r, uint8_t g, uint8_t b);

        void LogMessage(const char*& message, uint8_t level, const char* file, int line);

        void LogMessage(const std::string& message, uint8_t level, const char* file, int line);

    private:
        Logger();

        ~Logger();        
        
        static Logger* m_instance;

        std::map<uint8_t, RGB> m_LogLevelColors;

        uint8_t m_LogLevel;
    };
}
