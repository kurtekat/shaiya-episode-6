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

unsigned u0x59F8AF = 0x59F8AF;
void __declspec(naked) naked_0x59F896()
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
        jmp u0x59F8AF
    }
}

unsigned u0x5933FE = 0x5933FE;
void __declspec(naked) naked_0x5933F8()
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
        jne _0x5933FE

        // character->wings
        mov [esi+0x434],eax

        _0x5933FE:
        jmp u0x5933FE
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

void hook::gui()
{
    // weapon enchant bug
    util::detour((void*)0x4B8755, naked_0x4B8755, 5);
    // disguise bug
    util::detour((void*)0x5933F8, naked_0x5933F8, 6);
    // appearance/sex change bug
    util::detour((void*)0x59F896, naked_0x59F896, 6);

    // chat color bug workaround
    
    // balloon
    util::detour((void*)0x57C565, naked_0x57C565, 5);
    // message box
    util::detour((void*)0x47E07F, naked_0x47E07F, 5);

    // move when using cash shop
    std::array<std::uint8_t, 2> a00{ 0xEB, 0x2A };
    std::memcpy((void*)0x44565D, &a00, 2);
    // costume lag workaround
    std::array<std::uint8_t, 2> a01{ 0x75, 0x2F };
    std::memcpy((void*)0x56F38D, &a01, 2);
    std::array<std::uint8_t, 2> a02{ 0x75, 0x1E };
    std::memcpy((void*)0x583DED, &a02, 2);
    // pet/wing lag workaround
    std::array<std::uint8_t, 6> a03{ 0x0F, 0x85, 0x84, 0x00, 0x00, 0x00 };
    std::memcpy((void*)0x5881ED, &a03, 6);
    // remove ep6 vehicles (auction board)
    std::array<std::uint8_t, 1> a04{ 0x07 };
    std::memcpy((void*)0x463FE0, &a04, 1);
}
