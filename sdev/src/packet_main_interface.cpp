#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/RevengeMark.h"
using namespace shaiya;

namespace packet_main_interface
{
    void send_revenge_mark(CUser* target, CUser* killer)
    {
        auto killerId = killer->id;
        auto targetId = target->id;

        if (auto it = g_revengeMarks.find(killerId); it != g_revengeMarks.end())
        {
            if (auto revengeMark = std::find_if(
                it->second.begin(), it->second.end(), [&targetId](const auto& revengeMark) {
                    return revengeMark.charId == targetId;
                }
            ); revengeMark != it->second.end())
            {
                it->second.erase(revengeMark);
                RevengeMark::send(killer, targetId, 0);
            }
        }

        if (auto it = g_revengeMarks.find(targetId); it != g_revengeMarks.end())
        {
            if (auto revengeMark = std::find_if(
                it->second.begin(), it->second.end(), [&killerId](const auto& revengeMark) {
                    return revengeMark.charId == killerId;
                }
            ); revengeMark != it->second.end())
            {
                if (revengeMark->killCount < RevengeMark::maxKillCount)
                {
                    ++revengeMark->killCount;
                    RevengeMark::send(target, revengeMark->charId, revengeMark->killCount);
                }
            }
            else
            {
                it->second.push_back({ killerId, 1 });
                RevengeMark::send(target, killerId, 1);
            }
        }
        else
        {
            g_revengeMarks.insert({ targetId, {{ killerId, 1 }} });
            RevengeMark::send(target, killerId, 1);
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
