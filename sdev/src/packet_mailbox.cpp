#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/SConnection.h"
using namespace shaiya;

// This feature will not be implemented.

namespace packet_mailbox
{
    void handler(CUser* user, uint8_t* packet)
    {
        auto opcode = util::deserialize<uint16_t>(packet, 0);
        
        switch (opcode)
        {
        case 0x2A01:
        {
            break;
        }
        case 0x2A03:
        {
            break;
        }
        case 0x2A04:
        {
            break;
        }
        case 0x2A06:
        {
            break;
        }
        default:
            SConnection::Close(user, 9, 0);
            break;
        }
    }
}

unsigned u0x474FA5 = 0x474FA5;
unsigned u0x474FFE = 0x474FFE;
void __declspec(naked) naked_0x474FA0()
{
    __asm
    {
        cmp eax,0x2A00
        je case_0x2A00
        // original
        cmp eax,0x3100
        jmp u0x474FA5

        case_0x2A00:
        pushad

        push edi // packet
        push ebx // user
        call packet_mailbox::handler
        add esp,0x8

        popad

        jmp u0x474FFE
    }
}

void hook::packet_mailbox()
{
    // CUser::PacketProcessing
    util::detour((void*)0x474FA0, naked_0x474FA0, 5);
}
