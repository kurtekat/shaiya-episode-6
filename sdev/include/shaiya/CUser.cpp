#include "CItem.h"
#include "CQuest.h"
#include "CUser.h"
#include "ItemInfo.h"
#include "SkillInfo.h"
using namespace shaiya;

void CUser::AddExpFromUser(CUser* user/*esi*/, unsigned lastTargetId, int exp, bool isQuest)
{
    unsigned u0x465060 = 0x465060;

    __asm
    {
        movzx eax,isQuest
        push eax
        push exp
        push lastTargetId
        mov esi,user
        call u0x465060
    }
}

void CUser::CancelActionExc(CUser* user/*edi*/)
{
    unsigned u0x456610 = 0x456610;

    __asm
    {
        mov edi,user
        call u0x456610
    }
}

void CUser::ChkAddMoneyGet(CUser* user/*ecx*/, unsigned money/*edx*/)
{
    typedef void(__fastcall* LPFN)(CUser*, unsigned);
    (*(LPFN)0x486E60)(user, money);
}

void CUser::GemEquipmentAdd(CUser* user/*eax*/, int slot/*esi*/, int gem/*ecx*/)
{
    unsigned u0x462A70 = 0x462A70;

    _asm
    {
        mov ecx,gem
        mov esi,slot
        mov eax,user
        call u0x462A70
    }
}

void CUser::GemEquipmentRem(CUser* user/*eax*/, int slot/*esi*/, int gem/*ecx*/)
{
    unsigned u0x462C10 = 0x462C10;

    _asm
    {
        mov ecx,gem
        mov esi,slot
        mov eax,user
        call u0x462C10
    }
}

void CUser::GetGuildName(CUser* user, char* output)
{
    unsigned u0x484F50 = 0x484F50;

    __asm
    {
        push output
        mov ebx,user
        call u0x484F50
    }
}

PartyType CUser::GetPartyType(CUser* user)
{
    typedef PartyType(__stdcall* LPFN)(CUser*);
    return (*(LPFN)0x49B120)(user);
}

void CUser::InitEquipment(CUser* user/*ecx*/)
{
    typedef void(__thiscall* LPFN)(CUser*);
    (*(LPFN)0x461010)(user);
}

void CUser::InitEquipment(CUser* user/*ecx*/, bool reset)
{
    typedef void(__thiscall* LPFN)(CUser*, bool);
    (*(LPFN)0x461570)(user, reset);
}

void CUser::ItemBagToBag(CUser* user/*ecx*/, int srcBag, int srcSlot, int destBag, int destSlot)
{
    typedef void(__thiscall* LPFN)(CUser*, int, int, int, int);
    (*(LPFN)0x4685A0)(user, srcBag, srcSlot, destBag, destSlot);
}

void CUser::ItemBagToBank(CUser* user/*ecx*/, int srcBag, int srcSlot, int destBag/*100*/, int destSlot/*ecx*/)
{
    unsigned u0x469400 = 0x469400;

    __asm
    {
        mov ecx,destSlot
        push destBag
        push srcSlot
        push srcBag
        mov edx,user
        call u0x469400
    }
}

void CUser::ItemBankToBag(CUser* user/*edx*/, int srcBag/*100*/, int srcSlot/*ecx*/, int destBag, int destSlot)
{
    unsigned u0x468E80 = 0x468E80;

    __asm
    {
        push destSlot
        push destBag
        mov ecx,srcSlot
        push srcBag
        mov edx,user
        call u0x468E80
    }
}

void CUser::ItemBankToBank(CUser* user/*esi*/, int srcBag/*100*/, int srcSlot, int destBag/*100*/, int destSlot/*ecx*/)
{
    unsigned u0x469950 = 0x469950;

    __asm
    {
        mov ecx,destSlot
        push destBag
        push srcSlot
        push srcBag
        mov esi,user
        call u0x469950
    }
}

bool CUser::ItemCreate(CUser* user/*ecx*/, ItemInfo* info, int count)
{
    typedef bool(__thiscall* LPFN)(CUser*, ItemInfo*, int);
    return (*(LPFN)0x46BD10)(user, info, count);
}

bool CUser::ItemDelete(CUser* user, int type, int typeId)
{
    typedef bool(__stdcall* LPFN)(CUser*, int, int);
    return (*(LPFN)0x46C6A0)(user, type, typeId);
}

void CUser::ItemEquipmentAdd(CUser* user/*edi*/, CItem* item/*eax*/, int slot)
{
    unsigned u0x461640 = 0x461640;

    __asm
    {
        push slot
        mov eax,item
        mov edi,user
        call u0x461640
    }
}

void CUser::ItemEquipmentRem(CUser* user/*edx*/, CItem* item/*ecx*/, int slot)
{
    unsigned u0x461D10 = 0x461D10;

    __asm
    {
        push slot
        mov ecx,item
        mov edx,user
        call u0x461D10
    }
}

