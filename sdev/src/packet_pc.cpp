#include <algorithm>
#include <util/util.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/network/game/incoming/0500.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include "include/main.h"
#include "include/operator.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CNpcData.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NpcGateKeeper.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/TownMoveScroll.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

namespace packet_pc
{
    /// <summary>
    /// Handles incoming 0x55A packets.
    /// </summary>
    void handler_0x55A(CUser* user, GameTownMoveScrollIncoming* incoming)
    {
        if (user->status == UserStatus::Death)
            return;

        if (user->debuffTypeDetail)
            return;

        if (user->logoutTime)
            return;

        if (!incoming->bag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag, incoming->slot))
            return;

        auto& item = user->inventory[incoming->bag][incoming->slot];
        if (!item)
            return;

        if (item->info->realType != RealType::Consumable)
            return;

        if (item->info->effect != ItemEffect::TownMoveScroll)
            return;

        auto gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, item->info->reqVg);
        if (!gateKeeper)
            return;

        auto country = gateKeeper->country;
        if (country != user->country)
            return;

        auto it = g_townMoveData.find(user->mapId);
        if (it == g_townMoveData.end())
            return;

        // Disabled? (see Map.ini)
        if (!it->second)
            return;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);
        CUser::ItemUseNSend(user, incoming->bag, incoming->slot, false);

        auto index = std::clamp(static_cast<int>(incoming->gateIndex), 0, 2);
        auto mapId = gateKeeper->gates[index].mapId;
        auto x = gateKeeper->gates[index].x;
        auto y = gateKeeper->gates[index].y;
        auto z = gateKeeper->gates[index].z;
        UserHelper::SetMovePosition(user, MoveType::GateKeeper, 0, mapId, x, y, z);
    }
}

unsigned u0x4784DB = 0x4784DB;
unsigned u0x479155 = 0x479155;
void __declspec(naked) naked_0x4784D6()
{
    __asm
    {
        add eax,-0x501
        cmp eax,0x59
        je case_0x55A
        jmp u0x4784DB

        case_0x55A:
        pushad

        push ebp // packet
        push ecx // user
        call packet_pc::handler_0x55A
        add esp,0x8

        popad

        jmp u0x479155
    }
}

double g_itemRepairBuyDivisor = 15.0;
unsigned u0x471C29 = 0x471C29;
void __declspec(naked) naked_0x471C23()
{
    __asm
    {
        fld qword ptr[g_itemRepairBuyDivisor]
        jmp u0x471C29
    }
}

unsigned u0x472030 = 0x472030;
void __declspec(naked) naked_0x47202A()
{
    __asm
    {
        fdiv qword ptr[g_itemRepairBuyDivisor]
        jmp u0x472030
    }
}

void hook::packet_pc()
{
    // CUser::PacketPC
    util::detour((void*)0x4784D6, naked_0x4784D6, 5);
    // CUser::ItemRepair
    util::detour((void*)0x471C23, naked_0x471C23, 6);
    util::detour((void*)0x47202A, naked_0x47202A, 6);
}
