#pragma once

class HttpResponse
{
public:

    HttpResponse(std::vector<std::vector<char>>bufferList)
    {
        m_bufferList = bufferList;
    }

    ~HttpResponse()
    {
    }

    std::vector<std::vector<char>> m_bufferList;
};

