#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    enum struct MiniGameStatus : int32_t
    {
        GameExit,
        GameEnter,
        SlotStart,
        CardStart,
        CardNext
    };

    #pragma pack(push, 1)
    struct CMiniGame
    {
        MiniGameStatus status;     //0x00
        int32_t npcHouseId;        //0x04
        int32_t bettingMoney;      //0x08
        int32_t bettingSlotCount;  //0x0C
        int32_t changeMoney;       //0x10
        int32_t cardGameGrade;     //0x14
        int32_t npcCard;           //0x18
        CUser* user;               //0x1C
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(CMiniGame) == 0x20);
}
