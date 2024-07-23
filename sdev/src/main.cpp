#include <map>
#include <vector>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/RevengeMark.h"
#include "include/shaiya/include/Synergy.h"
#include "include/shaiya/include/Synthesis.h"
#include "include/shaiya/include/TownMoveScroll.h"
using namespace shaiya;

void enter_world_hook(CUser* user)
{
    CUser::UpdateKCStatus(user);

    if (std::find(g_users.begin(), g_users.end(), user->id) == g_users.end())
        g_users.push_back(user->id);
}

void leave_world_hook(CUser* user)
{
    std::erase(g_users, user->id);

#ifdef SHAIYA_EP6_4_PT
    g_appliedSynergies.erase(user->id);
    g_revengeMark.erase(user->id);
#endif
}

unsigned u0x455B06 = 0x455B06;
void __declspec(naked) naked_0x455B00()
{
    __asm
    {
        pushad

        push ecx // user
        call enter_world_hook
        add esp,0x4

        popad

        // original
        sub esp,0x8C
        jmp u0x455B06
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

void init_custom_memory(CUser* user)
{
    user->exchange.confirmed = false;

#ifdef SHAIYA_EP6_4_PT
    user->itemQualityEx.fill(0);
    user->itemQualityLvEx.fill(0);

    user->townMoveScroll.bag = 0;
    user->townMoveScroll.slot = 0;
    user->townMoveScroll.gateIndex = 0;

    user->skillAbility.type70.skillId = 0;
    user->skillAbility.type70.skillLv = 0;
    user->skillAbility.type70.triggered = false;
    user->skillAbility.type70.keepTick = 0;

    user->skillAbility.type73Percentage = 0;
    user->skillAbility.type74Percentage = 0;
    user->skillAbility.type78Percentage = 0;
    user->skillAbility.type87QuestExpRate = 0;
#endif
}

unsigned u0x45516B = 0x45516B;
void __declspec(naked) naked_0x455165()
{
    __asm
    {
        // original
        mov [edi+0x6264],ebx

        pushad

        push edi // user
        call init_custom_memory
        add esp,0x4

        popad

        jmp u0x45516B
    }
}

unsigned u0x455316 = 0x455316;
void __declspec(naked) naked_0x455310()
{
    __asm
    {
        pushad

        push edi // user
        call init_custom_memory
        add esp,0x4

        popad

        // original
        sub esp,0x10
        push ebx
        xor ebx,ebx
        jmp u0x455316
    }
}

void Main()
{
    // CUser::EnterWorld
    util::detour((void*)0x455B00, naked_0x455B00, 6);
    // CUser::LeaveWorld
    util::detour((void*)0x455C40, naked_0x455C40, 6);
    // CUser::CUser
    util::detour((void*)0x455165, naked_0x455165, 6);
    // CUser::ResetCharacter
    util::detour((void*)0x455310, naked_0x455310, 6);

    hook::packet_exchange();
    hook::packet_shop();

#ifdef SHAIYA_EP6_4_PT
    // change 0x62A0 to 0x630C
    std::array<std::uint8_t, 2> a00{ 0x0C, 0x63 };
    // SSyncHeap<CUser>::Alloc
    util::write_memory((void*)0x411F74, &a00, 2);

    hook::item_duration();
    hook::item_effect();
    hook::npc_quest();
    hook::packet_character();
    hook::packet_gem();
    hook::packet_market();
    hook::packet_myshop();
    hook::revenge_mark();
    hook::user_apply_skill();
    hook::user_equipment();
    hook::user_shape();
    hook::user_status();
    Synergy::init();
    Synthesis::init();
#endif
}
