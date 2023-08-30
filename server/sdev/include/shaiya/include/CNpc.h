#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    FWDDECL Npc;
    FWDDECL CMap;

    #pragma pack(push, 1)
    struct CNpc
    {
        SNode node;     //0x00
        SVector pos;    //0x08
        ULONG id;       //0x14
        CMap* map;      //0x18
        PAD(24);
        UINT32 type;    //0x34
        UINT32 typeId;  //0x38
        PAD(20);
        // cast this
        Npc* npcData;   //0x50
        //
    };
    #pragma pack(pop)
}
