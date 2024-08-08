#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void demo();
    void gui();
    void packet();
}
