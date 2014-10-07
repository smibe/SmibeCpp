#include "stdafx.h"
#include "CppUnitTest.h"
#include "WinUtils/include/WebClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WinUtils_UnitTest
{
    TEST_CLASS(WebClientTest)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            WebClient webClient;
            //webClient.Get(L"http://www.google.com/nonexistingfile", [](int statusCode, std::wstring response)
            //{
            //    Assert::AreEqual(404, statusCode);
            //});
            auto response = webClient.Get(L"http://www.google.com/nonexistingfile");
        }
    };
}