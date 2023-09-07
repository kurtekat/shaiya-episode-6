#pragma unmanaged
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/230B.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/MyShop.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace packet_myshop
{
    void send_item_list(CUser* user, MyShop* myShop)
    {
        constexpr int max_shop_slot_count = 20;

        MyShopItemList myshop{};
        myshop.opcode = 0x230B;
        myshop.itemCount = 0;

        for (int shop_slot = 0; shop_slot < max_shop_slot_count; ++shop_slot)
        {
            auto src_bag = myShop->srcBag[shop_slot];
            auto src_slot = myShop->srcSlot[shop_slot];

            if (!src_bag)
                continue;

            auto& item = myShop->user->inventory[src_bag][src_slot];
            if (!item)
                continue;

            MyShopItem myshop_item{};
            myshop_item.slot = shop_slot;
            myshop_item.price = myShop->price[shop_slot];
            myshop_item.type = item->type;
            myshop_item.typeId = item->typeId;
            myshop_item.count = item->count;
            myshop_item.quality = item->quality;
            std::memcpy(&myshop_item.gems, &item->gems, sizeof(item->gems));

            // to-do: implement dates
            myshop_item.toDate = 0;
            myshop_item.fromDate = 0;

            std::memcpy(myshop_item.craftName, &item->craftName, sizeof(CraftName));
            std::memcpy(&myshop.list[myshop.itemCount], &myshop_item, sizeof(MyShopItem));
            ++myshop.itemCount;
        }

        constexpr int packet_size_without_list = 3;
        int packet_size = packet_size_without_list + (myshop.itemCount * sizeof(MyShopItem));
        SConnection::Send(user, &myshop, packet_size);
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
