#pragma unmanaged
#include <array>

#include <include/util.h>
#include <include/main.h>


unsigned u0x5890BF = 0x5890BF;
void __declspec(naked) naked_0x5890A6()
{
    __asm
    {
        // CCharacter*
        cmp esi,dword ptr ds:[0x8E6654]
        jne wrong_appearance

        // sex, size, face, hair
        mov byte ptr ds:[0x8F5FB4],al
        mov byte ptr ds:[0x8F4FB2],cl
        mov byte ptr ds:[0x8F4FB1],dl
        mov byte ptr ds:[0x8F4FB0],bl

        wrong_appearance:
        mov ecx,esi
        jmp u0x5890BF
    }
}

unsigned u0x57CE9E = 0x57CE9E;
void __declspec(naked) naked_0x57CE98()
{
    __asm
    {
        // original
        mov dword ptr[esi+0x1C4],eax

        xor eax,eax

        // character->petType
        cmp byte ptr[esi+0x1B6],0x0
        jne dual_layer_clothes

        // character->pet
        mov [esi+0x42C],eax

        dual_layer_clothes:
        // character->clothesType
        cmp byte ptr[esi+0x1B7],0x0
        jne _0x57CE9E

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

        _0x57CE9E:
        jmp u0x57CE9E
    }
}

unsigned u0x56624A = 0x56624A;
void __declspec(naked) naked_0x566245()
{
    __asm
    {
        // write "120"
        mov byte ptr[esi+edi+0x2],0x31
        mov byte ptr[esi+edi+0x3],0x32
        mov byte ptr[esi+edi+0x4],0x30

        // original
        mov dx,word ptr[esi+edi+0x2]
        jmp u0x56624A
    }
}

unsigned u0x4758D4 = 0x4758D4;
void __declspec(naked) naked_0x4758CF()
{
    __asm
    {
        // write "120"
        mov byte ptr[edi+esi+0x2],0x31
        mov byte ptr[edi+esi+0x3],0x32
        mov byte ptr[edi+esi+0x4],0x30
        
        // original
        mov cx,word ptr[edi+esi+0x2]
        jmp u0x4758D4
    }
}

void hook::gui()
{
    // disguise bug
    util::detour((void*)0x57CE98, naked_0x57CE98, 6);
    // appearance/sex change bug
    util::detour((void*)0x5890A6, naked_0x5890A6, 6);
    
    // chat color bug workaround
    
    // balloon
    util::detour((void*)0x566245, naked_0x566245, 5);
    // message box
    util::detour((void*)0x4758CF, naked_0x4758CF, 5);

    // move when using cash shop
    std::array<std::uint8_t, 2> a00{ 0xEB, 0x2A };
    std::memcpy((void*)0x4481ED, &a00, 2);
    // costume lag workaround
    std::array<std::uint8_t, 2> a01{ 0x75, 0x2F };
    std::memcpy((void*)0x55952D, &a01, 2);
    std::array<std::uint8_t, 2> a02{ 0x75, 0x1E };
    std::memcpy((void*)0x56E08D, &a02, 2);
    // pet lag workaround
    std::array<std::uint8_t, 6> a03{ 0x0F, 0x85, 0x84, 0x00, 0x00, 0x00 };
    std::memcpy((void*)0x57236D, &a03, 6);
}
