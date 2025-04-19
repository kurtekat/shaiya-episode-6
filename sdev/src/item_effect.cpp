//#define SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
#include <util/util.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/SkillTypes.h>
#include <shaiya/include/network/game/incoming/0500.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/0400.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CNpcData.h"
#include "include/shaiya/include/CObject.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/CZone.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/NpcGateKeeper.h"
#include "include/shaiya/include/UserHelper.h"
using namespace shaiya;

namespace item_effect
{
    /// <summary>
    /// Adds support for additional item effects.
    /// </summary>
    int hook(CUser* user, CItem* item, ItemEffect effect, uint bag, uint slot)
    {
        switch (effect)
        {
        case ItemEffect::TownMoveScroll:
        {
            NpcGateKeeper* gateKeeper = nullptr;

            switch (item->info->itemId)
            {
            case 101102:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 111);
                break;
            case 101103:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 112);
                break;
            case 101104:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 101);
                break;
            case 101105:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 102);
                break;
            case 101106:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 103);
                break;
            case 101107:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 104);
                break;
            case 101108:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 105);
                break;
            case 101109:
                gateKeeper = CNpcData<NpcGateKeeper*>::GetNpc(2, 106);
                break;
            default:
                return 0;
            }

            if (!gateKeeper)
                return 0;

            auto index = user->savePosUseIndex;
            if (index < 0 || index > 2)
                return 0;

            auto mapId = gateKeeper->gates[index].mapId;
            auto x = gateKeeper->gates[index].x;
            auto y = gateKeeper->gates[index].y;
            auto z = gateKeeper->gates[index].z;
            UserHelper::SetMovePosition(user, mapId, x, y, z, int(UserMovePosType::TownMoveScroll), 5000);

            GameUserItemCastOutgoing outgoing{};
            outgoing.objectId = user->id;
            CObject::PSendViewCombat(user, &outgoing, sizeof(GameUserItemCastOutgoing));
            return 1;
        }
        default:
            return 0;
        }
    }

    /// <summary>
    /// Handles incoming 0x55A packets.
    /// </summary>
    void handler_0x55A(CUser* user, GameTownMoveScrollIncoming* incoming)
    {
        if (user->status == UserStatus::Death)
            return;

        if (!incoming->bag || incoming->bag > user->bagsUnlocked || incoming->slot >= max_inventory_slot)
            return;

        auto& item = user->inventory[incoming->bag][incoming->slot];
        if (!item)
            return;

        if (item->info->effect != ItemEffect::TownMoveScroll)
            return;

        if (incoming->gateIndex > 2)
            return;

        user->savePosUseBag = incoming->bag;
        user->savePosUseSlot = incoming->slot;
        user->savePosUseIndex = incoming->gateIndex;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);
        CUser::ItemUse(user, incoming->bag, incoming->slot, user->id, 0);
    }

    void town_move_scroll_hook(CUser* user)
    {
        auto& item = user->inventory[user->savePosUseBag][user->savePosUseSlot];
        if (!item)
            return;

        if (item->info->realType != RealType::Consumable)
            return;

        if (item->info->effect != ItemEffect::TownMoveScroll)
            return;

        if (user->mapId != user->moveMapId)
        {
            CWorld::ZoneLeaveUserMove(user, user->moveMapId, user->movePos.x, user->movePos.y, user->movePos.z);

            GameUserSetMapPosOutgoing outgoing{};
            outgoing.objectId = user->id;
            outgoing.mapId = user->moveMapId;
            outgoing.x = user->movePos.x;
            outgoing.y = user->movePos.y;
            outgoing.z = user->movePos.z;
            NetworkHelper::Send(user, &outgoing, sizeof(GameUserSetMapPosOutgoing));
            CUser::ItemUseNSend(user, user->savePosUseBag, user->savePosUseSlot, true);
        }
        else
        {
            if (!user->zone)
                return;

            if (!CZone::MoveUser(user->zone, user, user->movePos.x, user->movePos.y, user->movePos.z))
                return;

            GameUserSetMapPosOutgoing outgoing{};
            outgoing.objectId = user->id;
            outgoing.mapId = user->moveMapId;
            outgoing.x = user->movePos.x;
            outgoing.y = user->movePos.y;
            outgoing.z = user->movePos.z;
            CObject::SendView(user, &outgoing, sizeof(GameUserSetMapPosOutgoing));
            CUser::ItemUseNSend(user, user->savePosUseBag, user->savePosUseSlot, false);
        }
    }

    /// <summary>
    /// Implements item effects 212, 213, and 214.
    /// </summary>
    int zone_enter_item_hook(CItem* item, int enterType)
    {
        if (enterType != std::to_underlying(GameItemZoneEnterType::MobDrop))
            return 0;

        if (!item->zone)
            return 0;

        auto user = CZone::FindUser(item->zone, item->userId);
        if (!user)
            return 0;

        auto& pet = user->inventory[0][int(EquipmentSlot::Pet)];
        if (!pet)
            return 0;

        if (item->type == std::to_underlying(ItemType::Gold))
        {
            auto money = item->dropMoney;
            if (!money)
                return 0;

            auto effect = pet->info->effect;
            if (effect != ItemEffect::PetPickGoldDrop && effect != ItemEffect::PetPickDrop)
                return 0;

            auto rate = user->increaseGoldDropRate;
            switch (user->charmType)
            {
            case SkillCharmType::BlueDragon:
                break;
            case SkillCharmType::WhiteTiger:
                rate += 20;
                break;
            case SkillCharmType::RedPhoenix:
                rate += 50;
                break;
            default:
                break;
            }

            if (rate > 0)
                money += (rate / money) * 100;

            CUser::ItemGetMoney(user, money);
            return 1;
        }
        else
        {
            if (!item->info)
                return 0;

            if (item->info->realType == RealType::Quest)
                return 0;

            auto effect = pet->info->effect;
            if (effect != ItemEffect::PetPickItemDrop && effect != ItemEffect::PetPickDrop)
                return 0;

            CUser::ItemGet(user, item);
            return 1;
        }
    }
}

