#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <util/include/util.h>

unsigned u0x486320 = 0x486320;
void __declspec(naked) naked_0x486319()
{
    __asm
    {
        // search index
        movzx eax,byte ptr[ebp+0x5]
        cmp eax,0x13
        jge fix_index             // If index is >= 0x13 (19), jump to fix_index

        original_path:            // Label for the original execution path
        lea ecx,[ebp+0x7]
        jmp u0x486320

        fix_index:
        mov eax,0x12              // Set index to 0x12 (18)
        jmp original_path         // Jump to the original execution path
    }
}

void hook::packet_market()
{
    // CUser::PacketMarket case 0x1C01
    util::detour((void*)0x486319, naked_0x486319, 7);
}
