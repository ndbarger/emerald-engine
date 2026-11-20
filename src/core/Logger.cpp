#include "emerald/core/Logger.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

namespace emerald
{
    std::mutex Logger::mutex;
    std::ofstream Logger::logFile;
    LogLevel Logger::minimumLevel = LogLevel::Trace;

    namespace
    {
        const char *getLevelName(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Trace:
                return "TRACE";
            case LogLevel::Debug:
                return "DEBUG";
            case LogLevel::Info:
                return "INFO";
            case LogLevel::Warning:
                return "WARN";
            case LogLevel::Error:
                return "ERROR";
            case LogLevel::Fatal:
                return "FATAL";
            default:
                return "UNKNOWN";
            }
        }

        const char *getLevelColor(LogLevel level)
        {
            switch (level)
            {
            case LogLevel::Trace:
                return "\033[90m";
            case LogLevel::Debug:
                return "\033[36m";
            case LogLevel::Info:
                return "\033[32m";
            case LogLevel::Warning:
                return "\033[33m";
            case LogLevel::Error:
                return "\033[31m";
            case LogLevel::Fatal:
                return "\033[1;31m";
            default:
                return "\033[0m";
            }
        }

        std::string getTimestamp()
        {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);

            std::tm localTime{};

#ifdef _WIN32
            localtime_s(&localTime, &time);
#else
            localtime_r(&time, &localTime);
#endif

            std::ostringstream stream;

            stream << std::put_time(&localTime, "%H:%M:%S");

            return stream.str();
        }
    }

    bool Logger::init(const std::string &filePath)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (!filePath.empty())
        {
            logFile.open(filePath, std::ios::out | std::ios::app);

            if (!logFile.is_open())
                return false;
        }

        return true;
    }

    void Logger::shutdown()
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (logFile.is_open())
        {
            logFile.flush();
            logFile.close();
        }
    }

    void Logger::setLevel(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(mutex);
        minimumLevel = level;
    }

    void Logger::write(
        LogLevel level,
        std::string_view category,
        const std::string &message)
    {
        if (level < minimumLevel)
            return;

        std::lock_guard<std::mutex> lock(mutex);

        const std::string timestamp = getTimestamp();

        // Console output
        std::cout
            << getLevelColor(level)
            << "[" << timestamp << "] "
            << "[" << getLevelName(level) << "] "
            << "\033[0m"
            << "[" << category << "] "
            << message
            << std::endl;

        // File output (without ANSI colors)
        if (logFile.is_open())
        {
            logFile
                << "[" << timestamp << "] "
                << "[" << getLevelName(level) << "] "
                << "[" << category << "] "
                << message
                << '\n';

            if (level >= LogLevel::Error)
                logFile.flush();
        }
    }
}