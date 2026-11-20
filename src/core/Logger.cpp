#include <emerald/core/Logger.hpp>

#include <iostream>

namespace emerald
{
    // Not sure if we're going to use this yet
    void Logger::log(LogLevel level, const std::string &message)
    {
    }

    void Logger::debug(const std::string &message)
    {
        std::cout << "[DEBUG] " << message << std::endl;
    }

    void Logger::info(const std::string &message)
    {
        std::cout << "[INFO] " << message << std::endl;
    }

    void Logger::warning(const std::string &message)
    {
        std::cout << "[WARNING] " << message << std::endl;
    }

    void Logger::error(const std::string &message)
    {
        std::cerr << "[ERROR] " << message << std::endl;
    }

}