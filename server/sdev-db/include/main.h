#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void character_create();
    void character_list();
}
