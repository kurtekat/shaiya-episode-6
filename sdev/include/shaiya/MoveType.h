#pragma once
#include <cstdint>

namespace shaiya
{
    enum struct MoveType : int32_t
    {
        Default,
        GateKeeper = 1,
        Portal = 1,
        SavePoint,
        RecallRune,
        PartyCall,
        PartyMove,
        // itemId 100169 (EP5)
        MoveWar,
        // custom
        MoveTown,
        MovePvPZone,
        //
        MoveMapId200 = 10,
        MoveChar = 0xF904,
        MoveCharZone = 0xF905,
        MoveParty = 0xF90C,
        MoveTo = 0xFA09,
        MoveZone = 0xFA0A,
        MoveMap = 0xFA11,
        MoveInsZone = 0xFA12
    };
}
