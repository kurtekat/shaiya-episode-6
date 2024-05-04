#pragma once
#pragma warning(disable: 28159) // GetTickCount
//#define SHAIYA_EP6
//#define SHAIYA_EP6_4_PT
//#define SHAIYA_EP6_BLACKSMITH

#ifdef SHAIYA_EP6_4_PT
#define SHAIYA_EP6
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
    constexpr int max_equipment_slot = 17;
#else
    constexpr int max_equipment_slot = 8;
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
    typedef Array<char, 32> Password;

    typedef UINT32 ItemId;
    typedef Array<char, 21> CraftName;
    typedef Array<UINT8, 6> Gems;
    using CloakBadge = Gems;
    typedef Array<char, 21> ProductCode;

    typedef Array<Array<CItem*, 24>, 6> Inventory;
    typedef Array<CItem*, 240> Warehouse;

    enum struct Attribute : UINT8
    {
        None,
        Fire,
        Water,
        Earth,
        Wind,
        Fire2,
        Water2,
        Earth2,
        Wind2
    };

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

    #pragma pack(push, 1)
    struct ReqJob
    {
        bool attackFighter;
        bool defenseFighter;
        bool patrolRogue;
        bool shootRogue;
        bool attackMage;
        bool defenseMage;
    };
    #pragma pack(pop)

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
