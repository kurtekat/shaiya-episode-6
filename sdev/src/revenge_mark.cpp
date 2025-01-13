#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/RevengeMark.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
using namespace shaiya;

namespace revenge_mark
{
    void send(CUser* target, CUser* killer)
    {
        constexpr int max_kill_count = 999;

        auto killerId = killer->connection.object.id;
        auto targetId = target->connection.object.id;

        if (auto it = g_revengeMark.find(killerId); it != g_revengeMark.end())
        {
            if (auto revenge = std::find_if(
                it->second.begin(), it->second.end(), [&targetId](const auto& revenge) {
                    return revenge.killerId == targetId;
                }
            ); revenge != it->second.end())
            {
                it->second.erase(revenge);

                RevengeMarkOutgoing outgoing(targetId, 0);
                NetworkHelper::Send(killer, &outgoing, sizeof(RevengeMarkOutgoing));
            }
        }

        if (auto it = g_revengeMark.find(targetId); it != g_revengeMark.end())
        {
            if (auto revenge = std::find_if(
                it->second.begin(), it->second.end(), [&killerId](const auto& revenge) {
                    return revenge.killerId == killerId;
                }
            ); revenge != it->second.end())
            {
                if (revenge->killCount < max_kill_count)
                {
                    ++revenge->killCount;

                    RevengeMarkOutgoing outgoing(revenge->killerId, revenge->killCount);
                    NetworkHelper::Send(target, &outgoing, sizeof(RevengeMarkOutgoing));
                }
            }
            else
            {
                it->second.push_back({ killerId, 1 });

                RevengeMarkOutgoing outgoing(killerId, 1);
                NetworkHelper::Send(target, &outgoing, sizeof(RevengeMarkOutgoing));
            }
        }
        else
        {
            g_revengeMark.insert({ targetId, {{ killerId, 1 }} });

            RevengeMarkOutgoing outgoing(killerId, 1);
            NetworkHelper::Send(target, &outgoing, sizeof(RevengeMarkOutgoing));
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
        call revenge_mark::send
        add esp,0x8

        popad

        // original
        mov ebx,[esi+0x17F4]
        jmp u0x4656FD
    }
}

void hook::revenge_mark()
{
    // CUser::Death
    util::detour((void*)0x4656F7, naked_0x4656F7, 6);
}
