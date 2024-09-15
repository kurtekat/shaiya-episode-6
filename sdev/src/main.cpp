#include <array>
#include <map>
#include <vector>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/RevengeMark.h"
#include "include/shaiya/include/Synergy.h"
#include "include/shaiya/include/Synthesis.h"
using namespace shaiya;

void leave_world_hook(CUser* user)
{
    g_appliedSynergies.erase(user->connection.object.id);
    g_revengeMark.erase(user->connection.object.id);
}

void user_hook(CUser* user)
{
    user->exchange.confirmed = false;
#ifdef SHAIYA_EP6_4_PT
    user->itemQualityEx = {};
    user->itemQualityLvEx = {};
    user->townMoveScroll = {};
    user->skillAbility = {};
#endif
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
        call leave_world_hook
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

    hook::packet_exchange();
    hook::packet_shop();

#ifdef SHAIYA_EP6_4_PT
    // CUser::LeaveWorld
    util::detour((void*)0x455C40, naked_0x455C40, 6);
    // change 0x62A0 to 0x6300
    int size = 0x6300;
    // SSyncHeap<CUser>::Alloc
    util::write_memory((void*)0x411F74, &size, 4);

    hook::item_effect();
    hook::packet_character();
    hook::packet_gem();
    hook::packet_market();
    hook::packet_myshop();
    hook::packet_party();
    hook::packet_quest();
    hook::revenge_mark();
    hook::user_apply_skill();
    hook::user_equipment();
    hook::user_shape();
    hook::user_status();
    Synergy::init();
    Synthesis::init();
#endif
}
