#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/RevengeMark.h"
using namespace shaiya;

namespace packet_main_interface
{
    void send_revenge_mark(CUser* target, CUser* killer)
    {
        if (auto outer = g_revengeMarks.find(killer->id); outer != g_revengeMarks.end())
        {
            if (auto inner = outer->second.find(target->id); inner != outer->second.end())
            {
                outer->second.erase(inner);
                RevengeMark::send(killer, target->id, 0);
            }
        }

        if (auto outer = g_revengeMarks.find(target->id); outer != g_revengeMarks.end())
        {
            if (auto inner = outer->second.find(killer->id); inner != outer->second.end())
            {
                if (inner->second < RevengeMarkConstants::MaxKillCount)
                {
                    ++inner->second;
                    RevengeMark::send(target, inner->first, inner->second);
                }
            }
            else
            {
                outer->second.insert({ killer->id, 1 });
                RevengeMark::send(target, killer->id, 1);
            }
        }
        else
        {
            g_revengeMarks.insert({ target->id, {{ killer->id, 1 }} });
            RevengeMark::send(target, killer->id, 1);
        }
    }
}

unsigned u0x4656FD = 0x4656FD;
void __declspec(naked) naked_0x4656F7()
{
    __asm
    {
        pushad

        push esi // killer
        push edi // target
        call packet_main_interface::send_revenge_mark
        add esp,0x8

        popad

        // original
        mov ebx,[esi+0x17F4]
        jmp u0x4656FD
    }
}

void hook::packet_main_interface()
{
    // CUser::Death
    util::detour((void*)0x4656F7, naked_0x4656F7, 6);
}
