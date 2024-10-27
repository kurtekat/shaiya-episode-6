#pragma once
#include <cstdint>
#include <shaiya/include/common/ItemEffect.h>

namespace shaiya
{
    struct CUser;
    struct SVector;

    struct Helpers
    {
        static int GetFreeItemSlot(CUser* user, uint8_t bag);
        static bool ItemRemove(CUser* user, uint8_t bag, uint8_t slot, uint8_t count);
        static bool ItemRemove(CUser* user, uint32_t itemId, uint8_t count);
        static bool ItemRemove(CUser* user, ItemEffect effect, uint8_t count);

        static bool HasApplySkill(CUser* user, int skillId, int skillLv);

        static void SendMessageToServer(CUser* sender, const char* message);
        static void SendMessageToServer(const char* senderName, const char* message);
        static void SendNotice(const char* message);
        static void SendNoticeTo(CUser* user, const char* message);
        static void SendNoticeTo(uint32_t charId, const char* message);
        static void SendNoticeTo(const char* charName, const char* message);

        static void Send(CUser* user, void* packet, int length);
        static void SendDBAgent(void* packet, int length);
        static void SendGameLog(void* packet, int length);
        static void SendSession(void* packet, int length);
        static void SendUserLog(void* packet, int length);

        static void SetMovePosition(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay);
        static void SetMovePosition(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay);
        static bool Teleport(CUser* user, int mapId, float x, float y, float z, int recallType, ULONG delay);
        static bool Teleport(CUser* user, int mapId, SVector* pos, int recallType, ULONG delay);
    };
}
