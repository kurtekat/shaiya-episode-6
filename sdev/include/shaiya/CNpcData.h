#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    template<typename T>
    struct CNpcData
    {
        static T GetNpc(int npcType/*ecx*/, int npcTypeId/*eax*/);
    };

    template<typename T>
    T CNpcData<T>::GetNpc(int npcType/*ecx*/, int npcTypeId/*eax*/)
    {
        unsigned u0x424450 = 0x424450;

        __asm
        {
            mov eax,npcTypeId
            mov ecx,npcType
            call u0x424450
        }
    }
}
