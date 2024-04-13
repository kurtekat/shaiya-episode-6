#pragma once
#include <vector>

void Main();
extern "C" __declspec(dllexport) void DllExport();

using CharId = unsigned long;
inline std::vector<CharId> g_users{};

namespace hook
{
    void packet_exchange();
    void packet_shop();

    // ep6 functions

    void item_effect();
    void npc_quest();
    void packet_character();
    void packet_gem();
    void packet_market();
    void packet_myshop();
    void revenge_mark();
    void user_equipment();
    void user_apply_skill();
    void user_shape();
    void user_status();
}
