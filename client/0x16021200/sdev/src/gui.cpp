#include <array>

#include <include/util.h>
#include <include/main.h>

void hook::gui()
{
    // move when using cash shop
    std::array<std::uint8_t, 2> a00{ 0xEB, 0x2A };
    util::write_memory((void*)0x44565D, &a00, 2);
    // remove ep6 vehicles (auction board)
    std::array<std::uint8_t, 1> a01{ 0x07 };
    util::write_memory((void*)0x463FE0, &a01, 1);
}
