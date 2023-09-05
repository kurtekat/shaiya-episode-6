#pragma once
#include <windows.h>

void Main(HMODULE hModule);

namespace hook
{
    void packet_exchange();
    void packet_shop();

    // ep6 functions

    void packet_character();
    void packet_gem();
    void packet_market();
    void user_equipment();
    void user_shape();
    void user_status();
}
