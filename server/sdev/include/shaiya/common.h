#pragma once
#pragma warning(disable: 28159) // GetTickCount
//#define SHAIYA_EP6
//#define SHAIYA_EP6_3_US
//#define SHAIYA_EP6_3_PT
//#define SHAIYA_EP6_4_PT

#define SHAIYA_EP6_BLACKSMITH

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_COMMON
#endif

#if \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_3_PT
#define SHAIYA_EP6_3_COMMON
#endif

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_0511
#endif

#if \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_DURATION
#endif

#if \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_EFFECT
#endif

#if \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_EQUIPMENT
#endif

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_SET
#endif

#if \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_ITEM_SYNTHESIS
#endif

#if \
defined SHAIYA_EP6 || \
defined SHAIYA_EP6_3_US || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_QUEST_RESULT
#endif

#if \
defined SHAIYA_EP6_3_PT || \
defined SHAIYA_EP6_4_PT
#define SHAIYA_EP6_CLONE_SIZE_128
#endif

#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// thanks, Cups ^^
#define CONCAT(x, y) x ## y
#define EXPAND(x, y) CONCAT(x, y)
#define PAD(size) char EXPAND(pad, __LINE__)[size]

namespace shaiya
{
    struct CItem;

    #ifdef SHAIYA_EP6_4_PT
    constexpr int item_list_size = 17;
    #elif defined SHAIYA_EP6_3_COMMON
    constexpr int item_list_size = 16;
    #else
    constexpr int item_list_size = 8;
    #endif

    constexpr int warehouse_bag = 100;
    constexpr int bank_bag = 200;
    constexpr int guild_warehouse_bag = 255;

    constexpr int max_inventory_bag = 6;
    constexpr int max_inventory_slot = 24;
    constexpr int max_warehouse_slot = 240;
    constexpr int min_warehouse_slot = 120;

    template<class T, int N>
    using Array = std::array<T, N>;

    typedef unsigned Address;
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

    typedef Array<Array<CItem*, 24>, 6> Inventory;
    typedef Array<CItem*, 240> Warehouse;

    enum struct AuthStatus : UINT8
    {
        AdminA = 1,
        AdminB = 2,
        AdminC = 3,
        AdminD = 4,
        AdminE = 5,
        None = 11
    };

    enum struct ChatType : UINT8
    {
        Normal = 1,
        To,
        Guild,
        Party,
        Trade = 5,
        All = 5,
        Shout,
        Zone
    };

    enum struct Country : UINT8
    {
        Light,
        Fury,
        Neutral
    };

    #pragma pack(push, 1)
    struct GameLogMain
    {
        ULONG userId;
        Username username;
        ULONG charId;
        CharName charName;
        UINT16 level;
        UINT32 exp;
        UINT16 mapId;
        float x;
        float y;
        float z;
        ULONG actionTime;
    };
    #pragma pack(pop)

    enum EquipmentSlot
    {
        Helmet,      //0x1C0
        UpperArmor,  //0x1C4
        LowerArmor,  //0x1C8
        Gloves,      //0x1CC
        Shoes,       //0x1D0
        Weapon,      //0x1D4
        Shield,      //0x1D8
        Cloak,       //0x1DC
        Ring1,       //0x1E0
        Ring2,       //0x1E4
        Bracelet1,   //0x1E8
        Bracelet2,   //0x1EC
        Necklace,    //0x1F0
        Vehicle,     //0x1F4
        Pet,         //0x1F8
        Costume,     //0x1FC
        Wings,       //0x200
        Index17,     //0x204
        Index18,     //0x208
        Index19,     //0x20C
        Index20,     //0x210
        Index21,     //0x214
        Index22,     //0x218
        Index23      //0x21C
        // 0x220
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

    enum struct InsZoneId : UINT32
    {
        // boss mobs

        Number1001 = 1001,
        Number1002,
        Number1003,
        Number1004,
        Number1005,
        Number1006,
        Number1007,
        Number1008,
        Number1009,
        Number2000 = 2000,

        // portals

        DeepDesertLight = 1010,
        DeepDesertFury = 1020,
        StableErdeLight = 1011,
        StableErdeFury = 1021,
        PalaionRegnumLight = 1060,
        ValdemarRegnumFury = 1061
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
        Billing = 'B',
        MobDrop = 'D',
        G = 'G',
        QuestResult = 'Q',
        S = 'S',
        Exchange = 'T',
        UserDrop = 'U',
        V = 'V',
        CashShop = 'X'
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

    enum struct PvPStatusType : UINT8
    {
        Kill,
        Death,
        Win,
        Loss
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
        Dog,
        Horse,
        Pig,
        Fox = 10,
        Wolf,
        Knight,
        Stealth,
        Disguise = 100,
        Degeneration,
        Transformation,
    };
}
