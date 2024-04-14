#pragma once
#include <array>
#pragma warning(disable: 4005)
#define DIRECTINPUT_VERSION 0x800
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <dxgi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d2d1.h>
#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <dwrite.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    template<class T, int N>
    using Array = std::array<T, N>;

    typedef UINT8* Packet;
    typedef Array<char, 21> CharName;

    enum struct AuthStatus : UINT32
    {
        AdminA = 1,
        AdminB,
        AdminC,
        AdminD,
        AdminE,
        None = 11
    };

    enum struct Country : UINT8
    {
        Light,
        Fury
    };

    enum struct Family : UINT8
    {
        Human,
        Elf,
        Deatheater,
        Vail
    };

    enum struct Grow : UINT8
    {
        Easy,
        Normal,
        Hard,
        Ultimate
    };

    enum struct Job : UINT8
    {
        AttackFighter,
        DefenseFighter,
        PatrolRogue,
        ShootRogue,
        AttackMage,
        DefenseMage
    };

    enum struct Sex : UINT8
    {
        Male,
        Female
    };

    enum struct ShapeType : UINT8
    {
        None,
        Chicken = 4,
        Dog,
        Horse,
        Pig,
        Fox = 10,
        Wolf,
        Knight,
        Stealth,
        Disguise = 100,
        Transformation = 102,
    };
}
