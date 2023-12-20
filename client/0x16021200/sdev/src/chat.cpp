#include <include/util.h>
#include <include/main.h>

unsigned u0x57C3DA = 0x57C3DA;
void __declspec(naked) naked_0x57C3D5()
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
        jmp u0x57C3DA
    }
}

unsigned u0x57C56A = 0x57C56A;
void __declspec(naked) naked_0x57C565()
{
    __asm
    {
        // write "120"
        mov byte ptr[esi+edi+0x2],0x31
        mov byte ptr[esi+edi+0x3],0x32
        mov byte ptr[esi+edi+0x4],0x30

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
        // write "120"
        mov byte ptr[edi+esi+0x2],0x31
        mov byte ptr[edi+esi+0x3],0x32
        mov byte ptr[edi+esi+0x4],0x30
        
        // original
        mov cx,word ptr[edi+esi+0x2]
        jmp u0x47E084
    }
}

void hook::chat()
{
    // chat color bug workaround

    // names
    util::detour((void*)0x57C3D5, naked_0x57C3D5, 5);
    // balloon
    util::detour((void*)0x57C565, naked_0x57C565, 5);
    // message box
    util::detour((void*)0x47E07F, naked_0x47E07F, 5);
}
