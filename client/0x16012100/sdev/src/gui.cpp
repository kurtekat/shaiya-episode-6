#include <array>
#include <format>
#include <string>

#include <include/util.h>
#include <include/main.h>

void format_chat_color_size(char* text)
{
    auto len = std::strlen(&text[8]);
    auto str = std::format("{:03}", len);
    std::memcpy(&text[2], str.data(), 3);
}

unsigned u0x57C95A = 0x57C95A;
void __declspec(naked) naked_0x57C955()
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
        jmp u0x57C95A
    }
}

unsigned u0x47DDA4 = 0x47DDA4;
void __declspec(naked) naked_0x47DD9F()
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
        jmp u0x47DDA4
    }
}

void hook::gui()
{
    // chat color bug workaround

    // balloon
    util::detour((void*)0x57C955, naked_0x57C955, 5);
    // message box
    util::detour((void*)0x47DD9F, naked_0x47DD9F, 5);

    // move when using cash shop
    std::array<std::uint8_t, 2> a00{ 0xEB, 0x2A };
    util::write_memory((void*)0x4453BD, &a00, 2);
    // remove ep6 vehicles (auction board)
    std::array<std::uint8_t, 1> a01{ 0x07 };
    util::write_memory((void*)0x463D10, &a01, 1);
}
