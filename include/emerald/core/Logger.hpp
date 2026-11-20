#pragma once

#include <mutex>
#include <fstream>
#include <string>
#include <string_view>

#include <fmt/format.h>

namespace emerald
{
    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    class Logger
    {
    private:
        Logger() = delete; // prevent instantiation; this is a static class

        static std::mutex mutex;
        static std::ofstream logFile;
        static LogLevel minimumLevel;

        static void write(LogLevel level, std::string_view category, const std::string &message);

    public:
        // init/shutdown
        static bool init(const std::string &filePath);
        static void shutdown();

        // configure logging
        static void setLevel(LogLevel level);

        // general logging interface
        template <typename... Args>
        static void log(
            LogLevel level, std::string_view category,
            fmt::format_string<Args...> format, Args &&...args)
        {
            std::string message = fmt::format(
                format,
                std::forward<Args>(args)...);

            write(level, category, message);
        }

        // convenience methods
        template <typename... Args>
        static void trace(fmt::format_string<Args...> format, Args &&...args)
        {
            log(LogLevel::Trace, "Engine",
                format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void debug(fmt::format_string<Args...> format, Args &&...args)
        {
            log(LogLevel::Debug, "Engine",
                format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void info(fmt::format_string<Args...> format, Args &&...args)
        {
            log(LogLevel::Info, "Engine",
                format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void warning(fmt::format_string<Args...> format, Args &&...args)
        {
            log(LogLevel::Warning, "Engine",
                format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void error(fmt::format_string<Args...> format, Args &&...args)
        {
            log(LogLevel::Error, "Engine",
                format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void fatal(fmt::format_string<Args...> format, Args &&...args)
        {
            log(LogLevel::Fatal, "Engine",
                format, std::forward<Args>(args)...);
        }
    };
}