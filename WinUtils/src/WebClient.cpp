#include "stdafx.h"
#include "WinUtils/include/WebClient.h"
#include "Win32Exception.h"
#include "WinUtils/include/UrlHelper.h" 
#include "WinUtils/include/HttpResponse.h" 

const wchar_t* UserAgentString = L"Mozilla / 4.0 (compatible; MSIE 6.0; Windows NT 5.2; .NET CLR 1.0.3705;)";

WebClient::WebClient()
{
    WINHTTP_CURRENT_USER_IE_PROXY_CONFIG proxyConfig;
    if(WinHttpGetIEProxyConfigForCurrentUser(&proxyConfig) && proxyConfig.lpszProxy != nullptr)
    {
        m_hInternet.reset(
            WinHttpOpen(UserAgentString, WINHTTP_ACCESS_TYPE_NAMED_PROXY, proxyConfig.lpszProxy, proxyConfig.lpszProxyBypass, 0)
            );
        GlobalFree(proxyConfig.lpszAutoConfigUrl);
        GlobalFree(proxyConfig.lpszProxy);
        GlobalFree(proxyConfig.lpszProxyBypass);
    }
    else
    {
        m_hInternet.reset(
            WinHttpOpen(UserAgentString, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0)
            );

    }

    if(m_hInternet == nullptr) throw Win32Exception("WinHttpOpen failed");
}


WebClient::~WebClient()
{
}

std::unique_ptr<HttpResponse> WebClient::Get(const std::wstring& uri)
{
    UrlHelper urlHelper(uri);

    std::wstring url = urlHelper.GetUrl();
    WinHttpHandle hConnect(WinHttpConnect(m_hInternet.get(), urlHelper.GetUrl().c_str(), INTERNET_DEFAULT_HTTP_PORT, 0));
    if(hConnect == nullptr) throw Win32Exception("WinHttpConnect failed");

    WinHttpHandle hRequest(WinHttpOpenRequest(hConnect.get(), L"GET",
        urlHelper.GetParameter().c_str(),
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0));
    if(hRequest == nullptr) throw Win32Exception("WinHttpOpenRequest failed");

    auto bResult = WinHttpSendRequest(hRequest.get(),
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0, WINHTTP_NO_REQUEST_DATA, 0,
        0, 0);
    if(!bResult) throw Win32Exception("WinHttpSendRequest failed");

    bResult = WinHttpReceiveResponse(hRequest.get(), NULL);
    if(!bResult) throw Win32Exception("WinHttpSendRequest failed");

    DWORD dwSize = 0;
    std::vector<std::vector<char>> bufferList;
    do
    {
        bResult = WinHttpQueryDataAvailable(hRequest.get(), &dwSize);
        if(!bResult) throw Win32Exception("WinHttpQueryDataAvailable failed");

        if(dwSize == 0)
            break;

        std::vector<char> buffer(dwSize);
        DWORD dwDownloaded;
        bResult = !WinHttpReadData(hRequest.get(), buffer.data(), dwSize, &dwDownloaded);
        if(!bResult) throw Win32Exception("WinHttpSendRequest failed");

        bufferList.push_back(std::move(buffer));
    } while(dwSize > 0);

    return std::unique_ptr<HttpResponse>(new HttpResponse(bufferList));
}
