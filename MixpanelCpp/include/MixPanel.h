#pragma once
#include "MixPanelCpp/include/MixPanelCpp.h"
#include "WinUtils/include/IWebClient.h"

class MIX_PANEL_API MixPanel
{
public:
    MixPanel();
    MixPanel(IWebClient& webClient);
    ~MixPanel();

    void Track(const std::wstring& trackingId);
};

