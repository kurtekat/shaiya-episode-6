#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/ServerTime.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/network/dbAgent/incoming/0E00.h"
#include "include/shaiya/include/network/dbAgent/outgoing/0E00.h"
#include "include/shaiya/include/network/game/outgoing/2600.h"
using namespace shaiya;

namespace packet_shop
{
    /// <summary>
    /// Sends packet 0xE06 to the dbAgent service.
    /// </summary>
    /// <param name="user"></param>
    void send_reload_point(CUser* user)
    {
        DBAgentPointReloadIncoming packet(user->userId);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentPointReloadIncoming));
    }

    /// <summary>
    /// Handles incoming 0xE06 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void reload_point_handler(CUser* user, DBAgentPointReloadOutgoing* incoming)
    {
        if (InterlockedCompareExchange(&user->disableShop, 0, 0))
            return;

        InterlockedExchange(&user->points, incoming->points);

        PointBalanceOutgoing outgoing(user->points);
        Helpers::Send(user, &outgoing, sizeof(PointBalanceOutgoing));
    }

    /// <summary>
    /// Sends packet 0x2602 (6.4 PT) to the user. The item dates will be zero.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="packet"></param>
    void send_purchase(CUser* user, PointBuyItemOutgoing* packet)
    {
        PointBuyItemOutgoing2 outgoing{};
        outgoing.opcode = packet->opcode;
        outgoing.result = packet->result;
        outgoing.points = packet->points;
        outgoing.productCode = packet->productCode;
        outgoing.purchaseDate = packet->purchaseDate;
        outgoing.itemPrice = packet->itemPrice;
        outgoing.itemCount = packet->itemCount;

        if (outgoing.itemCount > outgoing.itemList.size())
            return;

        for (int i = 0; i < outgoing.itemCount; ++i)
        {
            Item2602v2 item2602{};
            item2602.bag = packet->itemList[i].bag;
            item2602.slot = packet->itemList[i].slot;
            item2602.type = packet->itemList[i].type;
            item2602.typeId = packet->itemList[i].typeId;
            item2602.count = packet->itemList[i].count;
            outgoing.itemList[i] = item2602;
        }

        int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item2602v2));
        Helpers::Send(user, &outgoing, length);
    }

    /// <summary>
    /// Sends packets 0xE06 and 0xE0A to the dbAgent service.
    /// </summary>
    /// <param name="user"></param>
    void send_purchase2(CUser* user)
    {
        DBAgentPointUpdateIncoming packet(user->userId);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentPointUpdateIncoming));

        send_reload_point(user);

        InterlockedExchange(&user->disableShop, 0);
    }

    /// <summary>
    /// Sends packet 0xE03 to the dbAgent service.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="targetName"></param>
    /// <param name="productCode"></param>
    /// <param name="itemPrice"></param>
    void send_purchase3(CUser* user, const char* targetName, const char* productCode, uint32_t itemPrice)
    {
        auto purchaseDate = ServerTime::now();
        auto purchaseNumber = InterlockedIncrement(reinterpret_cast<volatile unsigned*>(0x5879B0));

        DBAgentPointGiftItemIncoming packet(user->userId, targetName, productCode, itemPrice, purchaseDate, purchaseNumber);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentPointGiftItemIncoming));

        InterlockedExchange(&user->disableShop, 0);
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
        call packet_shop::send_reload_point
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
        call packet_shop::send_purchase2
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
        push eax // itemPrice
        lea eax,[esp+0x14E]
        push eax // productCode
        lea eax,[esp+0x167]
        push eax // targetName
        push edi // user
        call packet_shop::send_purchase3
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
        call packet_shop::reload_point_handler
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
        // price
        mov [esp+0x18C],edx
        // itemCount
        mov byte ptr[esp+0x190],bl

        pushad

        lea ecx,[esp+0x18C]

        push ecx // packet
        push edi // user
        call packet_shop::send_purchase
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

    // CClientToMgr::OnRecv case 0x105
    util::write_memory((void*)0x4069CF, 0x90, 5);

    // g_nPayLetterEnable
    int enabled = true;
    util::write_memory((void*)0x58799C, &enabled, 4);

#ifdef SHAIYA_EP6_4_PT
    // CUser::PacketShop case 0x2602
    util::detour((void*)0x4886E0, naked_0x4886E0, 5);
#endif
}
