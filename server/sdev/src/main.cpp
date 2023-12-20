#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/Revenge.h>
#include <include/shaiya/include/ServerTime.h>
#include <include/shaiya/include/Synergy.h>
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

    #ifdef SHAIYA_EP6_ITEM_SET
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

unsigned u0x45516B = 0x45516B;
void __declspec(naked) naked_0x455165()
{
    __asm
    {
        // original
        mov [edi+0x6264],ebx

        // initialize memory
        mov [edi+0x15E4],ebx
        mov [edi+0x5D9C],ebx
        mov [edi+0x5DA0],ebx
        mov [edi+0x5DA4],ebx

        jmp u0x45516B
    }
}

void Main(HMODULE hModule)
{
    DisableThreadLibraryCalls(hModule);
    // CUser::EnterWorld
    util::detour((void*)0x455B00, naked_0x455B00, 6);
    // CUser::LeaveWorld
    util::detour((void*)0x455C40, naked_0x455C40, 6);
    // CUser::CUser
    util::detour((void*)0x455165, naked_0x455165, 6);

    hook::packet_exchange();
    hook::packet_shop();

    #ifdef SHAIYA_EP6_COMMON
    hook::user_status();
    #endif

    #ifdef SHAIYA_EP6_4_PT
    hook::packet_gem();
    hook::packet_market();
    hook::revenge_mark();
    #endif

    #ifdef SHAIYA_EP6_0511
    hook::user_apply_skill();
    #endif

    #ifdef SHAIYA_EP6_QUEST_RESULT
    hook::npc_quest();
    #endif

    #ifdef SHAIYA_EP6_ITEM_DURATION
    hook::item_duration();
    hook::packet_myshop();
    #endif

    #ifdef SHAIYA_EP6_ITEM_EFFECT
    hook::item_effect();
    #endif

    #ifdef SHAIYA_EP6_ITEM_EQUIPMENT
    hook::packet_character();
    hook::user_equipment();
    hook::user_shape();
    #endif

    #ifdef SHAIYA_EP6_ITEM_SET
    Synergy::init();
    #endif
}
