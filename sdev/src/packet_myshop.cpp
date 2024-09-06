#include <ranges>
#include <shaiya/include/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/MyShop.h"
#include "include/shaiya/include/network/game/outgoing/2300.h"
using namespace shaiya;

namespace packet_myshop
{
    void send_item_list(CUser* user, MyShop* myShop)
    {
        MyShopItemListOutgoing outgoing{};
        outgoing.itemCount = 0;

        const auto& market = std::ranges::views::zip(
            std::as_const(myShop->srcBag),
            std::as_const(myShop->srcSlot),
            std::as_const(myShop->price)
        );

        for (int slot = 0; const auto& [srcBag, srcSlot, price] : market)
        {
            if (!srcBag || srcBag > user->bagsUnlocked || srcSlot >= max_inventory_slot)
            {
                ++slot;
                continue;
            }

            auto& item = myShop->user->inventory[srcBag][srcSlot];
            if (!item)
            {
                ++slot;
                continue;
            }

            Item230B item230B{};
            item230B.slot = slot;
            item230B.price = price;
            item230B.type = item->type;
            item230B.typeId = item->typeId;
            item230B.count = item->count;
            item230B.quality = item->quality;
            item230B.gems = item->gems;
            item230B.craftName = item->craftName;
            outgoing.itemList[outgoing.itemCount] = item230B;

            ++outgoing.itemCount;
            ++slot;
        }

        int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item230B));
        SConnection::Send(&user->connection, &outgoing, length);
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
