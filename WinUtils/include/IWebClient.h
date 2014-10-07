#pragma once
#include <string>
#include <functional>

typedef std::function<void(int, const std::wstring&)> FOnResponse;

class IWebClient
{
    virtual void Get(const std::wstring url, FOnResponse onResponse) = 0;
};