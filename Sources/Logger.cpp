#include "Logger.h"

namespace Hackaton
{

void Logger::Info(std::string_view text)
{
    std::cout << BOLDBLUE << "ℹ info " << RESET << text << std::endl;
}

void Logger::Warning(std::string_view text)
{
    std::cout << BOLDYELLOW << "⚠ warn " << RESET << text << std::endl;
}

void Logger::Error(std::string_view text)
{
    std::cout << BOLDRED << "⨯ error " << RESET << text << std::endl;
}

}