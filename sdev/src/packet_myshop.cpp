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
    /// <param name="user"></param>
    /// <param name="packet"></param>
    void send_0x230B(CUser* user, GameMyShopItemListOutgoing<MyShopUnit_EP5>* packet)
    {
        GameMyShopItemListOutgoing<MyShopUnit_EP6_4> outgoing{};
        outgoing.opcode = packet->opcode;
        outgoing.itemCount = packet->itemCount;

        for (int i = 0; i < outgoing.itemCount; ++i)
        {
            MyShopUnit_EP6_4 item230B{};
            item230B.shopSlot = packet->itemList[i].shopSlot;
            item230B.money = packet->itemList[i].money;
            item230B.type = packet->itemList[i].type;
            item230B.typeId = packet->itemList[i].typeId;
            item230B.count = packet->itemList[i].count;
            item230B.quality = packet->itemList[i].quality;
            item230B.gems = packet->itemList[i].gems;
            item230B.craftName = packet->itemList[i].craftName;       
            outgoing.itemList[i] = item230B;
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
