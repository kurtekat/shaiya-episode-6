#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void main_stats();
    void packet();
    void patch();
}
