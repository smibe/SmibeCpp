#include "stdafx.h"
#include "CppUnitTest.h"
#include "WinUtils/include/WebClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WinUtils_UnitTest
{
    TEST_CLASS(WebClientTest)
    {
    public:

        TEST_METHOD(WebClient_GetTest)
        {
            WebClient webClient;
            //webClient.Get(L"http://www.msftncsi.com/ncsi.txt", [](int statusCode, std::wstring response)
            //{
            //    Assert::AreEqual(404, statusCode);
            //});
            auto response = webClient.Get(L"http://www.msftncsi.com/ncsi.txt");
            Assert::AreEqual("Microsoft NCSI", response->GetResponse().c_str());
            Assert::AreEqual(200, response->GetStatus());
        }
    };
}