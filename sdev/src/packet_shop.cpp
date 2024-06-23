#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/dbAgent/incoming/0E00.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/2600.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemDuration.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

namespace packet_shop
{
    void send_reload_point(CUser* user)
    {
        DBAgentReloadPointIncoming packet(user->userId);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentReloadPointIncoming));
    }

    void reload_point_handler(CUser* user, uint32_t points)
    {
        if (InterlockedCompareExchange(&user->disableShop, 0, 0))
            return;

        InterlockedExchange(&user->points, points);

        PointOutgoing outgoing(user->points);
        SConnection::Send(&user->connection, &outgoing, sizeof(PointOutgoing));
    }

    void send_purchase(CUser* user, Packet buffer)
    {
        PointPurchaseItemOutgoing outgoing{};
        outgoing.opcode = util::deserialize<uint16_t>(buffer, 0);
        outgoing.result = util::deserialize<PointPurchaseItemResult>(buffer, 2);
        outgoing.points = util::deserialize<uint32_t>(buffer, 3);
        std::memcpy(&outgoing.productCode, &buffer[7], outgoing.productCode.size());
        outgoing.purchaseDate = util::deserialize<unsigned long>(buffer, 28);
        outgoing.itemPrice = util::deserialize<uint32_t>(buffer, 32);
        outgoing.itemCount = util::deserialize<uint8_t>(buffer, 36);

        int offset = 0;
        for (int i = 0; i < outgoing.itemCount; ++i)
        {
            Item2602 item2602{};
            item2602.bag = util::deserialize<uint8_t>(buffer, 37 + offset);
            item2602.slot = util::deserialize<uint8_t>(buffer, 38 + offset);
            item2602.type = util::deserialize<uint8_t>(buffer, 39 + offset);
            item2602.typeId = util::deserialize<uint8_t>(buffer, 40 + offset);
            item2602.count = util::deserialize<uint8_t>(buffer, 41 + offset);

#ifdef SHAIYA_EP6_4_PT
            auto itemInfo = CGameData::GetItemInfo(item2602.type, item2602.typeId);
            if (itemInfo && itemInfo->duration)
            {
                auto now = ServerTime::Now();
                item2602.toDate = ServerTime::Add(now, itemInfo->duration);
                item2602.fromDate = item2602.toDate ? now : 0;
            }
#endif

            outgoing.itemList[i] = item2602;
            offset += 5;
        }

        int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item2602));
        SConnection::Send(&user->connection, &outgoing, length);
    }

    void send_purchase2(CUser* user)
    {
        DBAgentSaveBuyPointItemIncoming packet(user->userId);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentSaveBuyPointItemIncoming));

        send_reload_point(user);

        InterlockedExchange(&user->disableShop, 0);
    }

    void send_purchase3(CUser* user, const char* targetName, const char* productCode, uint32_t itemPrice)
    {
        auto purchaseDate = ServerTime::Now();
        auto purchaseNumber = InterlockedIncrement(reinterpret_cast<volatile unsigned*>(0x5879B0));

        DBAgentSaveGiftPointItemIncoming packet(user->userId, targetName, productCode, itemPrice, purchaseDate, purchaseNumber);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentSaveGiftPointItemIncoming));

        InterlockedExchange(&user->disableShop, 0);
    }

    void send_item_duration(CUser* user, CItem* item, Packet buffer)
    {
        if (!item->itemInfo->duration)
            return;

        auto expireTime = ServerTime::Add(item->makeTime, item->itemInfo->duration);
        if (!expireTime)
            return;

        auto bag = util::deserialize<uint8_t>(buffer, 3);
        auto slot = util::deserialize<uint8_t>(buffer, 4);

        ItemDurationOutgoing outgoing(bag, slot, item->makeTime, expireTime);
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemDurationOutgoing));
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

        mov eax,[esi+0x6]

        push eax // points
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

unsigned u0x467F60 = 0x467F60;
unsigned u0x488CCE = 0x488CCE;
void __declspec(naked) naked_0x488CC9()
{
    __asm
    {
        call u0x467F60

        pushad

        lea eax,[esp+0x40]

        push eax // packet
        push ebp // item
        push edi // user
        call packet_shop::send_item_duration
        add esp,0xC

        popad

        jmp u0x488CCE
    }
}

unsigned u0x464B5F = 0x464B5F;
void __declspec(naked) naked_0x464B5A()
{
    __asm
    {
        call u0x467F60

        pushad

        lea eax,[esp+0x30]

        push eax // packet
        push ebp // item
        push edi // user
        call packet_shop::send_item_duration
        add esp,0xC

        popad

        jmp u0x464B5F
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
    // CUser::PacketShop case 0x2607
    util::detour((void*)0x488CC9, naked_0x488CC9, 5);
    // CUser::PacketBilling
    util::detour((void*)0x464B5A, naked_0x464B5A, 5);
#endif
}
