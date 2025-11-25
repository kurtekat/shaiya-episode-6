#include <util/util.h>
#include <shaiya/include/network/game/outgoing/2300.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/NetworkHelper.h"
using namespace shaiya;

namespace packet_myshop
{
    /// <summary>
    /// Sends packet 0x230B (6.4) to the user. The item dates will be zero.
    /// </summary>
    void send_0x230B(CUser* user, GameMyShopItemListOutgoing<MyShopUnit_EP5>* packet)
    {
        GameMyShopItemListOutgoing<MyShopUnit_EP6_4> outgoing{};
        outgoing.itemCount = packet->itemCount;

        auto it = packet->itemList.cbegin();
        auto last = it + packet->itemCount;
        auto dest = outgoing.itemList.begin();

        for (; it != last; ++it, ++dest)
        {
            dest->shopSlot = it->shopSlot;
            dest->money = it->money;
            dest->type = it->type;
            dest->typeId = it->typeId;
            dest->count = it->count;
            dest->quality = it->quality;
            dest->gems = it->gems;
            dest->craftName = it->craftName;
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
