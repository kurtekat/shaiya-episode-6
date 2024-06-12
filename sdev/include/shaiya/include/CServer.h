#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SConnection.h>
#include "include/shaiya/include/CClientToDBAgent.h"
#include "include/shaiya/include/CClientToGameLog.h"
#include "include/shaiya/include/CClientToMgr.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CObjectMgr.h"
#include "include/shaiya/include/CMonitorNet.h"
#include "include/shaiya/include/CWorld.h"
#include "include/shaiya/include/Obelisk.h"
#include "include/shaiya/include/SLog.h"
#include "include/shaiya/include/SThread.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CServer
    {
        PAD(20808);                        //0x109CED0
        CWorld world;                      //0x10A2018  0x5148
        CObjectMgr objectMgr;              //0x10A239C  0x54CC
        CClientToMgr clientToMgr;          //0x10A2540  0x5670
        CClientToDBAgent clientToDBAgent;  //0x10A2628  0x5758
        CLogConnection clientToLog;        //0x10A2710  0x5840
        CClientToGameLog clientToGameLog;  //0x10A2818  0x5948
        CMonitorNet monitorNet;            //0x10A28F8  0x5A28
        SThread thread;                    //0x10A2980  0x5AB0
        PAD(576);                          //0x10A29A8  0x5AD8
        PAD(80);                           //0x10A2BE8  0x5D18
        // 0x10A2C38  0x5D68
        Array<ObeliskZone, 64> obeliskZoneList;
        // 0x18C6E38  0x829F68
        Array<ObeliskBoss, 64> obeliskBossList;
        // 0x3F93038
    };
    #pragma pack(pop)

    static auto g_Server = (CServer*)0x109CED0;
}
