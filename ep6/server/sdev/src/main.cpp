#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/include/CUser.h>
using namespace shaiya;

void enter_world_hook(CUser* user)
{
    CUser::UpdateKCStatus(user);
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

void Main(HMODULE hModule)
{
    DisableThreadLibraryCalls(hModule);
    // CUser::EnterWorld
    util::detour((void*)0x455B00, naked_0x455B00, 6);

    hook::packet_exchange();
    hook::packet_shop();

    // ep6 functions

    hook::packet_character();
    hook::packet_gem();
    hook::packet_market();
    hook::packet_myshop();
    hook::user_equipment();
    hook::user_shape();
    hook::user_status();
}
