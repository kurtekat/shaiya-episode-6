#include <util/util.h>
#include "include/main.h"

// Author: Cups
// Date: 31/10/2017

unsigned u0x404E89 = 0x404E89;
unsigned u0x404FAE = 0x404FAE;
void __declspec(naked) naked_0x404E84()
{
    __asm
    {
        // original
        push eax
        mov ebx,ecx
        mov eax,esi

        // rsa key length
        cmp ecx,0x80
        jne _0x404FAE
        jmp u0x404E89

        _0x404FAE:
        jmp u0x404FAE
    }
}

void Main()
{
    // CUserCrypto::KeyInit
    util::detour((void*)0x404E84, naked_0x404E84, 5);
    hook::get_user();
}
