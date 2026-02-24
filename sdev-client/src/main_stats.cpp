#include <array>
#include <format>
#include <ranges>
#include <string>
#include <util/util.h>
#include <shaiya/include/network/game/incoming/0200.h>
#include "include/main.h"
#include "include/shaiya/BattlefieldMoveInfo.h"
#include "include/shaiya/Configuration.h"
#include "include/shaiya/CMessage.h"
#include "include/shaiya/CNetwork.h"
#include "include/shaiya/CPlayerData.h"
#include "include/shaiya/CStatusMiniBar.h"
#include "include/shaiya/Static.h"
using namespace shaiya;

void hook_0x531810(CStatusMiniBar_EP7* window)
{
    window->size.width = 210.0F;
    window->size.height = 75.0F;
    window->size3.width = 256.0F;
    window->size3.height = 128.0F;
    window->size4.width = 128.0F;
    window->size4.height = 128.0F;
    window->namePos.x = 115.0F;
    window->namePos.y = 3.0F;
    window->levelPos.x = 30.0F;
    window->levelPos.y = 27.0F;
    window->facePos.x = 6.0F;
    window->facePos.y = 14.0F;
    window->hpBarPos.x = 72.0F;
    window->hpBarPos.y = 25.0F;
    window->hpPos.x = 72.0F;
    window->hpPos.y = 27.0F;
    window->mpBarPos.x = 72.0F;
    window->mpBarPos.y = 41.0F;
    window->mpPos.x = 72.0F;
    window->mpPos.y = 43.0F;
    window->spBarPos.x = 72.0F;
    window->spBarPos.y = 57.0F;
    window->spPos.x = 72.0F;
    window->spPos.y = 59.0F;
}

void hook_0x531F97(CStatusMiniBar_EP7* window)
{
    CButton::Init(&window->button);
    window->image6 = {};
    window->message = nullptr;

    // Battlefield list (unused)
    window->v68C = nullptr;
    window->v690 = nullptr;
    // Unknown
    window->v694 = nullptr;

    // Base (CWindow)
    window->m_pos.x = 0;
    window->m_pos.y = 0;
    window->m_size.width = (int)window->size.width;
    window->m_size.height = (int)window->size.height;

    // Changes with HP/SP/MP
    window->hpBarLen = 0.0F;
    window->spBarLen = 0.0F;
    window->mpBarLen = 0.0F;

    // Unknown
    window->v8C = 0;
    window->v90 = 0.0F;

    CTexture::Create(&window->image2, "data/interface", "main_stats_bar_bg.tga", 256, 128);
    CTexture::Create(&window->image3, "data/interface", "main_stats_bar.tga", (int)window->size3.width, (int)window->size3.height);
    CTexture::Create(&window->image4, "data/interface", "main_stats_circle.tga", (int)window->size4.width, (int)window->size4.height);
    CTexture::Create(&window->image5, "data/interface", "main_stats_circle2.tga", 64, 64);
    CTexture::Create(&window->image1, "data/interface", "main_stats_light.tga", 64, 64);

    CButton::Func_0x551860(
        &window->button, window->m_pos.x, window->m_pos.y,
        38, 55, 256, 64, 165, 47, 0,
        "main_stats_pvp_button.tga", 256, 256,
        1,
        0.0F, 1.0F, 0.0F, 0.25F,
        0.0F, 1.0F, 0.25F, 0.5F,
        0.0F, 1.0F, 0.5F, 0.75F,
        0.0F, 1.0F, 0.5F, 0.75F,
        0.0F, 1.0F, 0.75F, 1.0F,
        0);

    CTexture::Create(&window->image6, "data/interface", "main_stats_pvp.tga", 256, 64);
    window->alpha6 = 0.0F;

    // Not implemented
    window->lastMoveTime = 0;
    window->enabled = true;
    //

    Configuration::LoadBattlefieldMoveData();
}

