#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void user_character();
    void character_list();
}
