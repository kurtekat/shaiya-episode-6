#include <array>

#include <include/util.h>
#include <include/main.h>

namespace item
{
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
}

unsigned u0x4B8766 = 0x4B8766;
void __declspec(naked) naked_0x4B8755()
{
    __asm
    {
        push eax // step
        call item::get_weapon_step
        add esp, 0x4

        jmp u0x4B8766
    }
}

void hook::item()
{
    // weapon enchant bug
    util::detour((void*)0x4B8755, naked_0x4B8755, 5);

    // costume lag workaround
    std::array<std::uint8_t, 2> a00{ 0x75, 0x2F };
    util::write_memory((void*)0x56F38D, &a00, 2);
    std::array<std::uint8_t, 2> a01{ 0x75, 0x1E };
    util::write_memory((void*)0x583DED, &a01, 2);
    // pet/wing lag workaround
    std::array<std::uint8_t, 6> a02{ 0x0F, 0x85, 0x84, 0x00, 0x00, 0x00 };
    util::write_memory((void*)0x5881ED, &a02, 6);
}
