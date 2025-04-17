#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include <shaiya/include/common/DateTime.h>
#include <shaiya/include/network/dbAgent/incoming/0E00.h>
#include <shaiya/include/network/dbAgent/outgoing/0E00.h>
#include <shaiya/include/network/game/outgoing/2600.h>
#include <shaiya/include/network/game/PointItemUnit.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/NetworkHelper.h"
using namespace shaiya;

namespace packet_shop
{
    /// <summary>
    /// Sends packet 0xE06 to the dbAgent service.
    /// </summary>
    /// <param name="user"></param>
    void send_dbAgent_0xE06(CUser* user)
    {
        DBAgentPointReloadIncoming outgoing{};
        outgoing.billingId = user->billingId;
        NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentPointReloadIncoming));
    }

    /// <summary>
    /// Sends packets 0xE0A and 0xE06 to the dbAgent service.
    /// </summary>
    /// <param name="user"></param>
    void send_dbAgent_0xE0A(CUser* user)
    {
        DBAgentPointUpdateIncoming outgoing{};
        outgoing.billingId = user->billingId;
        NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentPointUpdateIncoming));
        send_dbAgent_0xE06(user);
        InterlockedExchange(&user->pointsLock, 0);
    }

    /// <summary>
    /// Sends packet 0xE03 to the dbAgent service.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="targetName"></param>
    /// <param name="productCode"></param>
    /// <param name="purchasePoints"></param>
    void send_dbAgent_0xE03(CUser* user, const char* targetName, const char* productCode, uint purchasePoints)
    {
        SYSTEMTIME lt{};
        GetLocalTime(&lt);

        DBAgentPointItemGiftSendIncoming outgoing{};
        outgoing.billingId = user->billingId;
        std::memcpy(outgoing.targetName.data(), targetName, outgoing.targetName.size());
        std::memcpy(outgoing.productCode.data(), productCode, outgoing.productCode.size());
        outgoing.purchasePoints = purchasePoints;
        outgoing.purchaseDate = DateTime::encode(lt);
        outgoing.purchaseNumber = InterlockedIncrement(reinterpret_cast<volatile unsigned*>(0x5879B0));
        NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentPointItemGiftSendIncoming));
        InterlockedExchange(&user->pointsLock, 0);
    }

    /// <summary>
    /// Handles incoming 0xE06 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0xE06(CUser* user, DBAgentPointReloadOutgoing* incoming)
    {
        if (InterlockedCompareExchange(&user->pointsLock, 0, 0))
            return;

        InterlockedExchange(&user->points, incoming->points);

        GamePointOutgoing outgoing{};
        outgoing.points = user->points;
        NetworkHelper::Send(user, &outgoing, sizeof(GamePointOutgoing));
    }

    /// <summary>
    /// Sends packet 0x2602 (6.4) to the user. The item dates will be zero.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="packet"></param>
    void send_0x2602(CUser* user, GamePointBuyOutgoing<PointItemUnit_EP5>* packet)
    {
        GamePointBuyOutgoing<PointItemUnit_EP6_4> outgoing{};
        outgoing.result = packet->result;
        outgoing.remainingPoints = packet->remainingPoints;
        outgoing.log.productCode = packet->log.productCode;
        outgoing.log.purchaseDate = packet->log.purchaseDate;
        outgoing.log.purchasePoints = packet->log.purchasePoints;
        outgoing.itemCount = packet->itemCount;

        for (int i = 0; i < outgoing.itemCount; ++i)
        {
            PointItemUnit_EP6_4 item2602{};
            item2602.bag = packet->itemList[i].bag;
            item2602.slot = packet->itemList[i].slot;
            item2602.type = packet->itemList[i].type;
            item2602.typeId = packet->itemList[i].typeId;
            item2602.count = packet->itemList[i].count;
            outgoing.itemList[i] = item2602;
        }

        int length = outgoing.baseLength + (outgoing.itemCount * sizeof(PointItemUnit_EP6_4));
        NetworkHelper::Send(user, &outgoing, length);
    }
}

unsigned u0x4ED2D0 = 0x4ED2D0;
unsigned u0x47A4A9 = 0x47A4A9;
void __declspec(naked) naked_0x47A4A4()
{
    __asm
    {
        // original
        call u0x4ED2D0

        pushad

        push esi // user
        call packet_shop::send_dbAgent_0xE06
        add esp,0x4

        popad

        jmp u0x47A4A9
    }
}

unsigned u0x488D5F = 0x488D5F;
void __declspec(naked) naked_0x48876F()
{
    __asm
    {
        pushad

        push edi // user
        call packet_shop::send_dbAgent_0xE0A
        add esp,0x4

        popad

        // original
        jmp u0x488D5F
    }
}

void __declspec(naked) naked_0x488A80()
{
    __asm
    {
        pushad

        mov eax,[esp+0x174]
        push eax // purchasePoints
        lea eax,[esp+0x14E]
        push eax // productCode
        lea eax,[esp+0x167]
        push eax // targetName
        push edi // user
        call packet_shop::send_dbAgent_0xE03
        add esp,0x10

        popad

        // original
        jmp u0x488D5F
    }
}

unsigned u0x47D52A = 0x47D52A;
void __declspec(naked) naked_0x47D525()
{
    __asm
    {
        cmp word ptr[esi],0xE06
        jne exit_switch

        // case 0xE06

        pushad

        push esi // packet
        push ebx // user
        call packet_shop::handler_0xE06
        add esp,0x8

        popad

        exit_switch:
        mov al,0x1
        pop edi
        pop ebp
        pop ebx

        jmp u0x47D52A
    }
}

unsigned u0x488709 = 0x488709;
void __declspec(naked) naked_0x4886E0()
{
    __asm
    {
        // purchaseDate
        mov [esp+0x188],esi
        // purchasePoints
        mov [esp+0x18C],edx
        // itemCount
        mov byte ptr[esp+0x190],bl

        pushad

        lea ecx,[esp+0x18C]

        push ecx // packet
        push edi // user
        call packet_shop::send_0x2602
        add esp,0x8

        popad

        jmp u0x488709
    }
}

void hook::packet_shop()
{
    // CUser::PacketCharacter case 0x104
    util::detour((void*)0x47A4A4, naked_0x47A4A4, 5);
    // CUser::PacketShop case 0x2602
    util::detour((void*)0x48876F, naked_0x48876F, 5);
    // CUser::PacketShop case 0x2603
    util::detour((void*)0x488A80, naked_0x488A80, 5);
    // CUser::PacketUserDBPoint case 0xE06
    util::detour((void*)0x47D525, naked_0x47D525, 5);
    // CUser::PacketShop case 0x2602
    util::detour((void*)0x4886E0, naked_0x4886E0, 5);

    // CClientToMgr::OnRecv case 0x105
    util::write_memory((void*)0x4069CF, 0x90, 5);

    // g_nPayLetterEnable
    int enabled = true;
    util::write_memory((void*)0x58799C, &enabled, 4);
}
