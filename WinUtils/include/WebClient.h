#pragma once
#include <winhttp.h>
#include "HttpResponse.h" 

#pragma comment (lib, "winhttp.lib")

struct WinHttpHandleDeleter
{
    typedef HINTERNET pointer;

    void operator()(HINTERNET h)
    {
        if(h != nullptr)
        {
            WinHttpCloseHandle(h);
        }
    }

};
typedef std::unique_ptr<HINTERNET, WinHttpHandleDeleter> WinHttpHandle;

class WebClient
{
public:
    WebClient();
    ~WebClient();
    std::unique_ptr<HttpResponse> Get(const std::wstring& url);

    WinHttpHandle m_hInternet;
};

