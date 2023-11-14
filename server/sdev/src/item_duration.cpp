#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/022E.h>
#include <include/shaiya/packets/022F.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/ServerTime.h>
using namespace shaiya;

namespace item_duration
{
    constexpr int warehouse_bag = 100;

    void send_delete_notice(CUser* user, CItem* item, int bag, int slot)
    {
        CUser::ItemRemove(user, bag, slot);

        ItemExpireNoticeOutgoing packet{};
        packet.type = item->type;
        packet.typeId = item->typeId;

        if (bag == warehouse_bag)
            packet.noticeType = ItemExpireNoticeType::DeletedFromWarehouse;
        else
            packet.noticeType = ItemExpireNoticeType::DeletedFromInventory;

        SConnection::Send(&user->connection, &packet, sizeof(ItemExpireNoticeOutgoing));
    }

    void send_expire_notice(CUser* user, CItem* item, int bag, int slot)
    {
        int days = item->itemInfo->range;
        if (!days)
            return;

        auto expireTime = ServerTime::GetExpireTime(item->makeTime, days);
        if (!expireTime)
            return;

        SYSTEMTIME st{};
        ServerTime::ServerTimeToSystemTime(expireTime, &st);
        Duration duration(&st);

        if (duration.expired())
        {
            send_delete_notice(user, item, bag, slot);
            return;
        }

        if (!duration.days)
        {
            ItemExpireNoticeOutgoing packet{};
            packet.type = item->type;
            packet.typeId = item->typeId;

            if (!duration.hours)
            {
                packet.timeValue = static_cast<std::uint8_t>(duration.minutes);

                if (bag == warehouse_bag)
                    packet.noticeType = ItemExpireNoticeType::MinutesLeftWarehouse;
                else
                    packet.noticeType = ItemExpireNoticeType::MinutesLeftInventory;
            }
            else
            {
                packet.timeValue = static_cast<std::uint8_t>(duration.hours);

                if (bag == warehouse_bag)
                    packet.noticeType = ItemExpireNoticeType::HoursLeftWarehouse;
                else
                    packet.noticeType = ItemExpireNoticeType::HoursLeftInventory;
            }

            SConnection::Send(&user->connection, &packet, sizeof(ItemExpireNoticeOutgoing));
        }
    }

    void send(CUser* user, CItem* item, int bag, int slot)
    {
        int days = item->itemInfo->range;
        if (!days)
            return;

        switch (static_cast<CGameData::ItemType>(item->type))
        {
        case CGameData::ItemType::Pet:
        case CGameData::ItemType::Costume:
        {
            ItemDurationOutgoing packet{};
            packet.bag = bag;
            packet.slot = slot;
            packet.fromDate = item->makeTime;
            packet.toDate = ServerTime::GetExpireTime(item->makeTime, days);
            SConnection::Send(&user->connection, &packet, sizeof(ItemDurationOutgoing));

            send_expire_notice(user, item, bag, slot);
            break;
        }
        default:
            break;
        }
    }

    void send_bag_and_bank(CUser* user)
    {
        for (int bag = 0; bag < MAX_INVENTORY_BAG; ++bag)
        {
            for (int slot = 0; slot < MAX_INVENTORY_SLOT; ++slot)
            {
                auto& item = user->inventory[bag][slot];
                if (!item)
                    continue;

                send(user, item, bag, slot);
            }
        }

        for (int slot = 0; slot < MAX_WAREHOUSE_SLOT; ++slot)
        {
            auto& item = user->warehouse[slot];
            if (!item)
                continue;

            send(user, item, warehouse_bag, slot);
        }
    }

    void send_bag_to_bank(CUser* user, Packet buffer)
    {
        auto slot = util::read_bytes<std::uint8_t>(buffer, 37);
        if (slot >= MAX_WAREHOUSE_SLOT)
            return;

        auto& item = user->warehouse[slot];
        if (!item)
            return;

        int days = item->itemInfo->range;
        if (!days)
            return;

        switch (static_cast<CGameData::ItemType>(item->type))
        {
        case CGameData::ItemType::Pet:
        case CGameData::ItemType::Costume:
        {
            ItemDurationOutgoing packet{};
            packet.bag = warehouse_bag;
            packet.slot = slot;
            packet.fromDate = item->makeTime;
            packet.toDate = ServerTime::GetExpireTime(item->makeTime, days);
            SConnection::Send(&user->connection, &packet, sizeof(ItemDurationOutgoing));
            break;
        }
        default:
            break;
        }
    }

    void send_item_create(CUser* user, CItem* item, Packet buffer)
    {
        int days = item->itemInfo->range;
        if (!days)
            return;

        switch (static_cast<CGameData::ItemType>(item->type))
        {
        case CGameData::ItemType::Pet:
        case CGameData::ItemType::Costume:
        {
            ItemDurationOutgoing packet{};
            packet.bag = util::read_bytes<std::uint8_t>(buffer, 2);
            packet.slot = util::read_bytes<std::uint8_t>(buffer, 3);
            packet.fromDate = item->makeTime;
            packet.toDate = ServerTime::GetExpireTime(item->makeTime, days);
            SConnection::Send(&user->connection, &packet, sizeof(ItemDurationOutgoing));
            break;
        }
        default:
            break;
        }
    }
}

unsigned u0x492500 = 0x492500;
unsigned u0x47BC54 = 0x47BC54;
void __declspec(naked) naked_0x47BC4F()
{
    __asm
    {
        // original
        call u0x492500

        pushad

        push ebp // user
        call item_duration::send_bag_and_bank
        add esp,0x4

        popad
     
        jmp u0x47BC54
    }
}

unsigned u0x4ED0E0 = 0x4ED0E0;
unsigned u0x469934 = 0x469934;
void __declspec(naked) naked_0x46992F()
{
    __asm
    {
        // original
        call u0x4ED0E0

        pushad

        lea edx,[esp+0x40]

        push edx // packet
        push edi // user
        call item_duration::send_bag_to_bank
        add esp,0x8

        popad
     
        jmp u0x469934
    }
}

unsigned u0x46C22F = 0x46C22F;
void __declspec(naked) naked_0x46C22A()
{
    __asm
    {
        // original
        call u0x4ED0E0

        pushad

        lea edx,[esp+0xB4]
        mov ecx,[esp+0x38]

        push edx // packet
        push ebp // item
        push ecx // user
        call item_duration::send_item_create
        add esp,0xC

        popad
     
        jmp u0x46C22F
    }
}

void hook::item_duration()
{
    // CUser::PacketUserDBChar
    util::detour((void*)0x47BC4F, naked_0x47BC4F, 5);
    // CUser::ItemBagToBank
    util::detour((void*)0x46992F, naked_0x46992F, 5);
    // CUser::ItemCreate
    util::detour((void*)0x46C22A, naked_0x46C22A, 5);
}
