#include <shaiya/include/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/network/game/outgoing/2300.h"
using namespace shaiya;

namespace packet_myshop
{
    void send_item_list_hook(CUser* user, Packet buffer)
    {
        MyShopItemListOutgoing outgoing{};
        outgoing.opcode = util::deserialize<uint16_t>(buffer, 0);
        outgoing.itemCount = util::deserialize<uint8_t>(buffer, 2);

        int offset = 0;
        for (int i = 0; i < outgoing.itemCount; ++i)
        {
            Item230B item230B{};
            item230B.slot = util::deserialize<uint8_t>(buffer, 3 + offset);
            item230B.price = util::deserialize<uint32_t>(buffer, 4 + offset);
            item230B.type = util::deserialize<uint8_t>(buffer, 8 + offset);
            item230B.typeId = util::deserialize<uint8_t>(buffer, 9 + offset);
            item230B.count = util::deserialize<uint8_t>(buffer, 10 + offset);
            item230B.quality = util::deserialize<uint16_t>(buffer, 11 + offset);
            std::memcpy(item230B.gems.data(), &buffer[13 + offset], item230B.gems.size());
            std::memcpy(item230B.craftName.data(), &buffer[19 + offset], item230B.craftName.size());
            outgoing.itemList[i] = item230B;
            offset += 37;
        }

        int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item230B));
        SConnection::Send(&user->connection, &outgoing, length);
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
