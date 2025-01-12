#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/network/game/outgoing/2300.h"
using namespace shaiya;

namespace packet_myshop
{
    /// <summary>
    /// Sends packet 0x230B (6.4) to the user. The item dates will be zero.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="packet"></param>
    void send_item_list_hook(CUser* user, MyShopItemListOutgoing_EP5* packet)
    {
        MyShopItemListOutgoing_EP6_4 outgoing{};
        outgoing.opcode = packet->opcode;
        outgoing.itemCount = packet->itemCount;

        if (outgoing.itemCount > outgoing.itemList.size())
            return;

        for (int i = 0; i < outgoing.itemCount; ++i)
        {
            Item230B_EP6_4 item230B{};
            item230B.slot = packet->itemList[i].slot;
            item230B.price = packet->itemList[i].price;
            item230B.type = packet->itemList[i].type;
            item230B.typeId = packet->itemList[i].typeId;
            item230B.count = packet->itemList[i].count;
            item230B.quality = packet->itemList[i].quality;
            item230B.gems = packet->itemList[i].gems;
            item230B.craftName = packet->itemList[i].craftName;       
            outgoing.itemList[i] = item230B;
        }

        int length = outgoing.baseLength + (outgoing.itemCount * sizeof(Item230B_EP6_4));
        Helpers::Send(user, &outgoing, length);
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
        call packet_myshop::send_item_list_hook
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
