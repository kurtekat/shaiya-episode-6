#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
using namespace shaiya;

void CUser::AddApplySkillBuff(CUser* user, CGameData::SkillInfo* skillInfo)
{
    typedef void(__stdcall* LPFN)(CUser*, CGameData::SkillInfo*);
    (*(LPFN)0x494140)(user, skillInfo);
}

void CUser::AddApplySkillDebuff(CUser* user, CSkill* skill, CGameData::SkillInfo* skillInfo)
{
    typedef void(__stdcall* LPFN)(CUser*, CSkill*, CGameData::SkillInfo*);
    (*(LPFN)0x494BD0)(user, skill, skillInfo);
}

void CUser::CancelActionExc(CUser* user/*edi*/)
{
    Address u0x456610 = 0x456610;

    __asm
    {
        mov edi,user
        call u0x456610
    }
}

bool CUser::DamageByKeepSkill(CUser* user/*edi*/, int _type, ULONG id/*CUser->id*/, CDamage* damage)
{
    Address u0x4583F0 = 0x4583F0;

    __asm
    {
        push damage
        push id
        mov ecx,_type
        mov edi,user
        call u0x4583F0
    }
}

void CUser::ExchangeCancelReady(CUser* user/*ecx*/, CUser* exchangeUser/*esi*/)
{
    typedef void(__thiscall* LPFN)(CUser*);
    __asm { mov esi,exchangeUser }
    (*(LPFN)0x47E250)(user);
}

void CUser::GetGuildName(CUser* user, char* output)
{
    typedef void(__stdcall* LPFN)(char*);
    __asm { mov ebx,user }
    (*(LPFN)0x484F50)(output);
}

int CUser::GetPartyType(CUser* user)
{
    typedef int(__stdcall* LPFN)(CUser*);
    return (*(LPFN)0x49B120)(user);
}

void CUser::InitEquipment(CUser* user/*ecx*/)
{
    typedef void(__thiscall* LPFN)(CUser*);
    (*(LPFN)0x461010)(user);
}

void CUser::InitEquipment(CUser* user/*ecx*/, BOOL reset)
{
    typedef void(__thiscall* LPFN)(CUser*, BOOL);
    (*(LPFN)0x461570)(user, reset);
}

void CUser::ItemBagToBag(CUser* user/*ecx*/, int srcBag, int srcSlot, int destBag, int destSlot)
{
    typedef void(__thiscall* LPFN)(CUser*, int, int, int, int);
    (*(LPFN)0x4685A0)(user, srcBag, srcSlot, destBag, destSlot);
}

bool CUser::ItemCreate(CUser* user/*ecx*/, CGameData::ItemInfo* info, int count)
{
    typedef bool(__thiscall* LPFN)(CUser*, CGameData::ItemInfo*, int);
    return (*(LPFN)0x46BD10)(user, info, count);
}

bool CUser::ItemDelete(CUser* user, int type, int typeId)
{
    typedef bool(__stdcall* LPFN)(CUser*, int, int);
    return (*(LPFN)0x46C6A0)(user, type, typeId);
}

void CUser::ItemEquipmentAdd(CUser* user/*edi*/, CItem* item/*eax*/, int slot)
{
    Address u0x461640 = 0x461640;

    __asm
    {
        push slot
        mov eax,item
        mov edi,user
        call u0x461640
    }
}

void CUser::ItemEquipmentOptionAdd(CUser* user/*eax*/, CItem* item/*esi*/)
{
    Address u0x462720 = 0x462720;

    __asm
    {
        mov esi,item
        mov eax,user
        call u0x462720
    }
}

