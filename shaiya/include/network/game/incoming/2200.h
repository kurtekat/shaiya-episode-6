#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

// CUser::PacketComm (community)

namespace shaiya
{
    #pragma pack(push, 1)
    struct FriendAddIncoming
    {
        UINT16 opcode{ 0x2202 };
        CharArray<21> charName;

        FriendAddIncoming() = default;

        FriendAddIncoming(const char* charName)
            : charName{}
        {
            StringCbCopyA(this->charName.data(), this->charName.size(), charName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendRemoveIncoming
    {
        UINT16 opcode{ 0x2205 };
        ULONG charId;

        FriendRemoveIncoming() = default;

        FriendRemoveIncoming(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct FriendSaveMemoIncoming
    {
        UINT16 opcode{ 0x2206 };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        CharArray<51> memo;

        FriendSaveMemoIncoming() = default;

        FriendSaveMemoIncoming(ULONG charId, const char* memo)
            : charId(charId), memoLength(0), memo{}
        {
            StringCbCopyA(this->memo.data(), this->memo.size(), memo);
            this->memoLength = static_cast<UINT8>(std::strlen(this->memo.data()) + 1);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockAddIncoming
    {
        UINT16 opcode{ 0x2209 };
        CharArray<21> charName;

        BlockAddIncoming() = default;

        BlockAddIncoming(const char* charName)
            : charName{}
        {
            StringCbCopyA(this->charName.data(), this->charName.size(), charName);
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockRemoveIncoming
    {
        UINT16 opcode{ 0x220A };
        ULONG charId;

        BlockRemoveIncoming() = default;

        BlockRemoveIncoming(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct BlockSaveMemoIncoming
    {
        UINT16 opcode{ 0x220B };
        ULONG charId;
        // w/ null terminator
        UINT8 memoLength;
        CharArray<51> memo;

        BlockSaveMemoIncoming() = default;

        BlockSaveMemoIncoming(ULONG charId, const char* memo)
            : charId(charId), memoLength(0), memo{}
        {
            StringCbCopyA(this->memo.data(), this->memo.size(), memo);
            this->memoLength = static_cast<UINT8>(std::strlen(this->memo.data()) + 1);
        }
    };
    #pragma pack(pop)
}
