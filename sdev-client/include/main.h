#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void gui();
    void packet();
    void title();
}
