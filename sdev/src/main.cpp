#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/Configuration.h"
using namespace shaiya;

void Main()
{
    hook::packet_character();
    hook::packet_exchange();
    hook::packet_gem();
    //hook::packet_mailbox();
    hook::packet_main_interface();
    hook::packet_market();
    hook::packet_myshop();
    hook::packet_party();
    hook::packet_pc();
    hook::packet_quest();
    hook::packet_reward_item();
    hook::packet_shop();

    hook::item_effect();
    hook::user();
    hook::user_equipment();
    hook::user_shape();
    hook::user_skill();
    hook::world_thread();

    Configuration::Init();
    Configuration::LoadBattlefieldMoveData();
    Configuration::LoadChaoticSquareData();
    Configuration::LoadItemSetData();
    Configuration::LoadOnlineTimePrizeData();
    Configuration::LoadMapData();
}
