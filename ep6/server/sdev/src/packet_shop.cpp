#include <array>
#include <thread>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/include/CClientToMgr.h>
#include <shaiya/include/CUser.h>
using namespace shaiya;

unsigned g_nPayLetterEnable = 0x58799C;

// CClientToMgr::OnRecv
// ebx = packet

#pragma pack(push, 1)
// this packet is sent from ps_session at address 0x402EF0
// CClientToMgr::OnRecv handles it at address 0x4069CB and returns to a loop at address 0x4ECF40
// the result is g_nPayLetterEnable being set to false because the PayLetter server is not implemented
struct PacketBuffer0105
{
    ULONG u0x00;
    void* p0x04;
    ULONG u0x08;
    ULONG u0x0C;
    bool enable;   // ebx+0x02
    // 0x11
};

// billing packets

struct PacketBuffer1B02
{
    ULONG u0x00;
    void* p0x04;
    ULONG u0x08;
    ULONG u0x0C;
    ULONG userUid;         // ebx+0x02
    ULONG charId;          // ebx+0x06
    UINT8 result;          // ebx+0x0A
    char itemKey[25];      // ebx+0x0B
    UINT32 u0x32;          // ebx+0x24
    char orderNumber[16];  // ebx+0x28
    // user->id
    ULONG userId;          // ebx+0x38
    UINT32 u0x4A;          // ebx+0x3C
    UINT32 itemCount;      // ebx+0x40
    // 0x52
};

struct PacketBuffer1B03
{
    ULONG u0x00;
    void* p0x04;
    ULONG u0x08;
    ULONG u0x0C;
    ULONG userUid;         // ebx+0x02
    char productCode[21];  // ebx+0x06
    char targetName[21];   // ebx+0x1B
    UINT32 usePoint;       // ebx+0x30
    UINT32 points;         // ebx+0x34
    // 0x46
};
#pragma pack(pop)

namespace packet_shop
{
    using namespace shaiya;

    void raise_event_0x105(bool enable)
    {
        PacketBuffer0105 packet{};
        packet.u0x00 = 0;
        packet.p0x04 = &packet.u0x0C;
        packet.u0x08 = 0;
        // 00 00 05 01
        packet.u0x0C = 0x1050000;
        packet.enable = enable;
        CClientToMgr::OnRecv(&packet);
    }

    void raise_event_0x1B02(CUser* user)
    {
        PacketBuffer1B02 packet{};
        packet.u0x00 = 0;
        packet.p0x04 = &packet.u0x0C;
        packet.u0x08 = 0;
        // 00 00 02 1B
        packet.u0x0C = 0x1B020000;
        packet.userUid = user->userUid;
        packet.charId = user->charId;
        CClientToMgr::OnRecv(&packet);
    }

    void raise_event_0x1B03(CUser* user, const char* targetName, const char* productCode, std::uint32_t usePoint)
    {
        PacketBuffer1B03 packet{};
        packet.u0x00 = 0;
        packet.p0x04 = &packet.u0x0C;
        packet.u0x08 = 0;
        // 00 00 03 1B
        packet.u0x0C = 0x1B030000;
        packet.userUid = user->userUid;
        strncpy_s(packet.productCode, productCode, sizeof(packet.productCode));
        strncpy_s(packet.targetName, targetName, sizeof(packet.targetName));
        packet.usePoint = usePoint;
        packet.points = user->points;
        CClientToMgr::OnRecv(&packet);
    }

    void purchase_item_async(CUser* user)
    {
        std::thread([=] {
            raise_event_0x1B02(user);
            }).detach();
    }

    void send_present_async(CUser* user, const char* targetName, const char* productCode, std::uint32_t usePoint)
    {
        std::thread([=] {
            raise_event_0x1B03(user, targetName, productCode, usePoint);
            }).detach();
    }

    void set_pay_letter_enable_async(bool enable)
    {
        std::thread([=] {
            raise_event_0x105(enable);
            }).detach();
    }
}

unsigned u0x488D5F = 0x488D5F;
void __declspec(naked) naked_0x48876F()
{
    __asm
    {
        pushad

        push edi // user
        call packet_shop::purchase_item_async
        add esp,0x4

        popad

        // original
        jmp u0x488D5F
    }
}

unsigned u0x47D163 = 0x47D163;
void __declspec(naked) naked_0x47D151()
{
    __asm 
    {
        xor ebp,ebp
        add ebx,0x5998
        mov eax,[esi+0x6]
        // user->points
        mov[ecx+0x5AC0],eax
        jmp u0x47D163
    }
}

void __declspec(naked) naked_0x488A80()
{
    __asm
    {
        pushad

        mov eax,[esp+0x174]
        push eax // usePoint
        lea eax,[esp+0x14E]
        push eax // productCode
        lea eax,[esp+0x167]
        push eax // targetName
        push edi // user
        call packet_shop::send_present_async
        add esp,0x10

        popad

        // original
        jmp u0x488D5F
    }
}

unsigned u0x47D3DC = 0x47D3DC;
void __declspec(naked) naked_0x47D3D7()
{
    __asm
    {
        // user->disableShop
        mov [ebx+0x5AC4],0x0
        // original
        mov al,0x1
        pop edi
        pop ebp
        pop ebx

        jmp u0x47D3DC
    }
}

void hook::packet_shop()
{
    // CUser::PacketShop
    util::detour((void*)0x48876F, naked_0x48876F, 5);
    // CUser::PacketUserDBPoint
    util::detour((void*)0x47D151, naked_0x47D151, 6);
    // CUser::PacketShop
    util::detour((void*)0x488A80, naked_0x488A80, 5);
    // CUser::PacketUserDBPoint
    util::detour((void*)0x47D3D7, naked_0x47D3D7, 5);

    // fake a 0x105 event
    packet_shop::set_pay_letter_enable_async(true);
}
