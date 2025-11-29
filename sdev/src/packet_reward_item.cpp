#include <chrono>
#include <util/util.h>
#include <shaiya/include/network/TP_MAIN.h>
#include <shaiya/include/network/game/outgoing/1F00.h>
#include "include/main.h"
#include "include/shaiya/CGameData.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/NetworkHelper.h"
#include "include/shaiya/RewardItem.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

/// <summary>
/// See the docs for a list of supported clients.
/// </summary>

namespace packet_reward_item
{
    void handler(CUser* user, TP_MAIN* packet)
    {
        using namespace std::chrono_literals;

        switch (packet->opcode)
        {
        case 0x1F04:
        {
            if (!g_rewardItemCount)
                return;

            auto it = g_rewardItemProgress.find(user->billingId);
            if (it == g_rewardItemProgress.end())
                return;

            auto& progress = it->second;
            if (!progress.completed)
                return;

            auto& item = g_rewardItemList[progress.index];
            auto itemInfo = CGameData::GetItemInfo(item.type, item.typeId);
            if (!itemInfo)
                return;

            if (!CUser::ItemCreate(user, itemInfo, item.count))
            {
                // The client will output system message 7188 inside a message box
                GameRewardItemGetResultOutgoing outgoing{};
                outgoing.result = GameRewardItemGetResult::Failure;
                NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemGetResultOutgoing));
            }
            else
            {
                GameRewardItemGetResultOutgoing outgoing{};
                outgoing.result = GameRewardItemGetResult::Success; 
                outgoing.messageNumber = 7192;
                NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemGetResultOutgoing));

                ++progress.index;

                if (progress.index >= g_rewardItemCount)
                {
                    auto minutes = g_rewardItemList[0].minutes;
                    auto ms = minutes * 60000 + 15000;
                    auto now = std::chrono::system_clock::now();

                    progress.index = 0;
                    progress.timeout = now + std::chrono::milliseconds(ms);
                    progress.completed = false;

                    GameRewardItemListIndexOutgoing outgoing{};
                    NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemListIndexOutgoing));
                }
                else
                {
                    auto minutes = g_rewardItemList[progress.index].minutes;
                    auto ms = minutes * 60000 + 15000;
                    auto now = std::chrono::system_clock::now();

                    progress.timeout = now + std::chrono::milliseconds(ms);
                    progress.completed = false;

                    GameRewardItemListIndexOutgoing outgoing{};
                    outgoing.index = progress.index;
                    NetworkHelper::Send(user, &outgoing, sizeof(GameRewardItemListIndexOutgoing));
                }
            }

            break;
        }
        default:
            SConnection::Close(user, 9, 0);
            break;
        }
    }
}

unsigned u0x474F00 = 0x474F00;
unsigned u0x474F3A = 0x474F3A;
void __declspec(naked) naked_0x474EFB()
{
    __asm
    {
        cmp eax,0x1F00
        je case_0x1F00
        // original
        cmp eax,0xF100
        jmp u0x474F00

        case_0x1F00:
        pushad

        push edi // packet
        push ebx // user
        call packet_reward_item::handler
        add esp,0x8

        popad

        jmp u0x474F3A
    }
}

unsigned u0x4EC850 = 0x4EC850;
unsigned u0x47BDA7 = 0x47BDA7;
void __declspec(naked) naked_0x47BDA2()
{
    __asm
    {
        call u0x4EC850

        pushad

        push ebp // user
        call RewardItemEvent::send
        add esp,0x4

        popad

        jmp u0x47BDA7
    }
}

void hook::packet_reward_item()
{
    // CUser::PacketProcessing
    util::detour((void*)0x474EFB, naked_0x474EFB, 5);
    // CUser::PacketUserDBChar case 0x407
    util::detour((void*)0x47BDA2, naked_0x47BDA2, 5);
}