void CUser::ItemEquipmentOptionRem(CUser* user/*eax*/, CItem* item/*esi*/)
{
    Address u0x462820 = 0x462820;

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

void CUser::ItemRemove(CUser* user/*ecx*/, int bag, int slot/*ebx*/)
{
    typedef void(__thiscall* LPFN)(CUser*, int);
    __asm { mov ebx,slot }
    (*(LPFN)0x46C290)(user, bag);
}

void CUser::ItemUse(CUser* user, int bag, int slot, ULONG targetId, int byTargetType)
{
    typedef void(__stdcall* LPFN)(CUser*, int, int, ULONG, int);
    (*(LPFN)0x472DA0)(user, bag, slot, targetId, byTargetType);
}

void CUser::ItemUseNSend(CUser* user, int bag, int slot, BOOL moveMap)
{
    typedef void(__thiscall* LPFN)(CUser*, int, int, BOOL);
    (*(LPFN)0x4728E0)(user, bag, slot, moveMap);
}

bool CUser::QuestAddItem(CUser* user, int type, int typeId/*ecx*/, int count, int* outBag, int* outSlot/*edx*/, CGameData::ItemInfo** outInfo)
{
    typedef bool(__fastcall* LPFN)(int, int*, CUser*, int, int, int*, CGameData::ItemInfo**);
    return (*(LPFN)0x48D5E0)(typeId, outSlot, user, type, count, outBag, outInfo);
}

void CUser::RemApplySkillBuff(CUser* user/*ecx*/, CGameData::SkillInfo* skillInfo)
{
    typedef void(__thiscall* LPFN)(CUser*, CGameData::SkillInfo*);
    (*(LPFN)0x494760)(user, skillInfo);
}

void CUser::RemApplySkillDebuff(CUser* user/*esi*/, CSkill* skill/*ebx*/, CGameData::SkillInfo* skillInfo/*edx*/)
{
    Address u0x494EB0 = 0x494EB0;

    __asm
    {
        mov esi,user
        mov ebx,skill
        mov edx,skillInfo
        call u0x494EB0
    }
}

void CUser::SendAdminCmdError(CUser* user, UINT16 error/*ecx*/)
{
    Address u0x480770 = 0x480770;

    __asm
    {
        push user
        movzx ecx,error
        call u0x480770
    }
}

void CUser::SendCharacterHonor(CUser* user/*ecx*/)
{
    Address u0x492FE0 = 0x492FE0;

    __asm
    {
        mov ecx,user
        call u0x492FE0
    }
}

void CUser::SendDBExp(CUser* user/*eax*/)
{
    Address u0x47AAA0 = 0x47AAA0;

    __asm
    {
        mov eax,user
        call u0x47AAA0
    }
}

void CUser::SendDBMoney(CUser* user/*eax*/)
{
    Address u0x47AAE0 = 0x47AAE0;

    __asm
    {
        mov eax,user
        call u0x47AAE0
    }
}

// not implemented (sends user->money)
void CUser::SendDBBankMoney(CUser* user/*eax*/)
{
    Address u0x47AB20 = 0x47AB20;

    __asm
    {
        mov eax,user
        call u0x47AB20
    }
}

void CUser::SendDBStatusUp(CUser* user/*eax*/)
{
    Address u0x47AB60 = 0x47AB60;

    __asm
    {
        mov eax,user
        call u0x47AB60
    }
}

void CUser::SendDBGrow(CUser* user/*eax*/)
{
    Address u0x47ABE0 = 0x47ABE0;

    __asm
    {
        mov eax,user
        call u0x47ABE0
    }
}

void CUser::SendDBLevel(CUser* user/*eax*/)
{
    Address u0x47AC20 = 0x47AC20;

    __asm
    {
        mov eax,user
        call u0x47AC20
    }
}

void CUser::SendDBSkillPoint(CUser* user/*eax*/)
{
    Address u0x47ACA0 = 0x47ACA0;

    __asm
    {
        mov eax,user
        call u0x47ACA0
    }
}

void CUser::SendDBStatPoint(CUser* user/*eax*/)
{
    Address u0x47AC60 = 0x47AC60;

    __asm
    {
        mov eax,user
        call u0x47AC60
    }
}

void CUser::SendDBAgentQuickSlot(CUser* user/*eax*/)
{
    Address u0x47ACE0 = 0x47ACE0;

    __asm
    {
        mov eax,user
        call u0x47ACE0
    }
}

void CUser::SendEnergyAllToParty(CUser* user/*eax*/)
{
    Address u0x4911A0 = 0x4911A0;

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
    Address u0x490830 = 0x490830;

    __asm
    {
        mov esi,user
        call u0x490830
    }
}

void CUser::SendMaxMP(CUser* user/*esi*/)
{
    Address u0x490A70 = 0x490A70;

    __asm
    {
        mov esi,user
        call u0x490A70
    }
}

void CUser::SendMaxSP(CUser* user/*esi*/)
{
    Address u0x490960 = 0x490960;

    __asm
    {
        mov esi,user
        call u0x490960
    }
}

void CUser::SendRecoverAdd(CUser* user/*eax*/, int health/*ecx*/, int stamina/*edx*/, int mana)
{
    Address u0x490DA0 = 0x490DA0;

    __asm
    {
        push mana
        mov edx,stamina
        mov ecx,health
        mov eax,user
        call u0x490DA0
    }
}

void CUser::SendRecoverChange(CUser* user/*esi*/, int health/*ecx*/, int stamina, int mana/*edx*/)
{
    Address u0x491080 = 0x491080;

    __asm
    {
        push stamina
        mov edx,mana
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
    Address u0x4910F0 = 0x4910F0;

    __asm
    {
        push mana
        mov edx,stamina
        mov ecx,health
        mov esi,user
        call u0x4910F0
    }
}

void CUser::SendRunMode(CUser* user, BOOL runMode)
{
    user->running = runMode;

    typedef void(__stdcall* LPFN)(CUser*, BOOL);
    (*(LPFN)0x491510)(user, runMode);
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
    Address u0x460E40 = 0x460E40;

    __asm
    {
        mov esi,user
        call u0x460E40
    }
}

void CUser::SetSkillAbility(CUser* user, int typeEffect/*ecx*/, int _type/*edx*/, int value/*eax*/)
{
    Address u0x495570 = 0x495570;

    __asm
    {
        push user
        mov ecx,typeEffect
        mov edx,_type
        mov eax,value
        call u0x495570
    }
}

void CUser::StatResetSkill(CUser* user/*eax*/, BOOL _event)
{
    Address u0x48FBC0 = 0x48FBC0;

    __asm
    {
        push _event
        mov eax,user
        call u0x48FBC0
    }
}

void CUser::StatResetStatus(CUser* user/*edi*/, BOOL _event)
{
    Address u0x48F710 = 0x48F710;

    __asm
    {
        push _event
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
    Address u0x49C280 = 0x49C280;

    __asm
    {
        mov eax,user
        call u0x49C280
    }
}

void CUser::UseItemSkill(CUser* user/*edi*/, CGameData::SkillInfo* info/*eax*/)
{
    Address u0x4725B0 = 0x4725B0;

    __asm
    {
        mov eax,info
        mov edi,user
        call u0x4725B0
    }
}
