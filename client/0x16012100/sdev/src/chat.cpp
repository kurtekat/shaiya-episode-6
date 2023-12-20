#include <include/util.h>
#include <include/main.h>

unsigned u0x57C7CA = 0x57C7CA;
void __declspec(naked) naked_0x57C7C5()
{
    __asm
    {
        // write "120"
        mov byte ptr[esi+edi+0x2],0x31
        mov byte ptr[esi+edi+0x3],0x32
        mov byte ptr[esi+edi+0x4],0x30
        // note: misaligns the name :P

        // original
        mov eax,esi
        lea edx,[eax+0x1]
        jmp u0x57C7CA
    }
}

unsigned u0x57C95A = 0x57C95A;
void __declspec(naked) naked_0x57C955()
{
    __asm
    {
        // write "120"
        mov byte ptr[esi+edi+0x2],0x31
        mov byte ptr[esi+edi+0x3],0x32
        mov byte ptr[esi+edi+0x4],0x30

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
        // write "120"
        mov byte ptr[edi+esi+0x2],0x31
        mov byte ptr[edi+esi+0x3],0x32
        mov byte ptr[edi+esi+0x4],0x30
        
        // original
        mov cx,word ptr[edi+esi+0x2]
        jmp u0x47DDA4
    }
}

void hook::chat()
{
    // chat color bug workaround

    // names
    util::detour((void*)0x57C7C5, naked_0x57C7C5, 5);
    // balloon
    util::detour((void*)0x57C955, naked_0x57C955, 5);
    // message box
    util::detour((void*)0x47DD9F, naked_0x47DD9F, 5);
}
