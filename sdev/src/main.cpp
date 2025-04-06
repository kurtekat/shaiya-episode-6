#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemRemake.h"
#include "include/shaiya/include/RevengeMark.h"
#include "include/shaiya/include/Synergy.h"
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void user_leave_world_hook(CUser* user)
{
    g_appliedSynergies.erase(user->id);
    g_revengeMarks.erase(user->id);
}

/// <summary>
/// Please check Cheat Engine scripts for instructions that access 
/// extended user memory. Adjust the scripts and increase the user 
/// allocation size as needed. (e.g., 0x6500)
/// 
/// Scripts accessing memory between 0x62A0 and 0x62F4 will become 
/// an issue sooner or later.
/// </summary>
/// <param name="user"></param>
void user_hook(CUser* user)
{
    user->exchange.confirmed = false;
    user->itemQualityLvEx = {};
    user->itemQualityEx = {};
    user->skillAbility70 = {};
    user->multiplyQuestExpRate = 0;
}

unsigned u0x45516B = 0x45516B;
void __declspec(naked) naked_0x455165()
{
    __asm
    {
        pushad

        push edi // user
        call user_hook
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
        call user_hook
        add esp,0x4

        popad

        // original
        mov [edi+0x58EC],ebx
        jmp u0x455A89
    }
}

unsigned u0x455C46 = 0x455C46;
void __declspec(naked) naked_0x455C40()
{
    __asm
    {
        pushad

        push ecx // user
        call user_leave_world_hook
        add esp,0x4

        popad

        // original
        push ebp
        mov ebp,esp
        and esp,-0x8
        jmp u0x455C46
    }
}

void Main()
{
    // CUser::CUser
    util::detour((void*)0x455165, naked_0x455165, 6);
    // CUser::ResetCharacter
    util::detour((void*)0x455A83, naked_0x455A83, 6);
    // CUser::LeaveWorld
    util::detour((void*)0x455C40, naked_0x455C40, 6);
    // change 0x62A0 to 0x62F4
    int size = 0x62F4;
    // SSyncHeap<CUser>::Alloc
    util::write_memory((void*)0x411F74, &size, 4);

    hook::item_effect();
    hook::packet_character();
    hook::packet_exchange();
    hook::packet_gem();
    //hook::packet_mailbox();
    hook::packet_market();
    hook::packet_myshop();
    hook::packet_party();
    hook::packet_quest();
    hook::packet_shop();
    hook::revenge_mark();
    hook::user_equipment();
    hook::user_shape();
    hook::user_skill();
    hook::user_status();
    ItemRemake4::init();
    ItemRemake5::init();
    Synergy::init();
    Synthesis::init();
}
