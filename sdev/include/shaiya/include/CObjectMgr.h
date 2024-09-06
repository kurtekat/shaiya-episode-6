#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/SSyncHeap.h>

namespace shaiya
{
    struct AdminNotice;
    struct CDead;
    struct CItem;
    struct CloneUser;
    struct CMob;
    struct CNpc;
    struct CQuest;
    struct CSkill;
    struct CTrap;
    struct CUser;

    #pragma pack(push, 1)
    // 00411260 ctor
    struct CObjectMgr
    {
        PAD(24);
        SSyncHeap<CUser> users;          //0x18
        SSyncHeap<CMob> mobs;            //0x3C
        SSyncHeap<CNpc> npcs;            //0x60
        SSyncHeap<CItem> items;          //0x84
        SSyncHeap<CDead> dead;           //0xA8
        SSyncHeap<CTrap> traps;          //0xCC
        SSyncHeap<CQuest> quests;        //0xF0
        SSyncHeap<CSkill> skills;        //0x114
        SSyncHeap<AdminNotice> notices;  //0x138
        SSyncHeap<CloneUser> clones;     //0x15C
        // object size: 36 (0x24)
        SSyncHeap<void> unknown;         //0x180
        // 0x1A4

        static void FreeItem(CItem* item/*edi*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectMgr) == 0x1A4);
    static auto g_pObjectMgr = (CObjectMgr*)0x10A239C; // 0x587964
}