unsigned u0x47469F = 0x47469F;
unsigned u0x474690 = 0x474690;
void __declspec(naked) naked_0x47468A()
{
    __asm
    {
        pushad

        mov edx,[esp+0xB7C]
        mov edi,[esp+0xB78]

        push edx // slot
        push edi // bag
        push ecx // effect
        push ebx // item
        push ebp // user
        call item_effect::hook
        add esp,0x14
        test eax,eax

        popad

        jne _0x47469F

        // original
        mov eax,[esp+0x40]
        test eax,eax
        jmp u0x474690

        _0x47469F:
        jmp u0x47469F
    }
}

unsigned u0x4784DB = 0x4784DB;
unsigned u0x479155 = 0x479155;
void __declspec(naked) naked_0x4784D6()
{
    __asm
    {
        add eax,-0x501
        cmp eax,0x59
        je case_0x55A
        jmp u0x4784DB

        case_0x55A:
        pushad

        push ebp // packet
        push ecx // user
        call item_effect::handler_0x55A
        add esp,0x8

        popad

        jmp u0x479155
    }
}

unsigned u0x49DDC8 = 0x49DDC8;
unsigned u0x49DEB5 = 0x49DEB5;
unsigned u0x49E8D1 = 0x49E8D1;
void __declspec(naked) naked_0x49DDBF()
{
    __asm
    {
        cmp eax,0x7
        je town_move_scroll

        // original
        cmp eax,0x1
        jne _0x49DEB5
        jmp u0x49DDC8

        town_move_scroll:
        pushad

        push edi // user
        call item_effect::town_move_scroll_hook
        add esp,0x4

        popad

        jmp u0x49E8D1

        _0x49DEB5:
        jmp u0x49DEB5
    }
}

// CCell::EnterItem
unsigned u0x42A170 = 0x42A170;
unsigned u0x41DA1A = 0x41DA1A;
unsigned u0x41DA85 = 0x41DA85;
void __declspec(naked) naked_0x41DA15()
{
    __asm
    {
        pushad

        mov eax,[esp+0x4C]

        push eax // kind
        push edi // item
        call item_effect::zone_enter_item_hook
        add esp,0x8
        test eax,eax

        popad

        jne _0x41DA85

        // original
        call u0x42A170
        jmp u0x41DA1A

        _0x41DA85:
        jmp u0x41DA85
    }
}

void hook::item_effect()
{
    // CUser::ItemUse
    util::detour((void*)0x47468A, naked_0x47468A, 6);
    // CUser::PacketPC
    util::detour((void*)0x4784D6, naked_0x4784D6, 5);
    // CUser::UpdateResetPosition
    util::detour((void*)0x49DDBF, naked_0x49DDBF, 9);
#ifdef SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
    // CZone::EnterItem
    util::detour((void*)0x41DA15, naked_0x41DA15, 5);
#endif
}
