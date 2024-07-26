#include <array>
#include <format>
#include <map>
#include <string>
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <util/util.h>
#include "include/main.h"
#include "include/static.h"
#include "include/shaiya/include/CCharacter.h"
#include "include/shaiya/include/CDataFile.h"
#include "include/shaiya/include/ItemInfo.h"
#include <shaiya/include/item/ItemType.h>
using namespace shaiya;

namespace vehicle
{
    struct Vehicle
    {
        int model;
        int bone1;
        int bone2;
        std::string wavFileName;
    };

    std::vector<Vehicle> g_vehicles{};

    void init()
    {
        for (int i = 1; i <= 255; ++i)
        {
            auto itemInfo = CDataFile::GetItemInfo(int(ItemType::Vehicle), i);
            if (!itemInfo)
                continue;

            if (!itemInfo->reqRec)
                continue;

            Vehicle vehicle{};
            vehicle.model = itemInfo->vehicleModel;
            vehicle.bone1 = itemInfo->reqRec;
            vehicle.bone2 = itemInfo->reqInt;
            // e.g., vehicle_model033.wav
            vehicle.wavFileName = std::format("vehicle_model{:03d}.wav", vehicle.model);
            g_vehicles.push_back(vehicle);
        }
    }

    int play_wav(CCharacter* user)
    {
        auto model = user->vehicleModel;
        if (model <= 32)
            return 1;

        auto vehicle = std::find_if(g_vehicles.begin(), g_vehicles.end(), [&model](const auto& vehicle) {
            return vehicle.model == model;
            });

        if (vehicle != g_vehicles.end())
        {
            if (Static::PlayWav(vehicle->wavFileName.c_str(), &user->pos, 1000.0f, false))
                return 0;
        }

        Static::PlayWav("ef_dmg_transf01.wav", &user->pos, 1000.0f, false);
        return 0;
    }

    int get_main_bone(int model)
    {
        auto vehicle = std::find_if(g_vehicles.begin(), g_vehicles.end(), [&model](const auto& vehicle) {
            return vehicle.model == model;
            });

        if (vehicle == g_vehicles.end())
            return 0;

        return vehicle->bone1;
    }

    int get_rear_bone(int model)
    {
        auto vehicle = std::find_if(g_vehicles.begin(), g_vehicles.end(), [&model](const auto& vehicle) {
            return vehicle.model == model;
            });

        if (vehicle == g_vehicles.end())
            return 0;

        if (!vehicle->bone1)
            return 0;

        return vehicle->bone2;
    }

    int set_solo_bone(int model)
    {
        // models coded in game.exe
        if (model == 31 || model == 32)
        {
            uint8_t bone = 0x03;
            std::memcpy((void*)0x414B13, &bone, 1);
            std::memcpy((void*)0x414B67, &bone, 1);
            return 1;
        }

        uint8_t main = get_main_bone(model);

        if (!main)
            return 0;

        std::memcpy((void*)0x414B13, &main, 1);
        std::memcpy((void*)0x414B67, &main, 1);
        return 1;
    }

    int set_dual_bone(int model)
    {
        // models coded in game.exe
        if (model == 14 || model == 15 || model == 21)
        {
            uint8_t rear = 0x44;
            uint8_t main = 0x31;

            // rear bone
            std::memcpy((void*)0x4137A2, &rear, 1);
            std::memcpy((void*)0x4137F6, &rear, 1);

            // main bone
            std::memcpy((void*)0x413847, &main, 1);
            std::memcpy((void*)0x41389B, &main, 1);
            return 1;
        }

        uint8_t main = get_main_bone(model);
        uint8_t rear = get_rear_bone(model);

        if (!main || !rear)
            return 0;

        // rear bone
        std::memcpy((void*)0x4137A2, &rear, 1);
        std::memcpy((void*)0x4137F6, &rear, 1);

        // main bone
        std::memcpy((void*)0x413847, &main, 1);
        std::memcpy((void*)0x41389B, &main, 1);
        return 1;
    }
}

unsigned u0x414626 = 0x414626;
unsigned u0x4149F1 = 0x4149F1;
unsigned u0x4146FD = 0x4146FD;
unsigned u0x414AFF = 0x414AFF;
unsigned u0x414D85 = 0x414D85;
void __declspec(naked) naked_0x4145FE()
{
    __asm
    {
        // original
        cmp al, 0x0C
        je _0x4149F1
        cmp al, 0x0D
        je _0x4149F1
        movzx ecx, al
        cmp ecx, 0x1F
        jge _label
        cmp al, 0x7
        jne _0x4146FD

        // continue
        jmp u0x414626

        _0x4146FD :
        jmp u0x4146FD

            _0x4149F1 :
        jmp u0x4149F1

            _label :
        pushad

            push ecx // model
            call vehicle::set_solo_bone
            add esp, 0x4
            test eax, eax

            popad

            jne _0x414AFF

            // default
            jmp u0x414D85

            _0x414AFF :
        jmp u0x414AFF
    }
}

unsigned u0x413010 = 0x413010;
unsigned u0x41378E = 0x41378E;
unsigned u0x4132AB = 0x4132AB;
void __declspec(naked) naked_0x412FF0()
{
    __asm
    {
        // original
        cmp al, 0x0E
        je _label
        cmp al, 0x0F
        je _label
        cmp al, 0x15
        je _label

        // custom >= 33
        movzx ecx, al
        cmp ecx, 0x21
        jge _label
        cmp al, 0x11
        jne _0x4132AB

        // continue
        jmp u0x413010

        _0x4132AB :
        jmp u0x4132AB

            _label :
        pushad

            push ecx // model
            call vehicle::set_dual_bone
            add esp, 0x4
            test eax, eax

            popad

            jne _0x41378E

            // default
            jmp u0x414D85

            _0x41378E :
        jmp u0x41378E
    }
}

unsigned u0x74A350 = 0x74A350;
unsigned u0x4315F9 = 0x4315F9;
void __declspec(naked) naked_0x4315F4()
{
    __asm
    {
        pushad

        call vehicle::init

        popad

        // original
        push u0x74A350
        jmp u0x4315F9
    }
}

unsigned u0x41A912 = 0x41A912;
unsigned u0x41A806 = 0x41A806;
void __declspec(naked) naked_0x41A7FF()
{
    __asm
    {
        pushad

        push esi // user
        call vehicle::play_wav
        add esp, 0x4
        test eax, eax

        popad

        je _0x41A912

        // original
        movzx eax, byte ptr[esi + 0x2B8]
        jmp u0x41A806

        _0x41A912 :
        jmp u0x41A912
    }
}

void hook::vehicle()
{
    // allocate vehicles
    util::detour((void*)0x4315F4, naked_0x4315F4, 5);
    // solo vehicles
    util::detour((void*)0x4145FE, naked_0x4145FE, 8);
    // dual vehicles
    util::detour((void*)0x412FF0, naked_0x412FF0, 8);
    // play .wav by model
    util::detour((void*)0x41A7FF, naked_0x41A7FF, 7);
}
