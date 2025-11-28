//#define SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
#include <util/util.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemSlot.h>
#include <shaiya/include/common/ItemType.h>
#include <shaiya/include/common/SkillTypes.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/0400.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CNpcData.h"
#include "include/shaiya/CObject.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NetworkHelper.h"
#include "include/shaiya/NpcGateKeeper.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

namespace item_effect
{
    /// <summary>
    /// Adds support for additional item effects. Add new values to the enum and 
    /// then add more cases to this function.
    /// </summary>
    int hook(CUser* user, CItem* item, ItemEffect itemEffect, int bag, int slot)
    {
        switch (itemEffect)
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
            UserHelper::SetMovePosition(user, mapId, x, y, z, UserMovePosType::TownMoveScroll, 5000);

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
    /// Implements item effects 212, 213, and 214.
    /// </summary>
    int zone_enter_item_hook(CItem* item, int enterType)
    {
        if (enterType != static_cast<int>(GameItemZoneEnterType::MobDrop))
            return 0;

        if (!item->zone)
            return 0;

        auto user = CZone::FindUser(item->zone, item->userId);
        if (!user)
            return 0;

        auto& pet = user->inventory[0][ItemSlot::Pet];
        if (!pet)
            return 0;

        if (item->type == ItemType::Gold)
        {
            auto money = item->dropMoney;
            if (!money)
                return 0;

            auto itemEffect = pet->info->effect;
            if (itemEffect != ItemEffect::PetPickGoldDrop && itemEffect != ItemEffect::PetPickDrop)
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
            {
                auto bonus = (rate * money) / 100;
                money += bonus;
            }

            CUser::ItemGetMoney(user, money);
            return 1;
        }
        else
        {
            if (!item->info)
                return 0;

            if (item->info->realType == RealType::Quest)
                return 0;

            auto itemEffect = pet->info->effect;
            if (itemEffect != ItemEffect::PetPickItemDrop && itemEffect != ItemEffect::PetPickDrop)
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
#ifdef SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
    // CZone::EnterItem
    util::detour((void*)0x41DA15, naked_0x41DA15, 5);
#endif
}
