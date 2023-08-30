#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void Main(HMODULE hModule);

namespace hook
{
    void gui();
}
