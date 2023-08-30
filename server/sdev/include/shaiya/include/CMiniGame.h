#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    enum struct MiniGameState : UINT32
    {
        GameExit,
        GameEnter,
        SlotStart,
        CardStart,
        CardNext
    };

    struct CMiniGame
    {
        MiniGameState state;  //0x00
        UINT32 houseId;       //0x04
        UINT32 bettingMoney;  //0x08
        UINT32 numBets;       //0x0C
        UINT32 changeMoney;   //0x10
        UINT32 grade;         //0x14
        UINT32 npcCard;       //0x18
        CUser* user;          //0x1C
        // 0x20
    };
    #pragma pack(pop)
}
