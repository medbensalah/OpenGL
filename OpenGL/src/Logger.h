#pragma once
#include <chrono>
#include <cstdint>
#include <string>
#include <map>
#include <queue>

#define     LOG_LEVEL_NONE      0b0
#define     LOG_LEVEL_DEBUG     0b1
#define     LOG_LEVEL_INFO      0b10
#define     LOG_LEVEL_WARNING   0b100
#define     LOG_LEVEL_SUCCESS   0b1000
#define     LOG_LEVEL_ERROR     0b10000
#define     LOG_LEVEL_FATAL     0b100000
#define     LOG_LEVEL_ALL       0b111111

#define     LOG_MODE_CONSOLE   0b1
#define     LOG_MODE_FILE       0b10
#define     LOG_MODE_ALL        0b11

namespace MedLogger
{
#define     Log(message, logLevel)      Logger::GetInstance()->RequestLog(message, logLevel, __FILE__, __LINE__)



    static  auto start = std::chrono::system_clock::now();
    
    struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    struct LogData
    {
        std::string message;
        uint8_t loglevel;
        std::string file;
        int line;
    };
    
    class Logger
    {
    public:
        static Logger* GetInstance();

        static void SetLevel(uint8_t logLevel);
        
        static void SetLogMode(uint8_t logLevel, const std::string& path = "");

        static void SetLogLevelColor(uint8_t logLevel, uint8_t r, uint8_t g, uint8_t b);

        void RequestLog(const std::string& message, uint8_t logLevel, const std::string& file, int line);

        void LogLoop();

        void LogMessage(const std::stringstream& data);
        void LogMessageToFile(const std::stringstream& data);
        
    private:
        Logger();

        ~Logger();        
        
        static Logger* m_instance;

        std::string m_filePath;
        
        bool m_isFinished = false;
        
        std::queue<LogData> m_LogsQueue;
        
        std::map<uint8_t, RGB> m_LogLevelColors;

        uint8_t m_LogLevel;
        uint8_t m_LogMode;
    };
}
