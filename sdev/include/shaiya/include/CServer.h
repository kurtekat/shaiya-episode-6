#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/CClientToDBAgent.h"
#include "include/shaiya/include/CClientToGameLog.h"
#include "include/shaiya/include/CClientToMgr.h"
#include "include/shaiya/include/CLogConnection.h"
#include "include/shaiya/include/CObjectMgr.h"
#include "include/shaiya/include/CMonitorNet.h"
#include "include/shaiya/include/CWorld.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CServer
    {
        PAD(20808);                            //0x109CED0
        CWorld world;                          //0x10A2018  0x5148
        CObjectMgr objectMgr;                  //0x10A239C  0x54CC
        CClientToMgr clientToMgr;              //0x10A2540  0x5670
        CClientToDBAgent clientToDBAgent;      //0x10A2628  0x5758
        CLogConnection clientToLog;            //0x10A2710  0x5840
        CClientToGameLog clientToGameLog;      //0x10A2818  0x5948
        CMonitorNet monitorNet;                //0x10A28F8  0x5A28
        //
    };
    #pragma pack(pop)

    static auto g_Server = (CServer*)0x109CED0;
}
