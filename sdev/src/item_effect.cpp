//#define SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
#include <util/util.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemType.h>
#include <shaiya/include/network/game/outgoing/0400.h>
#include "include/main.h"
#include "include/operator.h"
#include "include/shaiya/CharmType.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/ItemInfo.h"
using namespace shaiya;

namespace item_effect
{
    /// <summary>
    /// Implements item effects 212, 213, and 214.
    /// </summary>
    int zone_enter_item_hook(CItem* item, int enterType)
    {
        if (enterType != GameItemZoneEnterType::MobDrop)
            return 0;

        if (!item->zone)
            return 0;

        auto user = CZone::FindUser(item->zone, item->userId);
        if (!user)
            return 0;

        auto& pet = user->inventory[0][14];
        if (!pet)
            return 0;

        if (item->type == ItemType::Gold)
        {
            auto money = item->dropMoney;
            if (!money)
                return 0;

            auto effect = pet->info->effect;
            if (effect != ItemEffect::PetGoldPick && effect != ItemEffect::PetGoldItemPick)
                return 0;

            auto rate = user->increaseGoldDropRate;
            switch (user->charmType)
            {
            case CharmType::BlueDragon:
                break;
            case CharmType::WhiteTiger:
                rate += 20;
                break;
            case CharmType::RedPhoenix:
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

            auto effect = pet->info->effect;
            if (effect != ItemEffect::PetItemPick && effect != ItemEffect::PetGoldItemPick)
                return 0;

            CUser::ItemGet(user, item);
            return 1;
        }
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
#ifdef SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
    // CZone::EnterItem
    util::detour((void*)0x41DA15, naked_0x41DA15, 5);
#endif
}
