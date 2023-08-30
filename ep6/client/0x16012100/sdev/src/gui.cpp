#pragma unmanaged
#include <array>

#include <include/util.h>
#include <include/main.h>

const std::array<std::uint16_t, 21> weapon_step
{
    0, 7, 14, 21, 31, 41, 51, 64, 77, 90, 106, 122, 138, 157, 176, 195, 217, 239, 261, 286, 311
};

int get_weapon_step(std::uint8_t step)
{
    if (step >= weapon_step.size())
        return 0;

    return weapon_step[step];
}

unsigned u0x4B8690 = 0x4B8690;
void __declspec(naked) naked_0x4B867F()
{
    __asm
    {
        push eax // step
        call get_weapon_step
        add esp,0x4

        jmp u0x4B8690
    }
}

unsigned u0x594AF1 = 0x594AF1;
void __declspec(naked) naked_0x594AEB()
{
    __asm
    {
        mov esi,[esp+0x4]
        mov edx,[esp+0x8]
        mov ecx,[esp+0xC]
        // original
        mov dword ptr ds:[0x914478],esi
        jmp u0x594AF1
    }
}

unsigned u0x59FFAF = 0x59FFAF;
void __declspec(naked) naked_0x59FF96()
{
    __asm
    {
        // CCharacter*
        cmp esi,dword ptr ds:[0x904AA0]
        jne wrong_appearance

        // sex, size, face, hair
        mov byte ptr ds:[0x914474],al
        mov byte ptr ds:[0x913472],cl
        mov byte ptr ds:[0x913471],dl
        mov byte ptr ds:[0x913470],bl

        wrong_appearance:
        mov ecx,esi
        jmp u0x59FFAF
    }
}

void hook::gui()
{
    // weapon enchant bug
    util::detour((void*)0x4B867F, naked_0x4B867F, 5);
    // hp/mp/sp bug
    util::detour((void*)0x594AEB, naked_0x594AEB, 6);
    // appearance/sex change bug
    util::detour((void*)0x59FF96, naked_0x59FF96, 6);
    // move when using cash shop
    std::array<std::uint8_t, 2> a00{ 0xEB, 0x2A };
    std::memcpy((void*)0x4453BD, &a00, 2);
    // costume lag workaround
    std::array<std::uint8_t, 2> a01{ 0x75, 0x2F };
    std::memcpy((void*)0x56F77D, &a01, 2);
    std::array<std::uint8_t, 2> a02{ 0x75, 0x1E };
    std::memcpy((void*)0x58437D, &a02, 2);
    // pet/wing lag workaround
    std::array<std::uint8_t, 6> a03{ 0x0F, 0x85, 0x84, 0x00, 0x00, 0x00 };
    std::memcpy((void*)0x58877D, &a03, 6);
    // remove ep6 vehicles (auction board)
    std::array<std::uint8_t, 1> a04{ 0x07 };
    std::memcpy((void*)0x463D10, &a04, 1);

    // 0x2602 EP5 packet format

    std::array<std::uint8_t, 3> a05{ 0x33, 0xD2, 0x90 };
    std::array<std::uint8_t, 3> a06{ 0x33, 0xC0, 0x90 };
    // ignore and null the dates
    util::write_memory((void*)0x5A463C, &a05, 3);
    util::write_memory((void*)0x5A4645, &a06, 3);

    std::uint8_t item_def_size = 5;
    // overwrite 13 with 5
    util::write_memory((void*)0x5E9891, &item_def_size, 1);
    util::write_memory((void*)0x5A4676, &item_def_size, 1);
}
