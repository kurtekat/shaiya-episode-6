#pragma once

void Main();
extern "C" __declspec(dllexport) void DllExport();

namespace hook
{
    void item_effect();
    void packet_character();
    void packet_exchange();
    void packet_gem();
    void packet_mailbox();
    void packet_main_interface();
    void packet_market();
    void packet_myshop();
    void packet_party();
    void packet_pc();
    void packet_quest();
    void packet_reward_item();
    void packet_shop();
    void user_equipment();
    void user_skill();
    void user_shape();
    void user_status();
    void world_thread();
}
