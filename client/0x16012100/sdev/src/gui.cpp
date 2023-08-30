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

unsigned u0x593BEE = 0x593BEE;
void __declspec(naked) naked_0x593BE8()
{
    __asm
    {
        // original
        mov byte ptr[esi+0x1C9],al

        xor eax,eax

        // character->petType
        cmp byte ptr[esi+0x1C7],0x0
        jne dual_layer_clothes

        // character->pet
        mov [esi+0x430],eax

        dual_layer_clothes:
        cmp byte ptr[esi+0x1C8],0x0
        jne wings

        // character->enableClothes
        mov [esi+0xAC],eax
        mov eax,-0x1

        // character->clothes
        mov [esi+0xB0],eax
        mov [esi+0xB4],eax
        mov [esi+0xB8],eax
        mov [esi+0xBC],eax
        mov [esi+0xC0],eax
        mov [esi+0xC4],eax
        xor eax,eax

        wings:
        cmp byte ptr[esi+0x1C9],0x0
        jne _0x593BEE

        // character->wings
        mov [esi+0x434],eax

        _0x593BEE:
        jmp u0x593BEE
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

void hook::gui()
{
    // weapon enchant bug
    util::detour((void*)0x4B867F, naked_0x4B867F, 5);
    // disguise bug
    util::detour((void*)0x593BE8, naked_0x593BE8, 6);
    // appearance/sex change bug
    util::detour((void*)0x59FF96, naked_0x59FF96, 6);
    
    // chat color bug workaround
    
    // balloon
    util::detour((void*)0x57C955, naked_0x57C955, 5);
    // message box
    util::detour((void*)0x47DD9F, naked_0x47DD9F, 5);

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
}
