#pragma once
#pragma warning(disable: 28159) // GetTickCount
//#define SHAIYA_EP6
//#define SHAIYA_EP6_3
//#define SHAIYA_EP6_3_PT
//#define SHAIYA_EP6_4_PT

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_COMMON
#endif

#if \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_3_PT
#define SHAIYA_EP6_3_COMMON
#endif

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_0511
#endif

#if \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_DURATION
#endif

#if \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_EFFECT
#endif

#if \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_LIST
#endif

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_SET
#endif

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3 || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_QUEST_RESULT
#endif

#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

template<class T, int N>
using Array = std::array<T, N>;

typedef unsigned Address;
typedef ULONG TickCount;

namespace shaiya
{
    #ifdef SHAIYA_EP6_4_PT
    constexpr int item_list_size = 17;
    #elif defined SHAIYA_EP6_3 || defined SHAIYA_EP6_3_PT
    constexpr int item_list_size = 16;
    #else
    constexpr int item_list_size = 8;
    #endif

    constexpr int guild_warehouse_bag = 255;
    constexpr int item_bank_bag = 200;
    constexpr int warehouse_bag = 100;

    constexpr int max_character_slot = 5;
    constexpr int max_inventory_bag = 6;
    constexpr int max_inventory_slot = 24;
    constexpr int max_myshop_slot = 20;
    constexpr int max_reqwis = 99;
    constexpr int max_warehouse_slot = 240;
    constexpr int min_warehouse_slot = 120;

    typedef UINT8* Packet;
    typedef Array<char, 128> ChatMessage;

    typedef ULONG CharId;
    typedef Array<char, 21> CharName;
    typedef Array<char, 51> Memo;

    typedef ULONG GuildId;
    typedef Array<char, 25> GuildName;

    typedef ULONG UserId;
    typedef Array<char, 32> Username;
    typedef Array<char, 16> Password;

    typedef UINT32 ItemId;
    typedef Array<char, 21> CraftName;
    typedef Array<UINT8, 6> Gems;
    using CloakBadge = Gems;
    typedef Array<char, 21> ProductCode;

    #pragma pack(push, 1)
    enum struct Country : UINT8
    {
        Light,
        Fury,
        Neutral
    };

    enum EquipmentSlot
    {
        Helmet,     //0x1C0
        UpperArmor, //0x1C4
        LowerArmor, //0x1C8
        Gloves,     //0x1CC
        Shoes,      //0x1D0
        Weapon,     //0x1D4
        Shield,     //0x1D8
        Cloak,      //0x1DC
        Ring1,      //0x1E0
        Ring2,      //0x1E4
        Bracelet1,  //0x1E8
        Bracelet2,  //0x1EC
        Necklace,   //0x1F0
        Vehicle,    //0x1F4
        Pet,        //0x1F8
        Costume,    //0x1FC
        Wings       //0x200
    };

    enum struct Family : UINT8
    {
        Human,
        Elf,
        Vail,
        Deatheater
    };

    enum struct Grow : UINT8
    {
        Easy,
        Normal,
        Hard,
        Ultimate
    };

    enum struct ItemDivType : UINT32
    {
        Group = 1,
        Random,
        Unknown,
        Master
    };

    enum struct ItemMakeType : char
    {
        B = 66,
        C,
        D,
        Q = 81,
        S = 83,
        X = 88
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

    enum struct KillPC : UINT8
    {
        To,
        From
    };

    enum struct Race : UINT8
    {
        Human,
        Elf,
        Light,
        DeathEater,
        Vail,
        Fury,
        Neutral
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
        Dog = 5,
        Horse = 6,
        Pig = 7,
        Fox = 10,
        Wolf = 11,
        Knight = 12,
        Stealth = 13,
        Disguise = 100,
        Degeneration,
        Transformation,
    };
    #pragma pack(pop)
}
