#include <include/main.h>
#include <include/shaiya/static.h>
#include <include/shaiya/include/CCharacter.h>
#include <include/shaiya/include/CNetwork.h>
#include <include/shaiya/include/CWorldMgr.h>
#include <util/include/util.h>
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

    void revenge_message(CCharacter* killer, std::uint32_t killCount)
    {
        std::copy_n(killer->charName.begin(), killer->charName.size(), g_static->t.begin());
        g_static->v = killCount;

        // 509    "<t> killed  you <v> time(s)."
        typedef void(__cdecl* LPFN)(int, int, int);
        (*(LPFN)0x423150)(5, 509, 1);
    }
}

unsigned u0x5F3A41 = 0x5F3A41;
void __declspec(naked) naked_0x5F3A3B()
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
        mov ecx,dword ptr ds:[0x22FA2F0]
        jmp u0x5F3A41
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

        pushad

        push esi // user
        call packet::remove_disguise
        add esp,0x4

        popad

        jmp u0x5933FE
    }
}

unsigned u0x4EF315 = 0x4EF315;
void __declspec(naked) naked_0x4EF2F3()
{
    __asm
    {
        // original
        mov [eax+0x10],ebx

        pushad

        push ebx // killCount
        push edi // killer
        call packet::revenge_message
        add esp,0x8

        popad

        jmp u0x4EF315
    }
}

unsigned u0x593D15 = 0x593D15;
unsigned u0x593D73 = 0x593D73;
void __declspec(naked) naked_0x593D0F()
{
    __asm
    {
        // original
        push 0x0 // arg #16
        cmp al,0xB
        jne _0x593D73

        push 0x0 // arg #15
        jmp u0x593D15

        _0x593D73:
        jmp u0x593D73
    }
}

void hook::packet()
{
    // recv default case
    util::detour((void*)0x5F3A3B, naked_0x5F3A3B, 6);
    // disguise bug
    util::detour((void*)0x5933F8, naked_0x5933F8, 6);
    // appearance/sex change bug
    util::detour((void*)0x59F896, naked_0x59F896, 6);
    // revenge message 509
    util::detour((void*)0x4EF2F3, naked_0x4EF2F3, 5);
    // javelin attack bug (0x502 handler)
    util::detour((void*)0x593D0F, naked_0x593D0F, 6);

    // javelin attack bug

    // increase the stack offsets (see detour)
    util::write_memory((void*)0x593D46, 0x3C, 1);
    util::write_memory((void*)0x593D4D, 0x4C, 1);
    // remove argument #8
    util::write_memory((void*)0x593D4F, 0x90, 2);
}
