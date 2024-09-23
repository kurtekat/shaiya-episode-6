#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
using namespace shaiya;

void user_hook(CUser* user)
{
    user->equipmentEx = {};
}

unsigned u0x4017B8 = 0x4017B8;
void __declspec(naked) naked_0x4017B2()
{
    __asm
    {
        pushad

        push esi // user
        call user_hook
        add esp,0x4

        popad

        // original
        mov [esi+0x8664],ebx
        jmp u0x4017B8
    }
}

unsigned u0x403456 = 0x403456;
void __declspec(naked) naked_0x403450()
{
    __asm
    {
        pushad

        push esi // user
        call user_hook
        add esp,0x4

        popad

        // original
        mov [esi+0x8664],ebx
        jmp u0x403456
    }
}

void Main()
{
    // CUser::CUser
    util::detour((void*)0x4017B2, naked_0x4017B2, 6);
    // CUser::Reset
    util::detour((void*)0x403450, naked_0x403450, 6);
    // change 0x8858 to 0x8948
    int size = 0x8948;
    // SSyncHeap<CUser>::Alloc
    util::write_memory((void*)0x40F474, &size, 4);

    hook::user_character();
    hook::character_list();
}
