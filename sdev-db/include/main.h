#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void character();
    void character_list();
}
