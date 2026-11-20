#pragma once

#include <string>

namespace emerald
{
    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    class Logger
    {
    private:
        Logger() = delete; // prevent instantiation; this is a static class

        static void log(LogLevel level, const std::string &message);

    public:
        static void debug(const std::string &message);
        static void info(const std::string &message);
        static void warning(const std::string &message);
        static void error(const std::string &message);
    };
}