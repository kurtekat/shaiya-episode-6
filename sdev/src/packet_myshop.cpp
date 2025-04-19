#include <ranges>
#include <util/util.h>
#include <shaiya/include/network/game/outgoing/2300.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/NetworkHelper.h"
using namespace shaiya;

namespace packet_myshop
{
    /// <summary>
    /// Sends packet 0x230B (6.4) to the user. The item dates will be zero.
    /// </summary>
    void send_0x230B(CUser* user, GameMyShopItemListOutgoing<MyShopUnit_EP5>* packet)
    {
        GameMyShopItemListOutgoing<MyShopUnit_EP6_4> outgoing{};
        outgoing.opcode = packet->opcode;
        outgoing.itemCount = packet->itemCount;

        for (auto&& [unit, item] : std::views::zip(
            outgoing.itemList, 
            std::as_const(packet->itemList)))
        {
            unit.shopSlot = item.shopSlot;
            unit.money = item.money;
            unit.type = item.type;
            unit.typeId = item.typeId;
            unit.count = item.count;
            unit.quality = item.quality;
            unit.gems = item.gems;
            unit.craftName = item.craftName;
        }

        int length = outgoing.baseLength + (outgoing.itemCount * sizeof(MyShopUnit_EP6_4));
        NetworkHelper::Send(user, &outgoing, length);
    }
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
        call packet_myshop::send_0x230B
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