void hook_0x532A23(CStatusMiniBar_EP7* window)
{
    CButton::Draw(&window->button, window->m_pos.x, window->m_pos.y);

    auto x = window->button.pos.x;
    x += window->m_pos.x;
    auto y = window->button.pos.y;
    y += window->m_pos.y;

    auto color = D3DCOLOR_RGBA(255, 255, 255, (int)window->alpha6);
    CTexture::Draw(&window->image6, color, x, y);

    if (!window->message)
        return;

    CMessage::Show(window->message);
}

// See US client 223
int func_0x51E670()
{
    auto it = std::ranges::find_if(g_pvpMoveData, BattlefieldLvInRangeF(g_pPlayerData->level));
    if (it == g_pvpMoveData.end())
        return -1;

    return it->mapId;
}

void func_0x531A74(CStatusMiniBar_EP7* window)
{
    // Returns true if the button is clicked
    if (!CButton::Func_0x550A10(&window->button))
        return;

    if (window->message)
        return;

    auto mapId = func_0x51E670();
    if (mapId == -1)
        return;

    auto block = Static::operator_new(sizeof(CMessage));
    if (!block)
        return;

    std::array<char, 256> mapName{};
    CPlayerData::GetMapName(mapName.data(), mapId);

    auto text = std::format("{}\n{}", mapName.data(), Static::GetMsg(514));
    window->message = CMessage::Init(block, MB_OKCANCEL, 255, 255, 255, text.data(), 0);
}

int hook_0x531A74(CStatusMiniBar_EP7* window)
{
    func_0x531A74(window);

    // Execution must get here no matter what, which is why the rest 
    // of the logic is in separate function.

    if (CButton::Func_0x54FEB0(&window->button, 1))
        return 1;

    if (!window->message)
        return 0;

    auto result = CMessage::DialogResult(window->message);
    switch (result)
    {
    case IDOK:
    {
        GameMovePvPZoneIncoming_EP7 outgoing{};
        CNetwork::Send(&outgoing, sizeof(GameMovePvPZoneIncoming_EP7));
        break;
    }
    case IDCANCEL:
        break;
    default:
        return 1;
    }

    if (window->message)
    {
        CMessage::Hide(window->message);
        Static::operator_delete(window->message);
        window->message = nullptr;
    }

    return 1;
}

void hook_0x5320E6(CStatusMiniBar_EP7* window)
{
    if (window->message)
    {
        CMessage::Hide(window->message);
        Static::operator_delete(window->message);
        window->message = nullptr;
    }

    CTexture::Reset(&window->image6);
    CButton::Reset(&window->button);
}

unsigned u0x532073 = 0x532073;
void __declspec(naked) naked_0x531F97()
{
    __asm
    {
        pushad

        push esi // window
        call hook_0x531F97
        add esp,0x4

        popad

        jmp u0x532073
    }
}

unsigned u0x532A2A = 0x532A2A;
void __declspec(naked) naked_0x532A23()
{
    __asm
    {
        pushad

        push esi // window
        call hook_0x532A23
        add esp,0x4

        popad

        // original
        mov ecx,[esp+0x108]
        jmp u0x532A2A
    }
}

void __declspec(naked) naked_0x531810()
{
    __asm
    {
        pushad

        sub ecx,0x2C

        push ecx // window
        call hook_0x531810
        add esp,0x4

        popad

        ret
    }
}

void __declspec(naked) naked_0x531A74()
{
    __asm
    {
        pushad

        push esi // window
        call hook_0x531A74
        add esp,0x4
        test eax,eax

        popad

        je original

        mov eax,0x1
        pop esi
        pop ecx
        ret

        original:
        xor eax,eax
        pop esi
        pop ecx
        ret
    }
}

