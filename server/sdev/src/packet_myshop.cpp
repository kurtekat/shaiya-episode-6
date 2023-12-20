#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/2300.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/MyShop.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

namespace packet_myshop
{
    void send_item_list(CUser* user, MyShop* myShop)
    {
        constexpr int packet_size_without_list = 3;

        MyShopItemListOutgoing packet{};
        packet.itemCount = 0;

        for (int slot = 0; slot < max_myshop_slot; ++slot)
        {
            auto srcBag = myShop->srcBag[slot];
            auto srcSlot = myShop->srcSlot[slot];

            if (!srcBag)
                continue;

            auto& item = myShop->user->inventory[srcBag][srcSlot];
            if (!item)
                continue;

            Item230B item230B{};
            item230B.slot = slot;
            item230B.price = myShop->price[slot];
            item230B.type = item->type;
            item230B.typeId = item->typeId;
            item230B.count = item->count;
            item230B.quality = item->quality;
            item230B.gems = item->gems;

            #ifdef SHAIYA_EP6_ITEM_DURATION
            if (ServerTime::IsTimedItem(item->itemInfo))
            {
                item230B.toDate = ServerTime::GetExpireTime(item->makeTime, item->itemInfo->range);
                item230B.fromDate = item230B.toDate ? item->makeTime : 0;
            }
            #endif

            item230B.craftName = item->craftName;
            packet.itemList[packet.itemCount] = item230B;

            ++packet.itemCount;
        }

        int length = packet_size_without_list + (packet.itemCount * sizeof(Item230B));
        SConnection::Send(&user->connection, &packet, length);
    }
}

unsigned u0x4877A6 = 0x4877A6;
void __declspec(naked) naked_0x48779E()
{
    __asm
    {
        pushad

        push esi // myShop
        push ebp // user
        call packet_myshop::send_item_list
        add esp,0x8

        popad
        
        jmp u0x4877A6
    }
}

void hook::packet_myshop()
{
    // CUser::PacketMyShop
    util::detour((void*)0x48779E, naked_0x48779E, 8);
}
