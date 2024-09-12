#include <map>
#include <vector>
#include <shaiya/include/SConnection.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/RevengeMark.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
using namespace shaiya;

namespace revenge_mark
{
    void send(CUser* target, CUser* killer)
    {
        // see game.004E77F4
        constexpr int max_kill_count = 999;

        auto killerId = killer->object.id;
        auto targetId = target->object.id;

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
                SConnection::Send(&killer->connection, &outgoing, sizeof(RevengeMarkOutgoing));
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
                    SConnection::Send(&target->connection, &outgoing, sizeof(RevengeMarkOutgoing));
                }
            }
            else
            {
                it->second.push_back({ killerId, 1 });

                RevengeMarkOutgoing outgoing(killerId, 1);
                SConnection::Send(&target->connection, &outgoing, sizeof(RevengeMarkOutgoing));
            }
        }
        else
        {
            g_revengeMark.insert({ targetId, {{ killerId, 1 }} });

            RevengeMarkOutgoing outgoing(killerId, 1);
            SConnection::Send(&target->connection, &outgoing, sizeof(RevengeMarkOutgoing));
        }
    }
}

unsigned u0x4ED210 = 0x4ED210;
unsigned u0x467D93 = 0x467D93;
void __declspec(naked) naked_0x467D8E()
{
    __asm
    {
        // original
        call u0x4ED210

        pushad

        push edi // killer
        push ebp // target
        call revenge_mark::send
        add esp,0x8

        popad

        // original
        jmp u0x467D93
    }
}

void hook::revenge_mark()
{
    // CUser::KillPCTo
    util::detour((void*)0x467D8E, naked_0x467D8E, 5);
}