unsigned u0x5320F3 = 0x5320F3;
void __declspec(naked) naked_0x5320E6()
{
    __asm
    {
        pushad

        push esi // window
        call hook_0x5320E6
        add esp,0x4

        popad

        // original
        mov eax,[esi+0x40]
        xor edi,edi
        jmp u0x5320F3
    }
}

void hook::main_stats()
{
    util::detour((void*)0x531F97, naked_0x531F97, 6);
    util::detour((void*)0x532A23, naked_0x532A23, 7);
    util::detour((void*)0x531810, naked_0x531810, 9);
    util::detour((void*)0x531A74, naked_0x531A74, 5);
    util::detour((void*)0x5320E6, naked_0x5320E6, 5);

    // Memory allocation (EP7)
    int size = 0x6F8;
    util::write_memory((void*)0x42B23A, &size, 4);

    // Notes: original offsets
    int v6A0 = 0x6A0; // 9C
    int v6A4 = 0x6A4; // A0
    int v6A8 = 0x6A8; // A4
    int v6AC = 0x6AC; // A8
    int v6B0 = 0x6B0; // AC
    int v6B4 = 0x6B4; // B0
    int v6B8 = 0x6B8; // B4
    int v6BC = 0x6BC; // B8
    int v6C0 = 0x6C0; // BC
    int v6C4 = 0x6C4; // C0
    int v6C8 = 0x6C8; // C4
    int v6CC = 0x6CC; // C8
    int v6D0 = 0x6D0; // CC
    int v6D4 = 0x6D4; // D0
    int v6D8 = 0x6D8; // D4
    int v6DC = 0x6DC; // D8
    int v6E0 = 0x6E0; // DC
    int v6E4 = 0x6E4; // E0
    int v6E8 = 0x6E8; // E4
    int v6EC = 0x6EC; // E8
    int v6F0 = 0x6F0; // EC
    int v6F4 = 0x6F4; // F0

    // CStatusMiniBar member offsets (0x5322A0)

    util::write_memory((void*)0x5322E1, &v6B4, 4);
    util::write_memory((void*)0x5322F7, &v6B0, 4);
    util::write_memory((void*)0x5323DC, &v6CC, 4);
    util::write_memory((void*)0x5323EB, &v6C8, 4);
    util::write_memory((void*)0x532427, &v6CC, 4);
    util::write_memory((void*)0x532436, &v6C8, 4);
    util::write_memory((void*)0x53251B, &v6DC, 4);
    util::write_memory((void*)0x53252A, &v6D8, 4);
    util::write_memory((void*)0x53256C, &v6DC, 4);
    util::write_memory((void*)0x53257B, &v6D8, 4);
    util::write_memory((void*)0x532660, &v6EC, 4);
    util::write_memory((void*)0x53266F, &v6E8, 4);
    util::write_memory((void*)0x5326B1, &v6EC, 4);
    util::write_memory((void*)0x5326C0, &v6E8, 4);
    util::write_memory((void*)0x5326F8, &v6D0, 4);
    util::write_memory((void*)0x532709, &v6D4, 4);
    util::write_memory((void*)0x53275D, &v6E0, 4);
    util::write_memory((void*)0x53276E, &v6E4, 4);
    util::write_memory((void*)0x5327B8, &v6F0, 4);
    util::write_memory((void*)0x5327C9, &v6F4, 4);
    util::write_memory((void*)0x532867, &v6B8, 4);
    util::write_memory((void*)0x532878, &v6BC, 4);
    util::write_memory((void*)0x5328FD, &v6C4, 4);
    util::write_memory((void*)0x53290C, &v6C0, 4);
    util::write_memory((void*)0x532928, &v6C4, 4);
    util::write_memory((void*)0x532937, &v6C0, 4);
    util::write_memory((void*)0x532972, &v6C4, 4);
    util::write_memory((void*)0x532981, &v6C0, 4);
    util::write_memory((void*)0x5329CD, &v6C4, 4);
    util::write_memory((void*)0x5329DC, &v6C0, 4);
}
