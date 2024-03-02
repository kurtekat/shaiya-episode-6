#include <array>
#include <chrono>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <strsafe.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/2600.h>
#include <include/shaiya/packets/dbAgent/0E00.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/SConnectionTBaseReconnect.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

namespace packet_shop
{
    void send_reload_point(CUser* user)
    {
        UserPointReloadPointIncoming packet{ 0xE06, user->userId };
        SConnectionTBaseReconnect::Send(g_pClientToDBAgent, &packet, sizeof(UserPointReloadPointIncoming));
    }

    void reload_point_handler(CUser* user, std::uint32_t points)
    {
        if (InterlockedCompareExchange(&user->disableShop, 0, 0))
            return;

        InterlockedExchange(&user->points, points);

        PointOutgoing packet{ 0x2605, user->points };
        SConnection::Send(&user->connection, &packet, sizeof(PointOutgoing));
    }

    void send_purchase(CUser* user, Packet buffer)
    {
        constexpr int packet_size_without_list = 37;

        PointPurchaseItemOutgoing packet{};
        packet.opcode = util::deserialize<std::uint16_t>(buffer, 0);
        packet.result = util::deserialize<PointPurchaseItemResult>(buffer, 2);
        packet.points = util::deserialize<std::uint32_t>(buffer, 3);
        std::memcpy(&packet.productCode, &buffer[7], packet.productCode.size());
        packet.purchaseDate = util::deserialize<std::uint32_t>(buffer, 28);
        packet.itemPrice = util::deserialize<std::uint32_t>(buffer, 32);
        packet.itemCount = util::deserialize<std::uint8_t>(buffer, 36);

        int offset = 0;
        for (int i = 0; i < packet.itemCount; ++i)
        {
            Item2602 item2602{};
            item2602.bag = util::deserialize<std::uint8_t>(buffer, 37 + offset);
            item2602.slot = util::deserialize<std::uint8_t>(buffer, 38 + offset);
            item2602.type = util::deserialize<std::uint8_t>(buffer, 39 + offset);
            item2602.typeId = util::deserialize<std::uint8_t>(buffer, 40 + offset);
            item2602.count = util::deserialize<std::uint8_t>(buffer, 41 + offset);
            packet.itemList[i] = item2602;

            offset += 5;
        }

        int length = packet_size_without_list + (packet.itemCount * sizeof(Item2602));
        SConnection::Send(&user->connection, &packet, length);
    }

    void send_purchase2(CUser* user)
    {
        UserPointSaveBuyPointItemIncoming packet{ 0xE0A, user->userId };
        SConnectionTBaseReconnect::Send(g_pClientToDBAgent, &packet, sizeof(UserPointSaveBuyPointItemIncoming));

        send_reload_point(user);

        InterlockedExchange(&user->disableShop, 0);
    }

    void send_purchase3(CUser* user, const char* targetName, const char* productCode, std::uint32_t itemPrice)
    {
        auto purchaseNumber = InterlockedIncrement(reinterpret_cast<volatile unsigned*>(0x5879B0));

        UserPointSaveGiftPointItemIncoming packet{};
        packet.userId = user->userId;
        StringCbCopyA(packet.targetName.data(), packet.targetName.size(), targetName);
        StringCbCopyA(packet.productCode.data(), packet.productCode.size(), productCode);
        packet.itemPrice = itemPrice;
        packet.purchaseDate = ServerTime::GetSystemTime();
        packet.purchaseNumber = purchaseNumber;
        SConnectionTBaseReconnect::Send(g_pClientToDBAgent, &packet, sizeof(UserPointSaveGiftPointItemIncoming));

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
