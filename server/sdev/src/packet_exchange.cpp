#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0A05.h>
#include <include/shaiya/packets/0A09.h>
#include <include/shaiya/packets/0A0A.h>
#include <include/shaiya/packets/240D.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

namespace packet_exchange
{
    void reset_state(CUser* user)
    {
        user->exchange.confirmState = 0;
        ExchangeConfirmOutgoing packet{ 0xA0A, 1, 0 };
        SConnection::Send(&user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        packet.state1 = 2;
        SConnection::Send(&user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        user->exchange.ready = false;
        ExchangeOutgoing packet2{ 0xA05, 3, 1 };
        SConnection::Send(&user->connection, &packet2, sizeof(ExchangeOutgoing));

        user->exchange.user->exchange.confirmState = 0;
        packet.state1 = 1;
        packet.state2 = 0;
        SConnection::Send(&user->exchange.user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        packet.state1 = 2;
        SConnection::Send(&user->exchange.user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        user->exchange.user->exchange.ready = false;
        SConnection::Send(&user->exchange.user->connection, &packet2, sizeof(ExchangeOutgoing));
    }

    void confirm_handler(CUser* user, Packet buffer)
    {
        if (!user->exchange.user)
            return;

        auto state = util::read_bytes<std::uint8_t>(buffer, 2);

        if (state)
        {
            user->exchange.confirmState = 1;
            ExchangeConfirmOutgoing packet{ 0xA0A, 1, 1 };
            SConnection::Send(&user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

            packet.state1 = 2;
            SConnection::Send(&user->exchange.user->connection, &packet, sizeof(ExchangeConfirmOutgoing));
        }
        else
        {
            reset_state(user);
        }
    }

    void cancel_ready(CUser* user, CUser* exchangeUser)
    {
        user->exchange.confirmState = 0;
        exchangeUser->exchange.confirmState = 0;

        ExchangeConfirmOutgoing packet{ 0xA0A, 1, 0 };
        SConnection::Send(&user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        packet.state1 = 2;
        SConnection::Send(&user->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        packet.state1 = 1;
        SConnection::Send(&exchangeUser->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        packet.state1 = 2;
        SConnection::Send(&exchangeUser->connection, &packet, sizeof(ExchangeConfirmOutgoing));

        // original code

        ExchangeOutgoing packet2{ 0xA05, 3, 1 };
        SConnection::Send(&user->connection, &packet2, sizeof(ExchangeOutgoing));
        SConnection::Send(&exchangeUser->connection, &packet2, sizeof(ExchangeOutgoing));
    }

    void maybe_reset_state(CUser* user)
    {
        if (!user->exchange.confirmState && !user->exchange.user->exchange.confirmState)
            return;

        reset_state(user);
    }

    void send_item(CUser* user, CUser* exchangeUser, Packet buffer, bool pvp)
    {
        ExchangeItemOutgoing packet{};
        packet.opcode = pvp ? 0x240D : 0xA09;
        packet.destSlot = util::read_bytes<std::uint8_t>(buffer, 5);

        auto bag = util::read_bytes<std::uint8_t>(buffer, 2);
        auto slot = util::read_bytes<std::uint8_t>(buffer, 3);

        if (!bag || bag > exchangeUser->bagsUnlocked || slot >= MAX_INVENTORY_SLOT)
            return;

        auto& item = exchangeUser->inventory[bag][slot];
        if (!item)
            return;

        packet.type = item->type;
        packet.typeId = item->typeId;
        packet.count = util::read_bytes<std::uint8_t>(buffer, 4);
        packet.quality = item->quality;
        packet.gems = item->gems;

        #ifdef WITH_ITEM_DURATION
        packet.toDate = ServerTime::GetExpireTime(item->makeTime, item->itemInfo->range);
        packet.fromDate = packet.toDate ? item->makeTime : 0;
        #endif

        packet.craftName = item->craftName;
        SConnection::Send(&user->connection, &packet, sizeof(ExchangeItemOutgoing));
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

unsigned u0x47E25B = 0x47E25B;
unsigned u0x47E263 = 0x47E263;
void __declspec(naked) naked_0x47E253()
{
    __asm
    {
        // user->exchange.confirmState
        cmp byte ptr[ecx+0x15E5],al
        jne _0x47E263

        // user->exchange.confirmState
        cmp byte ptr[esi+0x15E5],al
        jne _0x47E263

        // user->exchange.ready
        cmp byte ptr[ecx+0x15E4],al
        jne _0x47E263
        jmp u0x47E25B

        _0x47E263:
        jmp u0x47E263
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
        call packet_exchange::cancel_ready
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

        push ebx // user
        call packet_exchange::maybe_reset_state
        add esp,0x4

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

        push ebx // user
        call packet_exchange::maybe_reset_state
        add esp,0x4

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
    util::detour((void*)0x47E253, naked_0x47E253, 6);
    // CUser::ExchangeCancelReady
    util::detour((void*)0x47E26F, naked_0x47E26F, 6);
    // CUser::PacketExchange case 0xA06
    util::detour((void*)0x47DE08, naked_0x47DE08, 5);
    // CUser::PacketExchange case 0xA07
    util::detour((void*)0x47DFC0, naked_0x47DFC0, 5);

    #ifdef WITH_ITEM_DURATION
    // CUser::PacketExchange case 0xA06
    util::detour((void*)0x47DE7B, naked_0x47DE7B, 8);
    // CUser::PacketPvP case 0x240A
    util::detour((void*)0x48C69A, naked_0x48C69A, 8);
    #endif
}
