#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SSyncHeap.h"

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
        // to-do: count of what?
        UINT32 userCount;                   //0x00
        UINT32 itemCount;                   //0x04
        UINT32 mobCount;                    //0x08
        UINT32 npcCount;                    //0x0C
        UINT32 skillCount;                  //0x10
        UINT32 trapCount;                   //0x14
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
