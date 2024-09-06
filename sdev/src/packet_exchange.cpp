#include <shaiya/include/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/network/game/incoming/0A00.h"
#include "include/shaiya/include/network/game/outgoing/0A00.h"
#include "include/shaiya/include/network/game/outgoing/2400.h"
using namespace shaiya;

namespace packet_exchange
{
    void send_cancel_ready(CUser* user)
    {
        user->exchange.ready = false;
        ExchangeOutgoing outgoing(ExchangeType::CancelReady, true);
        SConnection::Send(&user->connection, &outgoing, sizeof(ExchangeOutgoing));
    }

    void send_cancel_confirm(CUser* user, CUser* exchangeUser)
    {
        user->exchange.confirmed = false;
        ExchangeConfirmOutgoing outgoing(ExchangeType::Sender, false);
        SConnection::Send(&user->connection, &outgoing, sizeof(ExchangeConfirmOutgoing));

        outgoing.excType = ExchangeType::Target;
        SConnection::Send(&user->connection, &outgoing, sizeof(ExchangeConfirmOutgoing));

        exchangeUser->exchange.confirmed = false;
        outgoing.excType = ExchangeType::Sender;
        SConnection::Send(&exchangeUser->connection, &outgoing, sizeof(ExchangeConfirmOutgoing));

        outgoing.excType = ExchangeType::Target;
        SConnection::Send(&exchangeUser->connection, &outgoing, sizeof(ExchangeConfirmOutgoing));
    }

    void send_cancel(CUser* user, CUser* exchangeUser)
    {
        send_cancel_ready(user);
        send_cancel_ready(exchangeUser);
        send_cancel_confirm(user, exchangeUser);
    }

    void confirm_handler(CUser* user, ExchangeConfirmIncoming* incoming)
    {
        if (!user->exchange.user)
            return;

        if (incoming->confirmed)
        {
            user->exchange.confirmed = true;
            ExchangeConfirmOutgoing outgoing(ExchangeType::Sender, true);
            SConnection::Send(&user->connection, &outgoing, sizeof(ExchangeConfirmOutgoing));

            outgoing.excType = ExchangeType::Target;
            SConnection::Send(&user->exchange.user->connection, &outgoing, sizeof(ExchangeConfirmOutgoing));
        }
        else
            send_cancel(user, user->exchange.user);
    }

    void send_item(CUser* user, CUser* exchangeUser, Packet buffer, bool pvp)
    {
        ExchangeItemOutgoing outgoing{};
        outgoing.opcode = pvp ? 0x240D : 0xA09;
        outgoing.destSlot = util::deserialize<uint8_t>(buffer, 5);

        auto bag = util::deserialize<uint8_t>(buffer, 2);
        auto slot = util::deserialize<uint8_t>(buffer, 3);

        if (!bag || bag > exchangeUser->bagsUnlocked || slot >= max_inventory_slot)
            return;

        auto& item = exchangeUser->inventory[bag][slot];
        if (!item)
            return;

        outgoing.type = item->type;
        outgoing.typeId = item->typeId;
        outgoing.count = util::deserialize<uint8_t>(buffer, 4);
        outgoing.quality = item->quality;
        outgoing.gems = item->gems;
        outgoing.craftName = item->craftName;
        SConnection::Send(&user->connection, &outgoing, sizeof(ExchangeItemOutgoing));
    }
}

unsigned u0x47D969 = 0x47D969;
unsigned u0x47E0DA = 0x47E0DA;
void __declspec(naked) naked_0x47D964()
{
    __asm
    {
        add eax,-0xA01
        cmp eax,0x9
        je case_0xA0A
        jmp u0x47D969

        case_0xA0A:
        pushad

        push edi // buffer
        push ebx // user
        call packet_exchange::confirm_handler
        add esp,0x8

        popad

        jmp u0x47E0DA
    }
}

unsigned u0x47E29D = 0x47E29D;
void __declspec(naked) naked_0x47E26F()
{
    __asm
    {
        pushad

        push esi // exchange user
        push ecx // user
        call packet_exchange::send_cancel
        add esp,0x8

        popad

        jmp u0x47E29D
    }
}

unsigned u0x47E250 = 0x47E250;
unsigned u0x47DE0D = 0x47DE0D;
void __declspec(naked) naked_0x47DE08()
{
    __asm
    {
        pushad

        push esi // exchange user
        push ebx // user
        call packet_exchange::send_cancel
        add esp,0x8

        popad

        // original
        call u0x47E250
        jmp u0x47DE0D
    }
}

unsigned u0x47DFC5 = 0x47DFC5;
void __declspec(naked) naked_0x47DFC0()
{
    __asm
    {
        pushad

        push esi // exchange user
        push ebx // user
        call packet_exchange::send_cancel
        add esp,0x8

        popad

        // original
        call u0x47E250
        jmp u0x47DFC5
    }
}

unsigned u0x47DF34 = 0x47DF34;
void __declspec(naked) naked_0x47DE7B()
{
    __asm
    {
        pushad

        push 0x0
        push edi // packet
        push ebx // exchange user
        push esi // user
        call packet_exchange::send_item
        add esp,0x10

        popad

        jmp u0x47DF34
    }
}

unsigned u0x48C753 = 0x48C753;
void __declspec(naked) naked_0x48C69A()
{
    __asm
    {
        pushad

        push 0x1
        push edi // packet
        push ebp // exchange user
        push esi // user
        call packet_exchange::send_item
        add esp,0x10

        popad

        jmp u0x48C753
    }
}

void hook::packet_exchange()
{
    // CUser::PacketExchange switch
    util::detour((void*)0x47D964, naked_0x47D964, 5);
    // CUser::ExchangeCancelReady
    util::detour((void*)0x47E26F, naked_0x47E26F, 6);
    // CUser::PacketExchange case 0xA06
    util::detour((void*)0x47DE08, naked_0x47DE08, 5);
    // CUser::PacketExchange case 0xA07
    util::detour((void*)0x47DFC0, naked_0x47DFC0, 5);

#ifdef SHAIYA_EP6_4_PT
    // CUser::PacketExchange case 0xA06
    util::detour((void*)0x47DE7B, naked_0x47DE7B, 8);
    // CUser::PacketPvP case 0x240A
    util::detour((void*)0x48C69A, naked_0x48C69A, 8);
#endif
}
