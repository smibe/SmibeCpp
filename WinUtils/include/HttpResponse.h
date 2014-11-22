#pragma once

class HttpResponse
{
public:

    HttpResponse(std::vector<wchar_t> header, std::vector<std::vector<char>>bufferList, int statusCode)
    {
        m_header = header;
        m_bufferList = bufferList;
        m_statusCode = statusCode;
    }

    ~HttpResponse()
    {
    }

    std::string GetResponse()		
    {
        std::string result;
        for(auto& chunk : m_bufferList)
        {
            result.append(chunk.data(), chunk.size());
        }
        return result;
    }

    int GetStatus()
    {
        return m_statusCode;
    }

    std::vector<std::vector<char>> m_bufferList;
    std::vector<wchar_t> m_header;
    int m_statusCode;
};

