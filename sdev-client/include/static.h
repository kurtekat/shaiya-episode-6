#pragma once
#include <shaiya/include/common/BillingItem.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/npc/NpcType.h>
#include <shaiya/include/user/AuthStatus.h>
#include "include/shaiya/common.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CWorldMgr.h"

namespace shaiya
{
    using Inventory = Array<Array<CItem, 24>, 6>;
    using Warehouse = Array<CItem, 240>;
    using Bank = Array<BillingItem, 240>;
    using StoredPointItems = Bank;

    enum struct WindowType : UINT32
    {
        None,
        Teleportation = 17,
        CashShop,
        GiftBox,
        AppearanceChange,
        SexChange,
        Talk = 100,
        Merchant,
        Blacksmith,
        Warehouse,
        LinkAndExtract,
        Priest,
        GamblingHouse,
        GateKeeper,
        VetManager,
        BadgeMerchant,
        BankTeller,
        GuildMaster,
        AuctionBoard = 117,
        ProBlacksmith = 120,
        Recreation,
        Creation,
        RuneCombination = 126,
    };

    enum struct TargetType : int
    {
        None = -1,
        Mob,
        Item,
        User,
        Npc
    };

    #pragma pack(push, 1)
    struct ExcItem
    {
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuickSlot
    {
        UINT8 srcBag;
        PAD(1);
        UINT16 srcSlot;
        PAD(4);
        // quick z and x
        UINT32 itemType;
        UINT32 itemTypeId;
        // 0x10
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 004F1980 ctor
    struct Global
    {
        UINT32 clientVersion;         //0x90D1D0  0x00
        AuthStatus authStatus;        //0x90D1D4  0x04
        PAD(3);
        BOOL isAdmin;                 //0x90D1D8  0x08
        UINT32 money;                 //0x90D1DC  0x0C
        UINT32 bankMoney;             //0x90D1E0  0x10
        UINT32 level;                 //0x90D1E4  0x14
        UINT32 maxHealth;             //0x90D1E8  0x18
        UINT32 maxMana;               //0x90D1EC  0x1C
        UINT32 maxStamina;            //0x90D1F0  0x20
        UINT32 exp;                   //0x90D1F4  0x24
        UINT32 reqExpToLvDown;        //0x90D1F8  0x28
        UINT32 reqExpToLvUp;          //0x90D1FC  0x2C
        UINT16 strength;              //0x90D200  0x30
        UINT16 intelligence;          //0x90D202  0x32
        UINT16 dexterity;             //0x90D204  0x34
        UINT16 wisdom;                //0x90D206  0x36
        UINT16 reaction;              //0x90D208  0x38
        UINT16 luck;                  //0x90D20A  0x3A
        PAD(160);
        UINT16 statPoint;             //0x90D2AC  0xDC
        UINT16 skillPoint;            //0x90D2AE  0xDE
        UINT32 abilityStrength;       //0x90D2B0  0xE0
        UINT32 abilityReaction;       //0x90D2B4  0xE4
        UINT32 abilityIntelligence;   //0x90D2B8  0xE8
        UINT32 abilityWisdom;         //0x90D2BC  0xEC
        UINT32 abilityDexterity;      //0x90D2C0  0xF0
        UINT32 abilityLuck;           //0x90D2C4  0xF4
        UINT32 minAttackPower;        //0x90D2C8  0xF8
        UINT32 addAttackPower;        //0x90D2CC  0xFC
        UINT32 minMagicPower;         //0x90D2D0  0x100
        UINT32 addMagicPower;         //0x90D2D4  0x104
        UINT32 defense;               //0x90D2D8  0x108
        UINT32 resistance;            //0x90D2DC  0x10C
        CharArray<4096> c110;         //0x90D2E0  0x110
        UINT16 mapId;                 //0x90E2E0  0x1110
        PAD(2);
        D3DVECTOR rebirthPos;         //0x90E2E4  0x1114
        UINT16 direction;             //0x90E2F0  0x1120
        PAD(2);
        ULONG charId;                 //0x90E2F4  0x1124
        Inventory inventory;          //0x90E2F8  0x1128
        // 0x910038  0x2E68
        Array<CItem, 256> bag250;
        // 0x913438  0x6268
        PAD(56);
        UINT8 hair;                   //0x913470  0x62A0
        UINT8 face;                   //0x913471  0x62A1
        UINT8 size;                   //0x913472  0x62A2
        Job job;                      //0x913473  0x62A3
        CharArray<4096> c62A4;        //0x913474  0x62A4
        Sex sex;                      //0x914474  0x72A4
        PAD(3);
        UINT32 health;                //0x914478  0x72A8
        UINT32 mana;                  //0x91447C  0x72AC
        UINT32 stamina;               //0x914480  0x72B0
        UINT8 helmetType;             //0x914484  0x72B4
        UINT8 upperType;              //0x914485  0x72B5
        UINT8 lowerType;              //0x914486  0x72B6
        UINT8 handsType;              //0x914487  0x72B7
        UINT8 bootsType;              //0x914488  0x72B8
        UINT8 weaponType;             //0x914489  0x72B9
        UINT8 shieldType;             //0x91448A  0x72BA
        UINT8 cloakType;              //0x91448B  0x72BB
        UINT8 necklaceType;           //0x91448C  0x72BC
        UINT8 ring1Type;              //0x91448D  0x72BD
        UINT8 ring2Type;              //0x91448E  0x72BE
        UINT8 bracelet1Type;          //0x91448F  0x72BF
        UINT8 bracelet2Type;          //0x914490  0x72C0
        UINT8 vehicleType;            //0x914491  0x72C1
        UINT8 petType;                //0x914492  0x72C2
        UINT8 costumeType;            //0x914493  0x72C3
        UINT8 wingsType;              //0x914494  0x72C4
        UINT8 helmetTypeId;           //0x914495  0x72C5
        UINT8 upperTypeId;            //0x914496  0x72C6
        UINT8 lowerTypeId;            //0x914497  0x72C7
        UINT8 handsTypeId;            //0x914498  0x72C8
        UINT8 bootsTypeId;            //0x914499  0x72C9
        UINT8 weaponTypeId;           //0x91449A  0x72CA
        UINT8 shieldTypeId;           //0x91449B  0x72CB
        UINT8 cloakTypeId;            //0x91449C  0x72CC
        UINT8 necklaceTypeId;         //0x91449D  0x72CD
        UINT8 ring1TypeId;            //0x91449E  0x72CE
        UINT8 ring2TypeId;            //0x91449F  0x72CF
        UINT8 bracelet1TypeId;        //0x9144A0  0x72D0
        UINT8 bracelet2TypeId;        //0x9144A1  0x72D1
        UINT8 vehicleTypeId;          //0x9144A2  0x72D2
        UINT8 petTypeId;              //0x9144A3  0x72D3
        UINT8 costumeTypeId;          //0x9144A4  0x72D4
        UINT8 wingsTypeId;            //0x9144A5  0x72D5
        PAD(40);
        CharArray<21> charName;       //0x9144CE  0x72FE
        PAD(1);
        WindowType windowType;        //0x9144E4  0x7314
        ULONG npcId1;                 //0x9144E8  0x7318
        ULONG npcId2;                 //0x9144EC  0x731C
        UINT32 npcIcon;               //0x9144F0  0x7320
        // 0x9144F4  0x7324
        Array<CItem, 256> npcShopItemList;
        UINT8 npcShopItemCount;       //0x9178F4  0xA724
        PAD(3);
        Warehouse warehouse;          //0x9178F8  0xA728
        PAD(4);
        // 0x91A9BC  0xD7EC
        Array<CItem, 8> exchangeItemList;
        // 0x91AB5C  0xD98C
        Array<CItem, 8> exchangeUserItemList;
        // 0x91ACFC  0xDB2C
        Array<ExcItem, 8> exchangeItemList2;
        BOOL exchangeAccepted;        //0x91AD14  0xDB44
        BOOL exchangeUserAccepted;    //0x91AD18  0xDB48
        BOOL exchangeConfirmed;       //0x91AD1C  0xDB4C
        BOOL exchangeUserConfirmed;   //0x91AD20  0xDB50
        UINT32 exchangeMoney;         //0x91AD24  0xDB54
        UINT32 exchangeUserMoney;     //0x91AD28  0xDB58
        ULONG exchangeUserId;         //0x91AD2C  0xDB5C
        BOOL questCompleted;          //0x91AD30  0xDB60
        UINT8 questMsgIndex;          //0x91AD34  0xDB64
        PAD(1);
        UINT16 questId;               //0x91AD36  0xDB66
        UINT8 questResultMsgIndex;    //0x91AD38  0xDB68
        PAD(3);
        // effect 39,44,45,50,99
        UINT8 itemEffectBag;          //0x91AD3C  0xDB6C
        UINT8 itemEffectSlot;         //0x91AD3D  0xDB6D
        UINT8 townScrollBag;          //0x91AD3E  0xDB6E
        UINT8 townScrollSlot;         //0x91AD3F  0xDB6F
        UINT32 npcTypeId;             //0x91AD40  0xDB70
        NpcType32 npcType;            //0x91AD44  0xDB74
        PAD(26802894);
        Country country;              //0x22AA816  0x199D646
        PAD(1);
        // 0x22AA818  0x199D648
        Array<QuickSlot, 50> quickSlotList;
        UINT8 quickSlot1Bag;          //0x22AAB38  0x199D968
        UINT8 quickSlot2Bag;          //0x22AAB39  0x199D969
        PAD(2);
        // 0x22AAB3C  0x199D96C
        Array<QuickSlot, 24> revolverList;
        // 0x22AACBC  0x199DAEC
        PAD(20);
        QuickSlot quickPotionZ;       //0x22AACD0  0x199DB00
        QuickSlot quickPotionX;       //0x22AACE0  0x199DB10
        // 0x22AACF0  0x199DB20
        PAD(332);
        UINT32 kills;                 //0x22AAE3C  0x199DC6C
        UINT32 deaths;                //0x22AAE40  0x199DC70
        PAD(2420);
        CharArray<128> textBuf;       //0x22AB7B8  0x199E5E8
        // 0x22AB838  0x199E668
        PAD(36);
        UINT32 points;                //0x22AB85C  0x199E68C
        PAD(34);
        Bank bank;                    //0x22AB882  0x199E6B2
        // 0x22ABB52  0x199E982
        StoredPointItems storedPointItems;
        // 0x22ABE22  0x199EC52
        PAD(1970);
        ULONG npcId3;                 //0x22AC5D4  0x199F404
        PAD(15408);
        // 0x19A3038
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 00572D30 ctor
    struct Camera
    {
        D3DMATRIX world;           //0x22B69B0  0x00
        D3DMATRIX view;            //0x22B69F0  0x40
        D3DMATRIX projection;      //0x22B6A30  0x80
        D3DVECTOR pos;             //0x22B6A70  0xC0
        D3DVECTOR lookAt;          //0x22B6A7C  0xCC
        D3DVECTOR up;              //0x22B6A88  0xD8
        DXGI_RGB color;            //0x22B6A94  0xE4
        // Character->pos
        D3DVECTOR target;          //0x22B6AA0  0xF0
        D3DMATRIX mat1;            //0x22B6AAC  0xFC
        D3DMATRIX mat2;            //0x22B6AEC  0x13C
        D3DMATRIX mat3;            //0x22B6B2C  0x17C
        D3DMATRIX mat4;            //0x22B6B6C  0x1BC
        // 0x22B6BAC  0x1FC
        PAD(348);
        // 0x22B6D08  0x358
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer1;
        // 0x22B6D0C  0x35C
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer2;
        PAD(4);
        // 0x22B6D14  0x364
        D3DPRESENT_PARAMETERS presentParameters;
        LPD3DXFONT font1;          //0x22B6D4C  0x39C
        LPD3DXFONT font2;          //0x22B6D50  0x3A0
        LPD3DXFONT font3;          //0x22B6D54  0x3A4
        LPD3DXFONT font4;          //0x22B6D58  0x3A8
        HFONT hFont;               //0x22B6D5C  0x3AC
        PAD(96);
        LPDIRECT3D9 d3d9;          //0x22B6DC0  0x410
        LPDIRECT3DDEVICE9 device;  //0x22B6DC4  0x414
        PAD(8);
        void* staticText;          //0x22B6DD0  0x420
        PAD(3076);
        LPDIRECTDRAW directDraw;   //0x22B79D8  0x1028
        PAD(1544);
        // 0x1634
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Static
    {
        PAD(216);                      //0x7AB000
        D2D_SIZE_U client;             //0x7AB0D8
        D3DVIEWPORT9 viewport;         //0x7AB0E0
        // 0x7AB0F8
        PAD(2788);
        // CUser->id, CMob->id, CNpc->id
        ULONG targetId;                //0x7ABBDC
        TargetType targetType;         //0x7ABBE0
        PAD(84796);
        // 0x7C0720
        CharArray<MAX_PATH> iniFileName;
        // 0x7C0824
        PAD(1416);
        float fogStart;                //0x7C0DAC
        float fogEnd;                  //0x7C0DB0
        PAD(28);
        CharArray<16> ipv4Addr;        //0x7C0DD0
        // 0x7C0DE0
        PAD(1468);
        HWND hwnd;                     //0x7C139C
        HINSTANCE hinst;               //0x7C13A0
        PAD(1940);
        // <t>
        CharArray<512> t;              //0x7C1B38
        PAD(1024);
        // <s>
        CharArray<512> s;              //0x7C2138
        // <p>
        CharArray<512> p;              //0x7C2338
        // <i>
        CharArray<512> i;              //0x7C2538
        // 0x7C2738
        PAD(4);
        // <v>
        UINT32 v;                      //0x7C273C
        PAD(9000);
        CWorldMgr worldMgr;            //0x7C4A68
        // 0x906DE0
        PAD(25584);
        Global global;                 //0x90D1D0
        // 0x22B0208
        PAD(6384);
        UINT32 killLv;                 //0x22B1AF8
        UINT32 deathLv;                //0x22B1AFC
        PAD(2492);
        LPDIRECTINPUT8A directInput8;  //0x22B24BC
        PAD(6832);
        HIMC himc;                     //0x22B3F70
        PAD(10804);
        LPDIRECT3DDEVICE9 device;      //0x22B69A8
        PAD(4);
        Camera camera;                 //0x22B69B0
        // 0x22B7FE4
        PAD(16);
        float fps;                     //0x22B7FF4
        PAD(237504);
        LPDIRECTSOUND8 directSound8;   //0x22F1FB8
        PAD(33608);
        int socket;                    //0x22FA304
        PAD(21368);
        // 0x22FF680
        CharArray<MAX_PATH> exeFileName;
        // 0x22FF784
        PAD(708);
        HMODULE hModule;               //0x22FFA48
        //

        static void GetMsg(int type, int line, int unknown);
    };
    #pragma pack(pop)
}

// access static memory
inline auto g_static = (shaiya::Static*)0x7AB000;
