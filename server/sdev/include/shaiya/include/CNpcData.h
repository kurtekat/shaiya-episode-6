#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SVector.h>

namespace shaiya
{
    typedef Array<char, 256> NpcName;
    typedef Array<char, 256> NpcGateDesc;

    #pragma pack(push, 1)
    enum struct NpcCountry : UINT32
    {
        Neutral,
        Light,
        Fury
    };

    enum struct NpcType : UINT16
    {
        Merchant = 1,
        GateKeeper,
        Blacksmith,
        VetManager,
        GamblingHouse,
        Warehouse,
        Normal,
        Guard,
        Animal,
        Apprentice,
        GuildMaster,
        Dead,
        SkillReset
    };

    struct Npc
    {
        NpcType type;        //0x00
        UINT16 typeId;       //0x02
        UINT32 shape;        //0x04
        PAD(8);
        NpcCountry country;  //0x10
        NpcName name;        //0x14
        // 0x114
        PAD(16);
        // 0x124
    };

    struct NpcGate
    {
        UINT16 mapId;      //0x00
        PAD(2);
        SVector pos;       //0x04
        NpcGateDesc desc;  //0x10
        UINT32 price;      //0x110
        // 0x114
    };

    struct NpcGateKeeper
    {
        Npc npc;
        // 0x124
        Array<NpcGate, 3> gate;
        // 0x460
    };

    struct NpcItem
    {
        UINT8 type;
        UINT8 typeId;
    };

    struct NpcShop
    {
        Npc npc;            //0x00
        UINT32 shopType;    //0x124
        UINT32 itemCount;   //0x128
        NpcItem* itemList;  //0x12C
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
