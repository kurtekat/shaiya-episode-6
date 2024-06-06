#include <array>
#include <format>
#include <util/util.h>
#include "include/main.h"

const std::array<uint16_t, 21> g_weapon_step
{
    0, 7, 14, 21, 31, 41, 51, 64, 77, 90, 106, 122, 138, 157, 176, 195, 217, 239, 261, 286, 311
};

int get_weapon_step(uint8_t enchantStep)
{
    if (enchantStep >= g_weapon_step.size())
        return 0;

    return g_weapon_step[enchantStep];
}

void format_chat_color_size(char* text)
{
    auto len = std::strlen(&text[8]);
    auto str = std::format("{:03}", len);
    std::memcpy(&text[2], str.data(), 3);
}

unsigned u0x57C56A = 0x57C56A;
void __declspec(naked) naked_0x57C565()
{
    __asm
    {
        pushad

        lea eax,[esi+edi]
        push eax
        call format_chat_color_size
        add esp,0x4

        popad

        // original
        mov dx,word ptr[esi+edi+0x2]
        jmp u0x57C56A
    }
}

unsigned u0x47E084 = 0x47E084;
void __declspec(naked) naked_0x47E07F()
{
    __asm
    {
        pushad

        lea eax,[edi+esi]
        push eax
        call format_chat_color_size
        add esp,0x4

        popad
        
        // original
        mov cx,word ptr[edi+esi+0x2]
        jmp u0x47E084
    }
}

unsigned u0x4B8766 = 0x4B8766;
void __declspec(naked) naked_0x4B8755()
{
    __asm
    {
        push eax // step
        call get_weapon_step
        add esp,0x4

        jmp u0x4B8766
    }
}

unsigned u0x41F9ED = 0x41F9ED;
unsigned u0x41F9C9 = 0x41F9C9;
void __declspec(naked) naked_0x41F9C0()
{
    __asm
    {
        // character->wings
        cmp dword ptr[esi+0x434],0x0
        jne _0x41F9ED

        // original
        mov edx,[esi+0x10]
        fld dword ptr ds:[0x748160]
        jmp u0x41F9C9

        _0x41F9ED:
        jmp u0x41F9ED
    }
}

unsigned u0x41BB40 = 0x41BB40;
unsigned u0x4110F0 = 0x4110F0;
unsigned u0x41F5E6 = 0x41F5E6;
unsigned u0x41E2CD = 0x41E2CD;
void __declspec(naked) naked_0x41E2BB()
{
    __asm
    {
        // original
        mov ecx,esi
        call u0x41BB40
        test eax,eax
        jne original
        // continue
        jmp u0x41E2CD

        original:
        mov ecx,esi
        call u0x4110F0
        // exit
        jmp u0x41F5E6
    }
}

void hook::gui()
{
    // chat color bug workaround

    // balloon
    util::detour((void*)0x57C565, naked_0x57C565, 5);
    // message box
    util::detour((void*)0x47E07F, naked_0x47E07F, 5);
    // weapon enchant bug
    util::detour((void*)0x4B8755, naked_0x4B8755, 5);
    // dungeon wings shadow workaround
    util::detour((void*)0x41F9C0, naked_0x41F9C0, 9);
    // evolution bug
    util::detour((void*)0x41E2BB, naked_0x41E2BB, 7);

    // remove ep6 vehicle section (auction board)
    util::write_memory((void*)0x463FE0, 0x07, 1);
    // speed recreation
    util::write_memory((void*)0x4C4D2F, 0x02, 1);
    // speed enhance
    util::write_memory((void*)0x501600, 0x02, 1);
    util::write_memory((void*)0x501602, 0x02, 1);
    util::write_memory((void*)0x501631, 0x02, 1);
    util::write_memory((void*)0x501633, 0x02, 1);
    util::write_memory((void*)0x501644, 0x03, 1);
    util::write_memory((void*)0x50164D, 0x03, 1);
    // costume lag workaround
    util::write_memory((void*)0x56F38D, 0x75, 1);
    util::write_memory((void*)0x583DED, 0x75, 1);
    // pet/wing lag workaround
    util::write_memory((void*)0x5881EE, 0x85, 1);
}
