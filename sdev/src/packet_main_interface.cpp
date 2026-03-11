#include <algorithm>
#include <map>
#include <util/util.h>
#include <shaiya/include/network/TP_MAIN.h>
#include <shaiya/include/network/game/incoming/0200.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include "include/main.h"
#include "include/shaiya/BattlefieldMoveInfo.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/RevengeMark.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

/// <summary>
/// Adds battlefield move support (EP7).
/// </summary>
void handler_0x233(CUser* user, GameMovePvPZoneIncoming_EP7* incoming)
{
    if (user->status == UserStatus::Death)
        return;

    if (user->debuffTypeDetail)
        return;

    if (user->logoutTime)
        return;

    auto it = std::ranges::find_if(g_pvpMoveData, BattlefieldLvInRangeF(user->level));
    if (it == g_pvpMoveData.end())
        return;

    auto index = std::clamp(static_cast<int>(user->family), 0, 3);
    auto mapId = it->mapPos[index].mapId;
    if (user->mapId == mapId)
        return;

    CUser::CancelActionExc(user);
    MyShop::Ended(&user->myShop);

    auto x = it->mapPos[index].x;
    auto y = it->mapPos[index].y;
    auto z = it->mapPos[index].z;
    UserHelper::SetMovePosition(user, MoveType::Portal, 0, mapId, x, y, z);
}

/// <summary>
/// Adds support for additional 0x200 packets.
/// </summary>
void handler_0x200(CUser* user, TP_MAIN* packet)
{
    auto incoming = SHAIYA_TP_MAIN_CAST(packet);
    switch (incoming->opcode)
    {
    case 0x233:
        handler_0x233(user, incoming);
        break;
    default:
        SConnection::Close(user, 9, 0);
        break;
    }
}

/// <summary>
/// Adds revenge mark support.
/// </summary>
void hook_0x4656F7(CUser* target, CUser* killer)
{
    if (g_revengeMarks.contains(killer->id))
    {
        if (g_revengeMarks[killer->id].erase(target->id))
        {
            RevengeMark::SendRevengeSuccess(killer, target->id);
        }
    }

    if (g_revengeMarks.contains(target->id))
    {
        if (g_revengeMarks[target->id].contains(killer->id))
        {
            auto& killCount = g_revengeMarks[target->id][killer->id];
            if (killCount < 999)
            {
                ++killCount;
                RevengeMark::SendKillCount(target, killer->id, killCount);
            }
        }
        else
        {
            g_revengeMarks[target->id].insert({ killer->id, 1 });
            RevengeMark::SendKillCount(target, killer->id, 1);
        }
    }
    else
    {
        g_revengeMarks.insert({ target->id, {{ killer->id, 1 }} });
        RevengeMark::SendKillCount(target, killer->id, 1);
    }
}

unsigned u0x477999 = 0x477999;
void __declspec(naked) naked_0x47798E()
{
    __asm
    {
        pushad

        push ebx // packet
        push ebp // user
        call handler_0x200
        add esp,0x8

        popad

        jmp u0x477999
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
        call hook_0x4656F7
        add esp,0x8

        popad

        // original
        mov ebx,[esi+0x17F4]
        jmp u0x4656FD
    }
}

void hook::packet_main_interface()
{
    // CUser::PacketMainInterface (default case)
    util::detour((void*)0x47798E, naked_0x47798E, 6);
    // CUser::Death
    util::detour((void*)0x4656F7, naked_0x4656F7, 6);
}
