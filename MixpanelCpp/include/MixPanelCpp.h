#pragma once

#ifdef MIX_PANEL_EXPORTS
#define MIX_PANEL_API __declspec(dllexport)
#else
#define MIX_PANEL_API __declspec(dllimport)
#endif

#include <string>
#include <functional>