void CUser::ItemEquipmentOptionAdd(CUser* user/*eax*/, CItem* item/*esi*/)
{
    unsigned u0x462720 = 0x462720;

    __asm
    {
        mov esi,item
        mov eax,user
        call u0x462720
    }
}

void CUser::ItemEquipmentOptionRem(CUser* user/*eax*/, CItem* item/*esi*/)
{
    unsigned u0x462820 = 0x462820;

    __asm
    {
        mov esi,item
        mov eax,user
        call u0x462820
    }
}

void CUser::ItemGet(CUser* user/*ecx*/, CItem* item)
{
    typedef void(__thiscall* LPFN)(CUser*, CItem*);
    (*(LPFN)0x46AE60)(user, item);
}

void CUser::ItemGetMoney(CUser* user/*edx*/, unsigned money/*ecx*/)
{
    unsigned u0x46BBA0 = 0x46BBA0;

    __asm
    {
        mov ecx,money
        mov edx,user
        call u0x46BBA0
    }
}

void CUser::ItemRemove(CUser* user/*ecx*/, int bag, int slot/*ebx*/)
{
    unsigned u0x46C290 = 0x46C290;

    __asm
    {
        push bag
        mov ebx,slot
        mov ecx,user
        call u0x46C290
    }
}

void CUser::ItemUse(CUser* user, int bag, int slot, unsigned targetId, int targetType)
{
    typedef void(__stdcall* LPFN)(CUser*, int, int, unsigned, int);
    (*(LPFN)0x472DA0)(user, bag, slot, targetId, targetType);
}

void CUser::ItemUseNSend(CUser* user, int bag, int slot, bool moveMap)
{
    typedef void(__thiscall* LPFN)(CUser*, int, int, bool);
    (*(LPFN)0x4728E0)(user, bag, slot, moveMap);
}

void CUser::LevelChange(CUser* user, int prevLv, int currLv)
{
    unsigned u0x49BD70 = 0x49BD70;

    __asm
    {
        push currLv
        mov eax,prevLv
        mov ecx,user
        call u0x49BD70
    }
}

void CUser::LevelUp(CUser* user, bool event)
{
    typedef void(__stdcall* LPFN)(CUser*, bool);
    (*(LPFN)0x49B9C0)(user, event);
}

void CUser::LevelUpStatus(CUser* user)
{
    unsigned u0x49B3B0 = 0x49B3B0;

    __asm
    {
        mov eax,user
        call u0x49B3B0
    }
}

bool CUser::QuestAddItem(CUser* user, int type, int typeId/*ecx*/, int count, int* outBag, int* outSlot/*edx*/, ItemInfo* outInfo)
{
    typedef bool(__fastcall* LPFN)(int, int*, CUser*, int, int, int*, ItemInfo*);
    return (*(LPFN)0x48D5E0)(typeId, outSlot, user, type, count, outBag, outInfo);
}

CQuest* CUser::QuestFind(CUser* user/*edi*/, int questId)
{
    unsigned u0x48D3A0 = 0x48D3A0;

    __asm
    {
        mov edi,user
        push questId
        call u0x48D3A0
    }
}

void CUser::QuestRemove(CUser* user/*esi*/, CQuest* quest/*eax*/, bool success)
{
    unsigned u0x48D030 = 0x48D030;

    __asm
    {
        movzx eax,success
        push eax
        mov eax,quest
        mov esi,user
        call u0x48D030
    }
}

void CUser::SendCharacterHonor(CUser* user/*ecx*/)
{
    unsigned u0x492FE0 = 0x492FE0;

    __asm
    {
        mov ecx,user
        call u0x492FE0
    }
}

void CUser::SendDBExp(CUser* user/*eax*/)
{
    unsigned u0x47AAA0 = 0x47AAA0;

    __asm
    {
        mov eax,user
        call u0x47AAA0
    }
}

void CUser::SendDBMoney(CUser* user/*eax*/)
{
    unsigned u0x47AAE0 = 0x47AAE0;

    __asm
    {
        mov eax,user
        call u0x47AAE0
    }
}

// not implemented (sends user->money)
void CUser::SendDBBankMoney(CUser* user/*eax*/)
{
    unsigned u0x47AB20 = 0x47AB20;

    __asm
    {
        mov eax,user
        call u0x47AB20
    }
}

void CUser::SendDBStatusUp(CUser* user/*eax*/)
{
    unsigned u0x47AB60 = 0x47AB60;

    __asm
    {
        mov eax,user
        call u0x47AB60
    }
}

void CUser::SendDBGrow(CUser* user/*eax*/)
{
    unsigned u0x47ABE0 = 0x47ABE0;

    __asm
    {
        mov eax,user
        call u0x47ABE0
    }
}

void CUser::SendDBLevel(CUser* user/*eax*/)
{
    unsigned u0x47AC20 = 0x47AC20;

    __asm
    {
        mov eax,user
        call u0x47AC20
    }
}

