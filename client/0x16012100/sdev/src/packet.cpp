#include <include/util.h>
#include <include/main.h>
#include <include/shaiya/include/CCharacter.h>
#include <include/shaiya/include/CNetwork.h>
using namespace shaiya;

namespace packet
{
    void process_incoming(std::uint16_t opcode, Packet packet)
    {
        switch (opcode)
        {
        case 0xFFFF:
            break;
        default:
            break;
        }
    }

    void remove_disguise(CCharacter* user)
    {
        if (!user->petType)
            user->pet = nullptr;

        if (!user->clothesType)
        {
            user->enableClothes = 0;
            user->clothes.fill(-1);
        }

        if (!user->wingsType)
            user->wings = nullptr;
    }
}

unsigned u0x5F3AAC = 0x5F3AAC;
void __declspec(naked) naked_0x5F3AA6()
{
    __asm
    {
        pushad

        movzx edx,word ptr[esp+0x50]
        lea eax,[esp+0x52]

        push eax // packet
        push edx // opcode
        call packet::process_incoming
        add esp,0x8

        popad

        // original
        mov ecx,dword ptr ds:[0x22FA708]
        jmp u0x5F3AAC
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

        pushad

        push esi // user
        call packet::remove_disguise
        add esp,0x4

        popad

        jmp u0x593BEE
    }
}

void hook::packet()
{
    // recv default case
    util::detour((void*)0x5F3AA6, naked_0x5F3AA6, 6);
    // disguise bug
    util::detour((void*)0x593BE8, naked_0x593BE8, 6);
    // appearance/sex change bug
    util::detour((void*)0x59FF96, naked_0x59FF96, 6);
}
