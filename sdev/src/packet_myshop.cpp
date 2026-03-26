#include <util/util.h>
#include <shaiya/include/network/game/outgoing/2300.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

/// <summary>
/// Sends packet 0x230B (6.4) to the user. The item dates will be zero.
/// </summary>
void hook_0x48733F(CUser* user, GameMyShopBuyListOutgoing_EP5* packet)
{
    GameMyShopBuyListOutgoing_EP6_4 outgoing{};
    outgoing.itemCount = packet->itemCount;

    auto it = packet->itemList.cbegin();
    auto last = it + packet->itemCount;
    auto unit = outgoing.itemList.begin();

    for (; it != last; ++it, ++unit)
    {
        unit->shopSlot = it->shopSlot;
        unit->money = it->money;
        unit->type = it->type;
        unit->typeId = it->typeId;
        unit->count = it->count;
        unit->quality = it->quality;
        unit->gems = it->gems;
        unit->craftName = it->craftName;
    }

    int length = outgoing.baseLength + (outgoing.itemCount * sizeof(MyShopUnit_EP6_4));
    SConnection::Send(user, &outgoing, length);
}

unsigned u0x487350 = 0x487350;
void __declspec(naked) naked_0x48733F()
{
    __asm
    {
        pushad

        lea eax,[esp+0x38]

        push eax // packet
        push ecx // user
        call hook_0x48733F
        add esp,0x8

        popad
        
        jmp u0x487350
    }
}

void hook::packet_myshop()
{
    // stMyShop::SendItemList
    util::detour((void*)0x48733F, naked_0x48733F, 6);
}
