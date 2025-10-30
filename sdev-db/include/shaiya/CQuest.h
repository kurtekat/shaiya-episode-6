#include <shaiya/include/common.h>
#include "SaveType.h"
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CQuest : SNode
    {
        SaveType saveType;  //0x08
        uint16_t questId;   //0x0C
        bool success;       //0x0E
        PAD(1);
        uint16_t delay;     //0x10
        uint8_t count1;     //0x12
        uint8_t count2;     //0x13
        uint8_t count3;     //0x14
        PAD(3);
        // 0x18
    };
    #pragma pack(pop)

    static_assert(sizeof(CQuest) == 0x18);
}
