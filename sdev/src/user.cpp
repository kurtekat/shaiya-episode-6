#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/RevengeMark.h"
#include "include/shaiya/Synergy.h"
using namespace shaiya;

/// <summary>
/// Please check Cheat Engine scripts for instructions that access extended user memory. 
/// Change the scripts and increase the allocation size as needed (e.g., 0x6500).
/// </summary>

void hook_0x414C33(CUser* user)
{
    g_itemSetSynergies.erase(user->id);
    g_revengeMarks.erase(user->id);
}

void hook_0x455165(CUser* user)
{
    user->itemQualityLvEx = {};
    user->itemQualityEx = {};
    user->multiplyQuestExpRate = 0;
    user->ability70Triggered = false;
    user->ability71Triggered = false;
    user->ability72Triggered = false;
}

void hook_0x455A83(CUser* user)
{
    user->itemQualityLvEx = {};
    user->itemQualityEx = {};
    user->multiplyQuestExpRate = 0;
    user->ability70Triggered = false;
    user->ability71Triggered = false;
    user->ability72Triggered = false;
}

void __declspec(naked) naked_0x414C33()
{
    __asm
    {
        pushad

        push edi // user
        call hook_0x414C33
        add esp,0x4

        popad

        // original
        pop esi
        mov esp,ebp
        pop ebp
        retn
    }
}

unsigned u0x45516B = 0x45516B;
void __declspec(naked) naked_0x455165()
{
    __asm
    {
        pushad

        push edi // user
        call hook_0x455165
        add esp,0x4

        popad

        // original
        mov [edi+0x6264],ebx
        jmp u0x45516B
    }
}

unsigned u0x455A89 = 0x455A89;
void __declspec(naked) naked_0x455A83()
{
    __asm
    {
        pushad
 
        push edi // user
        call hook_0x455A83
        add esp,0x4

        popad

        // original
        mov [edi+0x58EC],ebx
        jmp u0x455A89
    }
}

void hook::user()
{
    // CWorld::UserLeaveWorld
    util::detour((void*)0x414C33, naked_0x414C33, 5);
    // CUser::CUser
    util::detour((void*)0x455165, naked_0x455165, 6);
    // CUser::ResetCharacter
    util::detour((void*)0x455A83, naked_0x455A83, 6);
    // Change 0x62A0 to 0x62F0
    int size = 0x62F0;
    // SSyncHeap<CUser>::Alloc
    util::write_memory((void*)0x411F74, &size, 4);
}
