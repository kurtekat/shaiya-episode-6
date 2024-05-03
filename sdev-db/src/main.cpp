#include <array>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
using namespace shaiya;

void user_hook(CUser* user)
{
    EquipmentEx equipment{};
    std::fill(user->equipmentEx.begin(), user->equipmentEx.end(), equipment);
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

unsigned u0x402906 = 0x402906;
void __declspec(naked) naked_0x402900()
{
    __asm
    {
        pushad

        push esi // user
        call user_hook
        add esp,0x4

        popad

        // original
        sub esp,0xC
        push ebx
        xor ebx,ebx
        jmp u0x402906
    }
}

void Main()
{
    // CUser::CUser
    util::detour((void*)0x4017B2, naked_0x4017B2, 6);
    // CUser::Reset
    util::detour((void*)0x402900, naked_0x402900, 6);
    // change 0x8858 to 0x8948
    std::array<uint8_t, 2> a00{ 0x48, 0x89 };
    // SSyncHeap<CUser>::Alloc
    util::write_memory((void*)0x40F474, &a00, 2);

    hook::user_character();
    hook::character_list();
}
