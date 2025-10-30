#pragma once
#include <shaiya/include/common.h>
#include "SSyncHeap.h"

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
        uint32_t allocUserIdCount;          //0x00
        uint32_t allocItemIdCount;          //0x04
        uint32_t allocMobIdCount;           //0x08
        uint32_t allocNpcIdCount;           //0x0C
        uint32_t allocSkillIdCount;         //0x10
        uint32_t allocTrapIdCount;          //0x14
        SSyncHeap<CUser> userHeap;          //0x18
        SSyncHeap<CMob> mobHeap;            //0x3C
        SSyncHeap<CNpc> npcHeap;            //0x60
        SSyncHeap<CItem> itemHeap;          //0x84
        SSyncHeap<CDead> deadHeap;          //0xA8
        SSyncHeap<CTrap> trapHeap;          //0xCC
        SSyncHeap<CQuest> questHeap;        //0xF0
        SSyncHeap<CSkill> skillHeap;        //0x114
        SSyncHeap<AdminNotice> noticeHeap;  //0x138
        SSyncHeap<CloneUser> cloneHeap;     //0x15C
        // not implemented
        SSyncHeap<void> heap180;            //0x180
        // 0x1A4

        static void FreeItem(CItem* item/*edi*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CObjectMgr) == 0x1A4);
    static auto g_pObjectMgr = (CObjectMgr*)0x10A239C; // 0x587964
}
