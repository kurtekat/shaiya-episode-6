#pragma once
#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    template<class T, int N>
    using Array = std::array<T, N>;

    typedef UINT8* Packet;

    typedef ULONG CharId;
    typedef Array<char, 21> CharName;
    typedef Array<char, 51> ShapeName;

    typedef Array<UINT32, 6> Clothes;

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
        DeathEater,
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
