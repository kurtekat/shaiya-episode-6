#include <map>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/RevengeMark.h>
#include <include/shaiya/include/Synergy.h>
#include <include/shaiya/include/Synthesis.h>
#include <util/include/util.h>
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

#ifdef SHAIYA_EP6
    g_appliedSynergies.erase(user->id);
#endif

#ifdef SHAIYA_EP6_4_PT
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

void user_ctor_hook(CUser* user)
{
    user->exchange.confirmed = false;

#ifdef SHAIYA_EP6
    user->skillAbility70.skillId = 0;
    user->skillAbility70.skillLv = 0;
    user->skillAbility70.triggered = false;
    user->skillAbility70.keepTime = 0;
#endif

#ifdef SHAIYA_EP6_4_PT
    user->townScrollGateIndex = 0;
    user->itemQualityEx.fill(0);
    user->itemQualityLvEx.fill(0);
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
        call user_ctor_hook
        add esp,0x4

        popad

        jmp u0x45516B
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

    hook::packet_exchange();
    hook::packet_shop();

#ifdef SHAIYA_EP6_4_PT
    hook::item_duration();
    hook::item_effect();
    hook::packet_character();
    hook::packet_gem();
    hook::packet_market();
    hook::packet_myshop();
    hook::revenge_mark();
    hook::user_shape();
#endif

#ifdef SHAIYA_EP6
    hook::npc_quest();
    hook::user_apply_skill();
    hook::user_equipment();
    hook::user_status();
    Synergy::init();
#endif

#ifdef SHAIYA_EP6_4_PT
    Synthesis::init();
#endif
}
