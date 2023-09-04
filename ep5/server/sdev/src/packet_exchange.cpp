#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0A05.h>
#include <shaiya/packets/0A0A.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

// author: unknown

namespace packet_exchange
{
    void reset_state(CUser* user)
    {
        user->confirmExchangeState = 0;
        ConfirmExchangeResponse confirm_response{ 0xA0A, 1, 0 };
        SConnection::Send(user, &confirm_response, sizeof(ConfirmExchangeResponse));

        confirm_response.state1 = 2;
        SConnection::Send(user, &confirm_response, sizeof(ConfirmExchangeResponse));

        user->exchangeState = 0;
        ExchangeResponse exchange_response{ 0xA05, 3, 1 };
        SConnection::Send(user, &exchange_response, sizeof(ExchangeResponse));

        user->exchangeUser->confirmExchangeState = 0;
        confirm_response.state1 = 1;
        confirm_response.state2 = 0;
        SConnection::Send(user->exchangeUser, &confirm_response, sizeof(ConfirmExchangeResponse));

        confirm_response.state1 = 2;
        SConnection::Send(user->exchangeUser, &confirm_response, sizeof(ConfirmExchangeResponse));

        user->exchangeUser->exchangeState = 0;
        confirm_response.state1 = 3;
        confirm_response.state2 = 1;
        SConnection::Send(user->exchangeUser, &exchange_response, sizeof(ExchangeResponse));
    }

    void confirm_exchange_handler(CUser* user, Packet packet)
    {
        if (!user->exchangeUser)
            return;

        auto state = util::read_bytes<std::uint8_t>(packet, 2);

        if (state)
        {
            user->confirmExchangeState = 1;
            ConfirmExchangeResponse confirm_response{ 0xA0A, 1, 1 };
            SConnection::Send(user, &confirm_response, sizeof(ConfirmExchangeResponse));

            confirm_response.state1 = 2;
            SConnection::Send(user->exchangeUser, &confirm_response, sizeof(ConfirmExchangeResponse));
        }
        else
        {
            reset_state(user);
        }
    }

    void cancel_ready(CUser* user, CUser* exchangeUser)
    {
        user->confirmExchangeState = 0;
        exchangeUser->confirmExchangeState = 0;

        ConfirmExchangeResponse confirm_response{ 0xA0A, 1, 0 };
        SConnection::Send(user, &confirm_response, sizeof(ConfirmExchangeResponse));

        confirm_response.state1 = 2;
        SConnection::Send(user, &confirm_response, sizeof(ConfirmExchangeResponse));

        confirm_response.state1 = 1;
        SConnection::Send(exchangeUser, &confirm_response, sizeof(ConfirmExchangeResponse));

        confirm_response.state1 = 2;
        SConnection::Send(exchangeUser, &confirm_response, sizeof(ConfirmExchangeResponse));

        // original code

        ExchangeResponse exchange_response{ 0xA05, 3, 1 };
        SConnection::Send(user, &exchange_response, sizeof(ExchangeResponse));
        SConnection::Send(exchangeUser, &exchange_response, sizeof(ExchangeResponse));
    }

    void maybe_reset_state(CUser* user)
    {
        if (!user->confirmExchangeState)
            if (!user->exchangeUser->confirmExchangeState)
                return;

        reset_state(user);
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
        call packet_exchange::confirm_exchange_handler
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
        // user->confirmExchangeState
        cmp [ecx+0x1534],al
        jne _0x47E263
        // user->confirmExchangeState
        cmp [esi+0x1534],al
        jne _0x47E263
        // user->exchangeState
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
        // original
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
        // original
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
}
