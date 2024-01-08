#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void chat();
    void gui();
    void item();
    void packet();
}
