#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void packet();
    void patch();
}
