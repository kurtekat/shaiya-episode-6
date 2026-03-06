#include <util/util.h>
#include <shaiya/include/network/game/incoming/0A00.h>
#include <shaiya/include/network/game/outgoing/0A00.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

namespace packet_exchange
{
    /// <summary>
    /// Handles incoming 0xA0A packets.
    /// </summary>
    void handler_0xA0A(CUser* user, GameExchangeConfirmIncoming* incoming)
    {
        if (user->exchange.status < ExchangeStatus::Ready)
            return;

        auto& exchangeUser = user->exchange.user;
        if (!exchangeUser)
            return;

        if (user->pvpStatus != UserPvPStatus::None)
            return;

        if (exchangeUser->pvpStatus != UserPvPStatus::None)
            return;

        if (user->myShop.status != MyShopStatus::None)
            return;

        if (exchangeUser->myShop.status != MyShopStatus::None)
            return;

        if (user == exchangeUser)
        {
            SConnection::Close(user, 9, 0);
            return;
        }

        if (incoming->confirmed)
        {
            user->exchange.status = ExchangeStatus::Confirmed;

            GameExchangeConfirmOutgoing outgoing{};
            outgoing.type = GameExchangeConfirmType::User;
            outgoing.confirmed = true;
            SConnection::Send(user, &outgoing, sizeof(GameExchangeConfirmOutgoing));

            outgoing.type = GameExchangeConfirmType::ExchangeUser;
            SConnection::Send(exchangeUser, &outgoing, sizeof(GameExchangeConfirmOutgoing));
        }
        else
        {
            CUser::ExchangeCancelReady(user, exchangeUser);

            if (user->exchange.status == ExchangeStatus::Confirmed)
            {
                user->exchange.status = ExchangeStatus::Ready;

                GameExchangeConfirmOutgoing outgoing{};
                outgoing.type = GameExchangeConfirmType::User;
                outgoing.confirmed = false;
                SConnection::Send(user, &outgoing, sizeof(GameExchangeConfirmOutgoing));

                outgoing.type = GameExchangeConfirmType::ExchangeUser;
                SConnection::Send(exchangeUser, &outgoing, sizeof(GameExchangeConfirmOutgoing));
            }

            if (exchangeUser->exchange.status == ExchangeStatus::Confirmed)
            {
                exchangeUser->exchange.status = ExchangeStatus::Ready;

                GameExchangeConfirmOutgoing outgoing{};
                outgoing.type = GameExchangeConfirmType::User;
                outgoing.confirmed = false;
                SConnection::Send(exchangeUser, &outgoing, sizeof(GameExchangeConfirmOutgoing));

                outgoing.type = GameExchangeConfirmType::ExchangeUser;
                SConnection::Send(user, &outgoing, sizeof(GameExchangeConfirmOutgoing));
            }
        }
    }

    /// <summary>
    /// Sends packets 0xA09 or 0x240D (6.4) to the user. The item dates will be zero.
    /// </summary>
    void hook(CUser* user, GameExchangeAddDestOutgoing_EP5* packet)
    {
        GameExchangeAddDestOutgoing_EP6_4 outgoing{};
        outgoing.opcode = packet->opcode;
        outgoing.destSlot = packet->destSlot;
        outgoing.type = packet->type;
        outgoing.typeId = packet->typeId;
        outgoing.count = packet->count;
        outgoing.quality = packet->quality;
        outgoing.gems = packet->gems;
        outgoing.craftName = packet->craftName;
        SConnection::Send(user, &outgoing, sizeof(GameExchangeAddDestOutgoing_EP6_4));
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

        push edi // packet
        push ebx // user
        call packet_exchange::handler_0xA0A
        add esp,0x8

        popad

        jmp u0x47E0DA
    }
}

unsigned u0x47DBBF = 0x47DBBF;
void __declspec(naked) naked_0x47DB9E()
{
    __asm
    {
        // user->exchange.status
        cmp dword ptr[ebx+0x15C0],0x4
        jne _0x47E0DA
        // user->exchange.user
        mov esi,[ebx+0x15C4]
        test esi,esi
        je _0x47E0DA
        // user->exchange.status
        cmp dword ptr[esi+0x15C0],0x4
        jne _0x47E0DA
        // original
        lea ebp,[ebx+0x15C0]
        jmp u0x47DBBF

        _0x47E0DA:
        jmp u0x47E0DA
    }
}

unsigned u0x47DF34 = 0x47DF34;
void __declspec(naked) naked_0x47DF22()
{
    __asm
    {
        // itemCount
        mov byte ptr[esp+0x3E],dl

        pushad

        lea eax,[esp+0x3C]

        push eax // packet
        push esi // user
        call packet_exchange::hook
        add esp,0x8

        popad

        jmp u0x47DF34
    }
}

unsigned u0x48C902 = 0x48C902;
void __declspec(naked) naked_0x48C741()
{
    __asm
    {
        // itemCount
        mov byte ptr[esp+0x66],al

        pushad

        lea eax,[esp+0x64]

        push eax // packet
        push esi // user
        call packet_exchange::hook
        add esp,0x8

        popad

        jmp u0x48C902
    }
}

void hook::packet_exchange()
{
    // CUser::PacketExchange switch
    util::detour((void*)0x47D964, naked_0x47D964, 5);
    // CUser::PacketExchange case 0xA05
    util::detour((void*)0x47DB9E, naked_0x47DB9E, 7);
    // CUser::PacketExchange case 0xA06
    util::detour((void*)0x47DF22, naked_0x47DF22, 6);
    // CUser::PacketPvP case 0x240A
    util::detour((void*)0x48C741, naked_0x48C741, 6);
}
