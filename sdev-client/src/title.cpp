#include <util/util.h>
#include "include/main.h"
#include "include/static.h"
#include "include/shaiya/include/CCharacter.h"
#include "include/shaiya/include/CDataFile.h"
#include "include/shaiya/include/CEffectData.h"
#include "include/shaiya/include/CMonster.h"
#include "include/shaiya/include/CStaticText.h"
#include "include/shaiya/include/ItemInfo.h"
using namespace shaiya;

namespace title
{
    constexpr float chat_y_add = 1.75F;

    void hook(CCharacter* user, float x, float y, float extrusion)
    {
        const char* text = "Champion of Shaiya";
        const int effectDataId = 280;

        if (!user->pet)
            return;

        auto itemInfo = CDataFile::GetItemInfo(user->petType, user->petTypeId);
        if (!itemInfo)
            return;

        auto itemId = (itemInfo->type * 1000) + itemInfo->typeId;
        if (itemId != 120043)
            return;

        if (!user->title.text)
        {
            user->title.text = CStaticText::Create(text);
            auto w = CStaticText::GetTextWidth(text);
            user->title.pointX = long(w * 0.5);
        }

        if (!user->title.text)
            return;

        auto posY = y - 30.0;
        auto posX = x - user->title.pointX;

        CStaticText::Draw(user->title.text, long(posX), long(posY), extrusion, 0xFFFFFFFF);
        
        if (!user->title.effectDataId)
        {
            CCharacter::RemoveEffect(user, effectDataId, 0);
            CCharacter::RenderEffect(user, effectDataId, 0, 0, &user->pos, &user->dir, &user->up, 0);
            user->title.effectDataId = effectDataId;
        }
    }

    void remove_effect(CCharacter* user)
    {
        if (!user->title.effectDataId)
            return;

        CCharacter::RemoveEffect(user, user->title.effectDataId, 0);
        user->title.effectDataId = 0;
    }

    int create_effect()
    {
        // Champion of Shaiya
        return CEffectData::CreateFromFile(&g_var->eftCharacterEffect01, "data/Effect", "character_effect_01.eft");
    }
}

unsigned u0x453E81 = 0x453E81;
void __declspec(naked) naked_0x453E7C()
{
    __asm
    {
        pushad
        pushfd

        sub esp,0xC
        fld dword ptr[esp+0x4C]
        fstp dword ptr[esp+0x8]

        fld dword ptr[esp+0x48]
        fstp dword ptr[esp+0x4]

        fld dword ptr[esp+0x44]
        fstp dword ptr[esp]

        push esi // user
        call title::hook
        add esp,0x10

        popfd
        popad

        // original
        mov eax,dword ptr ds:[0x22B69A8]
        jmp u0x453E81
    }
}

unsigned u0x4184CF = 0x4184CF;
unsigned u0x418312 = 0x418312;
void __declspec(naked) naked_0x41830D()
{
    __asm 
    {
        // monster->model
        cmp dword ptr[eax+0x74],0x0
        je _0x4184CF
        
        // original
        cmp dword ptr[esp+0x38],0x0
        jmp u0x418312

        _0x4184CF:
        jmp u0x4184CF
    }
}

unsigned u0x412765 = 0x412765;
void __declspec(naked) naked_0x41275F()
{
    __asm
    {
        fld dword ptr[title::chat_y_add]
        jmp u0x412765
    }
}

unsigned u0x59F1BC = 0x59F1BC;
void __declspec(naked) naked_0x59F114()
{
    __asm
    {
        pushad

        push esi
        call title::remove_effect
        add esp,0x4

        popad

        jmp u0x59F1BC
    }
}

unsigned u0x59F484 = 0x59F484;
void __declspec(naked) naked_0x59F299()
{
    __asm
    {
        pushad

        push esi
        call title::remove_effect
        add esp,0x4

        popad

        jmp u0x59F484
    }
}

unsigned u0x412320 = 0x412320;
unsigned u0x59833A = 0x59833A;
void __declspec(naked) naked_0x598335()
{
    __asm
    {
        // original
        call u0x412320

        pushad

        push edi
        call title::remove_effect
        add esp,0x4

        popad

        jmp u0x59833A
    }
}

unsigned u0x58C460 = 0x58C460;
unsigned u0x42D6D2 = 0x42D6D2;
unsigned u0x42D8B5 = 0x42D8B5;
unsigned u0x42BC77 = 0x42BC77;
void __declspec(naked) naked_0x42D6C5()
{
    __asm 
    {
        // original
        call u0x58C460
        test eax,eax
        je _0x42BC77

        pushad

        call title::create_effect
        test eax,eax

        popad

        jne _0x42D8B5
        jmp u0x42D6D2

        _0x42D8B5:
        jmp u0x42D8B5

        _0x42BC77:
        jmp u0x42BC77
    }
}

void hook::title()
{
    util::detour((void*)0x453E7C, naked_0x453E7C, 5);
    // hide pets without a model
    util::detour((void*)0x41830D, naked_0x41830D, 5);
    // increase chat balloon height (1.5 to 1.75)
    util::detour((void*)0x41275F, naked_0x41275F, 6);
    // pet remove case
    util::detour((void*)0x59F114, naked_0x59F114, 5);
    // pet swap case
    util::detour((void*)0x59F299, naked_0x59F299, 5);
    // 0x504 handler
    util::detour((void*)0x598335, naked_0x598335, 5);
    // create effect from .eft file
    util::detour((void*)0x42D6C5, naked_0x42D6C5, 5);
}
