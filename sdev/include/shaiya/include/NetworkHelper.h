#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    class NetworkHelper
    {
    public:

        static void SendMessageToServer(CUser* sender, const char* message);
        static void SendMessageToServer(const char* senderName, const char* message);
        static void SendNotice(const char* message);
        static void SendNoticeTo(CUser* user, const char* message);
        static void SendNoticeTo(ULONG charId, const char* message);
        static void SendNoticeTo(const char* charName, const char* message);

        static void Send(CUser* user, void* packet, int length);
        static void SendDBAgent(void* packet, int length);
        static void SendGameLog(void* packet, int length);
        static void SendSession(void* packet, int length);
        static void SendUserLog(void* packet, int length);

        static void SendDBAgentItemCraftName(CUser* user, CItem* item, int bag, int slot);
        static void SendDBAgentItemGems(CUser* user, CItem* item, int bag, int slot);
    };
}
