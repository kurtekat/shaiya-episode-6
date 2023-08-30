#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        PAD(36);
        UINT32 joinCount;  //0x24
        CharId leaderId;   //0x28
        CUser* leader;     //0x2C
        // 0x30
        Array<CharId, 7> userList;
        // 0x4C
        PAD(28);
        // 0x68
    };
    #pragma pack(pop)
}
