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
        constexpr int shop_bag_size = 20;

        MyShopItemList item_list{};
        item_list.opcode = 0x230B;
        item_list.itemCount = 0;

        for (int i = 0; i < shop_bag_size; ++i)
        {
            auto bag = myShop->srcBag[i];
            auto slot = myShop->srcSlot[i];

            if (!myShop->srcBag[i])
                continue;

            auto& item = myShop->user->inventory[bag][slot];
            if (!item)
                continue;

            MyShopItem myshop_item{};
            myshop_item.index = item_list.itemCount;
            myshop_item.price = myShop->price[i];
            myshop_item.type = item->type;
            myshop_item.typeId = item->typeId;
            myshop_item.count = item->count;
            myshop_item.quality = item->quality;
            std::memcpy(&myshop_item.gems, &item->gems, sizeof(item->gems));

            // to-do: implement dates
            myshop_item.toDate = 0;
            myshop_item.fromDate = 0;

            std::memcpy(myshop_item.craftName, &item->craftName, sizeof(CraftName));
            std::memcpy(&item_list.inventory[item_list.itemCount], &myshop_item, sizeof(MyShopItem));
            ++item_list.itemCount;
        }

        constexpr int size_without_inventory = 3;
        int packet_size = size_without_inventory + (item_list.itemCount * sizeof(MyShopItem));
        SConnection::Send(user, &item_list, packet_size);
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
