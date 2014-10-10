#pragma once

class Win32Exception : public std::system_error
{
public:
    Win32Exception(const char* message, uint32_t errorNumber) : std::system_error(errorNumber, std::system_category(), message)
    {
    }
    Win32Exception(const char* message) : std::system_error(GetLastError(), std::system_category(), message)
    {
    }
    Win32Exception(const std::string message) : std::system_error(GetLastError(), std::system_category(), message)
    {
    }
};