void CUser::SendDBSkillPoint(CUser* user/*eax*/)
{
    unsigned u0x47ACA0 = 0x47ACA0;

    __asm
    {
        mov eax,user
        call u0x47ACA0
    }
}

void CUser::SendDBStatPoint(CUser* user/*eax*/)
{
    unsigned u0x47AC60 = 0x47AC60;

    __asm
    {
        mov eax,user
        call u0x47AC60
    }
}

void CUser::SendDBAgentQuickSlot(CUser* user/*eax*/)
{
    unsigned u0x47ACE0 = 0x47ACE0;

    __asm
    {
        mov eax,user
        call u0x47ACE0
    }
}

void CUser::SendEnergyAllToParty(CUser* user/*eax*/)
{
    unsigned u0x4911A0 = 0x4911A0;

    __asm
    {
        mov eax,user
        call u0x4911A0
    }
}

void CUser::SendEquipment(CUser* user/*ecx*/, int slot)
{
    typedef void(__thiscall* LPFN)(CUser*, int);
    (*(LPFN)0x492C00)(user, slot);
}

void CUser::SendMaxHP(CUser* user/*esi*/)
{
    unsigned u0x490830 = 0x490830;

    __asm
    {
        mov esi,user
        call u0x490830
    }
}

void CUser::SendMaxMP(CUser* user/*esi*/)
{
    unsigned u0x490A70 = 0x490A70;

    __asm
    {
        mov esi,user
        call u0x490A70
    }
}

void CUser::SendMaxSP(CUser* user/*esi*/)
{
    unsigned u0x490960 = 0x490960;

    __asm
    {
        mov esi,user
        call u0x490960
    }
}

void CUser::SendRecoverAdd(CUser* user/*eax*/, int health/*ecx*/, int stamina/*edx*/, int mana)
{
    unsigned u0x490DA0 = 0x490DA0;

    __asm
    {
        push mana
        mov edx,stamina
        mov ecx,health
        mov eax,user
        call u0x490DA0
    }
}

void CUser::SendRecoverChange(CUser* user/*esi*/, int health/*ecx*/, int stamina/*edx*/, int mana)
{
    unsigned u0x491080 = 0x491080;

    __asm
    {
        push mana
        mov edx,stamina
        mov ecx,health
        mov esi,user
        call u0x491080
    }
}

void CUser::SendRecoverMe(CUser* user/*ecx*/, int health, int stamina, int mana)
{
    typedef void(__thiscall* LPFN)(CUser*, int, int, int);
    (*(LPFN)0x490D60)(user, health, stamina, mana);
}

void CUser::SendRecoverSet(CUser* user/*esi*/, int health/*ecx*/, int stamina/*edx*/, int mana)
{
    unsigned u0x4910F0 = 0x4910F0;

    __asm
    {
        push mana
        mov edx,stamina
        mov ecx,health
        mov esi,user
        call u0x4910F0
    }
}

void CUser::SendShape(CUser* user/*ecx*/)
{
    typedef void(__thiscall* LPFN)(CUser*);
    (*(LPFN)0x4913E0)(user);
}

void CUser::SendSpeed(CUser* user/*ecx*/)
{
    typedef void(__thiscall* LPFN)(CUser*);
    (*(LPFN)0x491600)(user);
}

void CUser::SendUserShape(CUser* user)
{
    typedef void(__stdcall* LPFN)(CUser*);
    (*(LPFN)0x491B00)(user);
}

void CUser::SetAttack(CUser* user/*esi*/)
{
    unsigned u0x460E40 = 0x460E40;

    __asm
    {
        mov esi,user
        call u0x460E40
    }
}

void CUser::SetGameLogMain(CUser* user/*edi*/, void* packet/*esi*/)
{
    unsigned u0x467F60 = 0x467F60;

    __asm
    {
        mov esi,packet
        mov edi,user
        call u0x467F60
    }
}

void CUser::StatResetSkill(CUser* user/*eax*/, bool event)
{
    unsigned u0x48FBC0 = 0x48FBC0;

    __asm
    {
        movzx eax,event
        push eax
        mov eax,user
        call u0x48FBC0
    }
}

void CUser::StatResetStatus(CUser* user/*edi*/, bool event)
{
    unsigned u0x48F710 = 0x48F710;

    __asm
    {
        movzx eax,event
        push eax
        mov edi,user
        call u0x48F710
    }
}

void CUser::TauntMob(CUser* user, float dist, int aggro)
{
    typedef void(__stdcall* LPFN)(CUser*, float, int);
    (*(LPFN)0x4977B0)(user, dist, aggro);
}

void CUser::UpdateKCStatus(CUser* user/*eax*/)
{
    unsigned u0x49C280 = 0x49C280;

    __asm
    {
        mov eax,user
        call u0x49C280
    }
}

bool CUser::UseItemSkill(CUser* user/*edi*/, SkillInfo* info/*eax*/)
{
    unsigned u0x4725B0 = 0x4725B0;

    __asm
    {
        mov eax,info
        mov edi,user
        call u0x4725B0
    }
}
