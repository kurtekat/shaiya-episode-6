#pragma once
#include <shaiya/common.h>
#include <shaiya/include/SVector.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Npc
    {
        UINT16 type;     //0x00
        UINT16 typeId;   //0x02
        UINT32 shape;    //0x04
        PAD(8);
        UINT32 country;  //0x10
        char name[29];   //0x14
        PAD(243);
        // 0x124
    };

    struct NpcGate
    {
        UINT16 mapdId;       //0x00
        PAD(2);
        SVector outPos;      //0x04
        char location[256];  //0x10
        UINT32 cost;         //0x110
        // 0x114
    };

    struct NpcGateKeeper
    {
        UINT16 type;      //0x00
        UINT16 typeId;    //0x02
        UINT32 shape;     //0x04
        PAD(8);
        UINT32 country;   //0x10
        char name[29];    //0x14
        PAD(243);
        NpcGate gate[3];  //0x124
        // 0x460
    };

    struct NpcItem
    {
        UINT8 type;
        UINT8 typeId;
    };

    struct NpcShop
    {
        UINT16 type;       //0x00
        UINT16 typeId;     //0x02
        UINT32 shape;      //0x04
        PAD(8);
        UINT32 country;    //0x10
        char name[29];     //0x14
        PAD(243);
        UINT32 shopType;   //0x124
        UINT32 itemCount;  //0x128
        NpcItem* item;     //0x12C
        // 0x130
    };

    template<typename T>
    struct CNpcData
    {
        static T GetNpc(int npcType/*ecx*/, int npcId/*eax*/);
    };

    template<typename T>
    T CNpcData<T>::GetNpc(int npcType/*ecx*/, int npcId/*eax*/)
    {
        Address u0x424450 = 0x424450;

        __asm
        {
            mov eax,npcId
            mov ecx,npcType
            call u0x424450
        }
    }
    #pragma pack(pop)
}
