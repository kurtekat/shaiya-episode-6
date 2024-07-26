#pragma once
#include <shaiya/include/skill/SkillStatusType.h>
#include "include/shaiya/common.h"
#include "include/shaiya/include/CAniListData.h"
#include "include/shaiya/include/CEffectData.h"
#include "include/shaiya/include/CEffectModelList.h"
#include "include/shaiya/include/CInput.h"
#include "include/shaiya/include/CMonsterData.h"
#include "include/shaiya/include/CObjectData.h"
#include "include/shaiya/include/CPlayerData.h"
#include "include/shaiya/include/CTextureList.h"
#include "include/shaiya/include/CWorldMgr.h"
#include "include/shaiya/include/SIMM.h"

namespace shaiya
{
    struct CStaticText;
    struct CSwordEffect;
    struct CVertexShader;

    enum struct HealPointType : UINT8
    {
        Health,
        Stamina,
        Mana
    };

    // notes: code page (see 0x408060)
    // CP_ACP (see winnls.h)
    enum struct LoginVersion : UINT32
    {
        Korea = 1,     //
        China,         //
        Vietnam,       // 65001 (UTF-8)
        Japan,         // 932
        Taiwan,        // 950
        English,       // CP_ACP
        Germany,       // CP_ACP
        SingaMala,     // 950
        HongKong,      //
        France,        // CP_ACP
        Russia,        // CP_ACP
        Turkey,        // 1254
        Brazil,        // CP_ACP
        LatinAmerica,  // CP_ACP
        Poland,        // 1250
        Italy,         // CP_ACP
        Philippines    // CP_ACP
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
    // 00572D30 ctor
    struct Camera
    {
        D3DMATRIX world;            //0x22B69B0  0x00
        D3DMATRIX view;             //0x22B69F0  0x40
        D3DMATRIX projection;       //0x22B6A30  0x80
        D3DVECTOR pos;              //0x22B6A70  0xC0
        D3DVECTOR lookAt;           //0x22B6A7C  0xCC
        D3DVECTOR up;               //0x22B6A88  0xD8
        D3DVECTOR vec1;             //0x22B6A94  0xE4
        D3DVECTOR target;           //0x22B6AA0  0xF0
        D3DMATRIX mat1;             //0x22B6AAC  0xFC
        D3DMATRIX mat2;             //0x22B6AEC  0x13C
        D3DMATRIX mat3;             //0x22B6B2C  0x17C
        D3DMATRIX mat4;             //0x22B6B6C  0x1BC
        D3DMATRIX mat5;             //0x22B6BAC  0x1FC
        // 0x22B6BEC  0x23C
        PAD(260);
        D3DCOLOR fogColor;          //0x22B6CF0  0x340
        PAD(20);
        // 0x22B6D08  0x358
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer1;
        // 0x22B6D0C  0x35C
        LPDIRECT3DVERTEXBUFFER9 vertexBuffer2;
        // 0x22B6D10  0x360
        CVertexShader* vertexShader;
        // 0x22B6D14  0x364
        D3DPRESENT_PARAMETERS presentParameters;
        LPD3DXFONT d3dxFont3;       //0x22B6D4C  0x39C
        LPD3DXFONT d3dxFont2;       //0x22B6D50  0x3A0
        LPD3DXFONT d3dxFont1;       //0x22B6D54  0x3A4
        LPD3DXFONT d3dxFont0;       //0x22B6D58  0x3A8
        HFONT hFont;                //0x22B6D5C  0x3AC
        long text0Width;            //0x22B6D60  0x3B0
        long text1Width;            //0x22B6D64  0x3B4
        long text0Height;           //0x22B6D68  0x3B8
        long text1Height;           //0x22B6D6C  0x3BC
        UINT32 textColorR;          //0x22B6D70  0x3C0
        UINT32 textColorG;          //0x22B6D74  0x3C4
        UINT32 textColorB;          //0x22B6D78  0x3C8
        D3DMATERIAL9 material;      //0x22B6D7C  0x3CC
        LPDIRECT3D9 d3d9;           //0x22B6DC0  0x410
        LPDIRECT3DDEVICE9 device;   //0x22B6DC4  0x414
        UINT32 primitiveCount;      //0x22B6DC8  0x418
        BOOL showInfoText;          //0x22B6DCC  0x41C
        CStaticText* staticText;    //0x22B6DD0  0x420
        PAD(4);
        D3DGAMMARAMP gammaRamp1;    //0x22B6DD8  0x428
        D3DGAMMARAMP gammaRamp2;    //0x22B73D8  0xA28
        LPDIRECTDRAW directDraw;    //0x22B79D8  0x1028
        D3DGAMMARAMP gammaRamp3;    //0x22B79DC  0x102C
        PAD(4);
        D3DCOLOR clearDeviceColor;  //0x22B7FE0  0x1630
        // 0x1634
    };
    #pragma pack(pop)

    static_assert(sizeof(Camera) == 0x1634);

    #pragma pack(push, 1)
    // the .data section
    struct Static
    {
        PAD(212);                            //0x7AB000
        LoginVersion loginVersion;           //0x7AB0D4
        D2D_SIZE_U client;                   //0x7AB0D8
        D3DVIEWPORT9 viewport;               //0x7AB0E0
        // 0x7AB0F8
        PAD(2788);
        // CUser->id, CMob->id, CNpc->id
        ULONG targetId;                      //0x7ABBDC
        TargetType targetType;               //0x7ABBE0
        PAD(24576);
        CMonsterData monMonster;             //0x7B1BE4  monster.mon
        CMonsterData monNpc;                 //0x7B1BF8  npc.mon
        CMonsterData monStrip;               //0x7B1C0C  strip.mon
        CMonsterData monWings;               //0x7B1C20  wing.mon
        // 0x7B1C34
        PAD(284);
        CTextureList textureList;            //0x7B1D50
        CEffectModelList effectModelList;    //0x7B1D68
        // 0x7B1D80
        PAD(59808);
        CharArray<MAX_PATH> iniFileName;     //0x7C0720
        // 0x7C0824
        PAD(1384);
        BOOL enableWaterSurface;             //0x7C0D8C
        BOOL enableShadows;                  //0x7C0D90
        float viewFarthest;                  //0x7C0D94
        float viewNearest;                   //0x7C0D98
        // 0: 16-bit, 1: 32-bit
        UINT32 colorDepth;                   //0x7C0D9C
        float cameraTargetSpeed;             //0x7C0DA0
        float fogNearest;                    //0x7C0DA4
        float fogFarthest;                   //0x7C0DA8
        float fogStart;                      //0x7C0DAC
        float fogEnd;                        //0x7C0DB0
        BOOL disableFog;                     //0x7C0DB4
        float modelFarthest;                 //0x7C0DB8
        float grassFarthest;                 //0x7C0DBC
        // user, npc, mob
        float otherFarthest;                 //0x7C0DC0
        PAD(12);
        CharArray<16> ipv4Addr;              //0x7C0DD0
        // 0x7C0DE0
        PAD(1468);
        HWND hwnd;                           //0x7C139C
        HINSTANCE hinst;                     //0x7C13A0
        BOOL isFullscreenWindow;             //0x7C13A4
        PAD(4);
        BOOL isActiveWindow;                 //0x7C13AC
        PAD(1408);
        UINT32 sysMsgValue2;                 //0x7C1930  <v2>
        HealPointType sysMsgHealPointType1;  //0x7C1934  <up>
        SkillStatusType sysMsgDebuffType;    //0x7C1935  <zz>
        HealPointType sysMsgHealPointType2;  //0x7C1936  <hp>
        PAD(1);
        CharArray<512> sysMsgLapisName;      //0x7C1938  <r>
        CharArray<512> sysMsgTargetName;     //0x7C1B38  <t>
        CharArray<1024> sysMsgBuffer;        //0x7C1D38  <b>
        CharArray<512> sysMsgSkillName;      //0x7C2138  <s>
        CharArray<512> sysMsgPlayerName;     //0x7C2338  <p>
        CharArray<512> sysMsgItemName;       //0x7C2538  <i>
        UINT32 sysMsgValue3;                 //0x7C2738  <v3>
        UINT32 sysMsgValue;                  //0x7C273C  <v>
        CharArray<1024> sysMsgTextBuffer1;   //0x7C2740
        CharArray<1024> sysMsgTextBuffer2;   //0x7C2B40
        CharArray<1024> sysMsgTextBuffer3;   //0x7C2F40
        CharArray<1024> sysMsgTextBuffer4;   //0x7C3340
        CharArray<1024> sysMsgTextBuffer5;   //0x7C3740
        // 0:5 (switches buffers)
        UINT32 sysMsgTextBufferIndex;        //0x7C3B40
        PAD(3868);
        CSwordEffect* seffEventEffect;       //0x7C4A60
        CSwordEffect* seffWeather;           //0x7C4A64
        CWorldMgr worldMgr;                  //0x7C4A68
        CSwordEffect* seffLoginCloud;        //0x906DE0
        CSwordEffect* seffWeapon;            //0x906DE4
        PAD(25576);
        CPlayerData playerData;              //0x90D1D0
        // 0x22B0208
        PAD(6384);
        UINT32 killLv;                       //0x22B1AF8
        UINT32 deathLv;                      //0x22B1AFC
        PAD(2488);
        CInput input;                        //0x22B24B8
        HIMC inputContext;                   //0x22B3F70
        SIMM inputMethodManager;             //0x22B3F74
        // 0x22B3F8C
        PAD(6684);
        CharArrayW<1024> wideCharBuffer1;    //0x22B59A8
        CharArrayW<1024> wideCharBuffer2;    //0x22B61A8
        LPDIRECT3DDEVICE9 device;            //0x22B69A8
        PAD(4);
        Camera camera;                       //0x22B69B0
        // 0x22B7FE4
        PAD(16);
        float fps;                           //0x22B7FF4
        PAD(12816);
        CAniListData humfAction;             //0x22BB208
        CAniListData hummAction;             //0x22BB228
        CAniListData huwfAction;             //0x22BB248
        CAniListData huwmAction;             //0x22BB268
        CAniListData elmrAction;             //0x22BB288
        CAniListData elmmAction;             //0x22BB2A8
        CAniListData elwrAction;             //0x22BB2C8
        CAniListData elwmAction;             //0x22BB2E8
        CAniListData vimrAction;             //0x22BB308
        CAniListData vimmAction;             //0x22BB328
        CAniListData viwrAction;             //0x22BB348
        CAniListData viwmAction;             //0x22BB368
        CAniListData demfAction;             //0x22BB388
        CAniListData demrAction;             //0x22BB3A8
        CAniListData dewfAction;             //0x22BB3C8
        CAniListData dewrAction;             //0x22BB3E8
        CMonsterData vehicleHu01;            //0x22BB408
        CMonsterData vehicleEl01;            //0x22BB41C
        CMonsterData vehicleVi01;            //0x22BB430
        CMonsterData vehicleDe01;            //0x22BB444
        CObjectData objectData00;            //0x22BB458
        CObjectData itm01;                   //0x22BB474
        CObjectData itm02;                   //0x22BB490
        CObjectData itm03;                   //0x22BB4AC
        CObjectData itm04;                   //0x22BB4C8
        CObjectData itm05;                   //0x22BB4E4
        CObjectData itm06;                   //0x22BB500
        CObjectData itm07;                   //0x22BB51C
        CObjectData itm08;                   //0x22BB538
        CObjectData itm09;                   //0x22BB554
        CObjectData itm10;                   //0x22BB570
        CObjectData itm11;                   //0x22BB58C
        CObjectData itm12;                   //0x22BB5A8
        CObjectData itm13;                   //0x22BB5C4
        CObjectData itm14;                   //0x22BB5E0
        CObjectData itm15;                   //0x22BB5FC
        CObjectData objectData16;            //0x22BB618
        CObjectData objectData17;            //0x22BB634
        CObjectData objectData18;            //0x22BB650
        CObjectData itm19;                   //0x22BB66C
        CObjectData objectData20;            //0x22BB688
        CObjectData objectData21;            //0x22BB6A4
        CObjectData objectData22;            //0x22BB6C0
        CObjectData objectData23;            //0x22BB6DC
        CObjectData objectData24;            //0x22BB6F8
        CObjectData objectData25;            //0x22BB714
        CObjectData objectData26;            //0x22BB730
        CObjectData objectData27;            //0x22BB74C
        CObjectData objectData28;            //0x22BB768
        CObjectData objectData29;            //0x22BB784
        CObjectData objectData30;            //0x22BB7A0
        CObjectData objectData31;            //0x22BB7BC
        CObjectData objectData32;            //0x22BB7D8
        CObjectData objectData33;            //0x22BB7F4
        CObjectData itm34;                   //0x22BB810
        CObjectData objectData35;            //0x22BB82C
        CObjectData objectData36;            //0x22BB848
        CObjectData objectData37;            //0x22BB864
        CObjectData objectData38;            //0x22BB880
        CObjectData objectData39;            //0x22BB89C
        // notes: effectDataId, .eft, skillId(s)
        CEffectData effectData00;            //0x22BB8B8
        CEffectData effectData01;            //0x22BB9E4
        CEffectData eftAttack;               //0x22BBB10  2  attack, attack01
        CEffectData eftLevelUp;              //0x22BBC3C  3  levelup
        CEffectData eftStart;                //0x22BBD68  4  start
        CEffectData eftPortal;               //0x22BBE94  5  portal
        CEffectData eftPoint;                //0x22BBFC0  6  point
        CEffectData eftWeather;              //0x22BC0EC  7  weather
        CEffectData eftMonster;              //0x22BC218  8  monster
        CEffectData eftWater;                //0x22BC344  9  cwater
        CEffectData eftRun;                  //0x22BC470  10  crun
        CEffectData eftQuest;                //0x22BC59C  11  up
        CEffectData eftUp;                   //0x22BC6C8  12
        CEffectData eftItemL;                //0x22BC7F4  13  item_l
        CEffectData eftItemF;                //0x22BC920  14  item_f
        CEffectData eftBless;                //0x22BCA4C  15  bless
        CEffectData eftNpc;                  //0x22BCB78  16  strip_npc
        CEffectData effectData17;            //0x22BCCA4
        CEffectData effectData18;            //0x22BCDD0
        CEffectData eftGuild;                //0x22BCEFC  19  guild
        CEffectData in_ma_generic;           //0x22BD028  20
        CEffectData in_ma_fire;              //0x22BD154  21
        CEffectData in_ma_earth;             //0x22BD280  22
        CEffectData in_ma_wind;              //0x22BD3AC  23
        CEffectData in_ma_water;             //0x22BD4D8  24
        CEffectData in_ma_light;             //0x22BD604  25
        CEffectData in_ma_white;             //0x22BD730  26
        CEffectData in_sa_spirits;           //0x22BD85C  27
        CEffectData in_ma_red_flare;         //0x22BD988  28
        CEffectData in_ma_dark;              //0x22BDAB4  29
        CEffectData in_mb_generic;           //0x22BDBE0  30
        CEffectData in_mb_fire;              //0x22BDD0C  31
        CEffectData in_mb_earth;             //0x22BDE38  32
        CEffectData in_mb_wind;              //0x22BDF64  33
        CEffectData in_mb_water;             //0x22BE090  34
        CEffectData in_mb_white;             //0x22BE1BC  35
        CEffectData in_mb_red_flare;         //0x22BE2E8  36
        CEffectData in_mc_yellow;            //0x22BE414  37
        CEffectData in_mc_black;             //0x22BE540  38
        CEffectData in_mc_suicide;           //0x22BE66C  39
        CEffectData in_sc_cowardice;         //0x22BE798  40
        CEffectData in_mc_taunt;             //0x22BE8C4  41
        CEffectData in_mc_wind;              //0x22BE9F0  42
        CEffectData in_mc_water;             //0x22BEB1C  43
        CEffectData in_md_yellow;            //0x22BEC48  44
        CEffectData in_md_black;             //0x22BED74  45
        CEffectData in_sa_round;             //0x22BEEA0  46
        CEffectData in_sa_power;             //0x22BEFCC  47
        CEffectData in_sa_dragon;            //0x22BF0F8  48
        CEffectData in_sa_red;               //0x22BF224  49
        CEffectData in_sa_black;             //0x22BF350  50
        CEffectData in_sb_deathly;           //0x22BF47C  51
        CEffectData in_sc_rising;            //0x22BF5A8  52
        CEffectData in_sd_wind;              //0x22BF6D4  53
        CEffectData in_sd_m_wind;            //0x22BF800  54
        CEffectData in_se_protection;        //0x22BF92C  55
        CEffectData ca_magic;                //0x22BFA58  56
        CEffectData ca_fire;                 //0x22BFB84  57
        CEffectData ca_ice;                  //0x22BFCB0  58
        CEffectData ca_piercing;             //0x22BFDDC  59
        CEffectData ca_triple;               //0x22BFF08  60
        CEffectData ca_elemental;            //0x22C0034  61
        CEffectData ca_bomb;                 //0x22C0160  62
        CEffectData ca_sharp;                //0x22C028C  63
        CEffectData ca_death;                //0x22C03B8  64
        CEffectData ca_sacrifice;            //0x22C04E4  65
        CEffectData ca_killer;               //0x22C0610  66
        CEffectData ca_jumping_airshot;      //0x22C073C  67
        CEffectData ca_shower;               //0x22C0868  68
        CEffectData ca_flame_q;              //0x22C0994  69
        CEffectData ca_earth_q;              //0x22C0AC0  70
        CEffectData ca_storm_q;              //0x22C0BEC  71
        CEffectData ca_surge_q;              //0x22C0D18  72
        CEffectData ca_souanlip;             //0x22C0E44  73
        CEffectData rc_mana;                 //0x22C0F70  74
        CEffectData rc_stamina;              //0x22C109C  75
        CEffectData rc_health;               //0x22C11C8  76
        CEffectData eftDaSkill47;            //0x22C12F4  77  da_self_fire  47
        CEffectData da_self_crag;            //0x22C1420  78
        CEffectData eftDaSkill51;            //0x22C154C  79  da_target_slumpshot  51,310,314,315
        CEffectData eftDaSkill90;            //0x22C1678  80  da_target_untouchable  90  
        CEffectData eftDaSkill96;            //0x22C17A4  81  da_self_confusion  96
        CEffectData eftDaSkill118;           //0x22C18D0  82  da_target_dragon  118,324
        CEffectData da_self_power;           //0x22C19FC  83
        CEffectData eftDaSkill48;            //0x22C1B28  84  da_area_fire  48
        CEffectData eftDaSkill50;            //0x22C1C54  85  da_area_rock  50
        CEffectData eftDaSkill52;            //0x22C1D80  86  da_area_gale  52
        CEffectData eftDaSkill53;            //0x22C1EAC  87  da_area_hailstorm  53
        CEffectData eftDaSkill68;            //0x22C1FD8  88  da_area_meteor  68
        CEffectData eftDaSkill69;            //0x22C2104  89  da_area_earthquake  69
        CEffectData eftDaSkill70;            //0x22C2230  90  da_area_lightning  70
        CEffectData eftDaSkill71;            //0x22C235C  91  da_area_blizzard  71
        CEffectData eftDaSkill72;            //0x22C2488  92  da_area_elemental  72
        CEffectData eftDaSkill174;           //0x22C25B4  93  da_target_valribomb  174,180,282,301,309,312
        CEffectData eftDaSkill83;            //0x22C26E0  94  da_area_earthpole  83
        CEffectData eftDaSkill84;            //0x22C280C  95  da_area_turbulent  84,307,322
        CEffectData eftDaSkill85;            //0x22C2938  96  da_area_frozen  85
        CEffectData eftDaSkill171;           //0x22C2A64  97  da_target_suicidal  171
        CEffectData eftDaSkill113;           //0x22C2B90  98  da_target_trapbomb  113
        CEffectData eftDaSkill149;           //0x22C2CBC  99  da_area_disease  149
        CEffectData eftDaSkill156;           //0x22C2DE8  100  da_area_mwind  156,158
        CEffectData eftDaSkill162;           //0x22C2F14  101  da_area_bloodshower  162
        CEffectData eftDaSkill163;           //0x22C3040  102  da_area_shower  163
        CEffectData da_target_adamage;       //0x22C316C  103
        // 29,34,37,38,39,40,41,45,55,57,64,67,70,80,93,
        // 137,150,152,154,164,165,166,167,281
        CEffectData eftDaGeneric;            //0x22C3298  104  da_target_generic
        CEffectData eftDaSkill30;            //0x22C33C4  105  da_target_bash  30
        CEffectData eftDaSkill31;            //0x22C34F0  106  da_target_concentration  31,91,133,393,395,412
        CEffectData eftDaSkill33;            //0x22C361C  107  da_target_slow  33,159,169
        CEffectData eftDaSkill35;            //0x22C3748  108  da_target_root  35
        CEffectData eftDaSkill36;            //0x22C3874  109  da_target_sonic  36
        CEffectData eftDaSkill42;            //0x22C39A0  110  da_target_slumber  42
        CEffectData eftDaSkill44;            //0x22C3ACC  111  da_target_agi  44
        CEffectData eftDaSkill46;            //0x22C3BF8  112  da_target_long  46,413
        CEffectData eftDaSkill54;            //0x22C3D24  113  da_target_protect  54
        CEffectData eftDaSkill58;            //0x22C3E50  114  da_target_burserkfighter  58
        CEffectData eftDaSkill59;            //0x22C3F7C  115  da_target_mana  59
        CEffectData eftDaSkill66;            //0x22C40A8  116  da_target_mana  66
        CEffectData eftDaSkill61;            //0x22C41D4  117  da_target_stun  61
        CEffectData eftDaSkill62;            //0x22C4300  118  da_target_stop  62
        CEffectData eftDaSkill65;            //0x22C442C  119  da_target_stamina  65,155
        CEffectData eftDaSkill73;            //0x22C4558  120  da_target_iveision  73
        CEffectData eftDaSkill74;            //0x22C4684  121  da_target_healthasis  74
        CEffectData eftDaSkill75;            //0x22C47B0  122  da_target_cqguard  75
        CEffectData eftDaSkill76;            //0x22C48DC  123  da_target_darkness  76
        CEffectData eftDaSkill77;            //0x22C4A08  124  da_target_transformation  77,127,274,275
        CEffectData eftDaSkill78;            //0x22C4B34  125  da_target_silence  78
        CEffectData eftDaSkill79;            //0x22C4C60  126  da_target_distraction  79
        CEffectData eftDaSkill82;            //0x22C4D8C  127  da_target_hellfire  82,321
        CEffectData effectData128;           //0x22C4EB8  128
        CEffectData eftDaSkill86;            //0x22C4FE4  129  da_target_mirror  86
        CEffectData eftDaSkill87;            //0x22C5110  130  da_target_ebomb  87,95
        CEffectData eftDaSkill88;            //0x22C523C  131  da_target_heath  88
        CEffectData eftDaSkill89;            //0x22C5368  132  da_target_mattack  89
        CEffectData eftDaSkill92;            //0x22C5494  133  da_target_dying  92,94
        CEffectData eftDaSkill119;           //0x22C55C0  134  da_target_power  119
        CEffectData ca_hellfire;             //0x22C56EC  135
        CEffectData eftDaSkill97;            //0x22C5818  136  da_target_degeneration  63,97,107,172 
        CEffectData eftDaSkill98;            //0x22C5944  137  da_target_panic  98
        CEffectData eftDaSkill99;            //0x22C5A70  138  da_target_corse  99
        CEffectData eftDaSkill101;           //0x22C5B9C  139  da_target_misfortune  101
        CEffectData eftDaSkill102;           //0x22C5CC8  140  da_target_healing  102,131,144,148
        CEffectData eftDaSkill103;           //0x22C5DF4  141  da_target_dispel  103,130,173,326
        CEffectData eftDaSkill106;           //0x22C5F20  142  da_target_sacrifice  106
        CEffectData eftDaSkill108;           //0x22C604C  143  da_target_shotpointer  108
        CEffectData eftDaSkill109;           //0x22C6178  144  da_target_attribute  109
        CEffectData eftDaSkill110;           //0x22C62A4  145  da_target_blunt  110
        CEffectData eftDaSkill111;           //0x22C63D0  146  da_target_tactical  111
        CEffectData eftDaSkill112;           //0x22C64FC  147  da_target_leadership  112,128
        CEffectData eftDaSkill115;           //0x22C6628  148  da_target_manashot  115
        CEffectData eftDaSkill116;           //0x22C6754  149  da_target_aurora  116
        CEffectData eftDaSkill117;           //0x22C6880  150  da_target_support  117
        CEffectData eftDaSkill120;           //0x22C69AC  151  da_target_incantation  120
        CEffectData eftDaSkill121;           //0x22C6AD8  152  da_target_marksman  121
        CEffectData eftDaSkill123;           //0x22C6C04  153  da_target_prayer  123
        CEffectData eftDaSkill124;           //0x22C6D30  154  da_target_healpole  124,187
        CEffectData eftDaSkill125;           //0x22C6E5C  155  da_target_soul  125
        CEffectData eftDaSkill126;           //0x22C6F88  156  da_target_resurrection  126
        CEffectData eftDaSkill129;           //0x22C70B4  157  da_target_sattack  129,142
        CEffectData eftDaSkill132;           //0x22C71E0  158  da_target_bodyprotect  132
        CEffectData eftDaSkill135;           //0x22C730C  159  da_target_dizacent  135
        CEffectData eftDaSkill136;           //0x22C7438  160  da_target_dilcritical  136
        CEffectData eftDaSkill139;           //0x22C7564  161  da_target_econtrol  139,140
        CEffectData eftDaSkill141;           //0x22C7690  162  da_target_meveision  141
        CEffectData eftDaSkill143;           //0x22C77BC  163  da_target_nemesys  143
        CEffectData eftDaSkill146;           //0x22C78E8  164  da_target_sirsteindom  146
        CEffectData eftDaSkill147;           //0x22C7A14  165  da_target_aruzblo  147,305,308
        CEffectData eftDaSkill134;           //0x22C7B40  166  da_tartet_sbomb  134,145,151,302
        CEffectData eftDaSkill38;            //0x22C7C6C  167  da_target_mwind  38
        CEffectData eftDaSkill160;           //0x22C7D98  168  da_target_dreinge  160
        CEffectData eftDaSkill170;           //0x22C7EC4  169  da_target_atthersing  170
        CEffectData eftDaSkill176;           //0x22C7FF0  170  da_target_tattack  176
        CEffectData eftDaSkill178;           //0x22C811C  171  da_target_bomb  178
        CEffectData eftDaSkill60;            //0x22C8248  172  da_target_manadrain  49,60
        CEffectData ca_disease;              //0x22C8374
        CEffectData in_mc_generic;           //0x22C84A0
        CEffectData in_mc_cowardice;         //0x22C85CC
        CEffectData eftDaSkill138;           //0x22C86F8  176  da_target_heavyswat  122,138
        CEffectData in_mc_white;             //0x22C8824
        CEffectData eftDaSkill168;           //0x22C8950  178  da_target_healingprayer  168
        CEffectData eftDaSkill175;           //0x22C8A7C  179  da_target_pguard  175
        CEffectData eftDaSkill177;           //0x22C8BA8  180  da_target_nuke  153,157,177
        CEffectData eftDaSkill181;           //0x22C8CD4  181  da_target_dayfly  181
        CEffectData eftDaSkill182;           //0x22C8E00  182  da_target_pantera  182,183 
        CEffectData eftDaSkill184;           //0x22C8F2C  183  da_self_kamainb  184
        CEffectData eftDaSkill185;           //0x22C9058  184  da_target_ebreath  185
        CEffectData eftDaSkill186;           //0x22C9184  185  da_target_recover  186,325
        CEffectData in_sa_solash;            //0x22C92B0
        CEffectData in_sa_g_attack;          //0x22C93DC
        CEffectData in_sa_trap;              //0x22C9508
        CEffectData in_sa_vclash;            //0x22C9634
        CEffectData in_sa_phantom;           //0x22C9760
        CEffectData in_sa_saiarick;          //0x22C988C
        CEffectData in_sa_stinger;           //0x22C99B8
        CEffectData in_sa_d_damage;          //0x22C9AE4
        CEffectData in_sa_stop_blow;         //0x22C9C10
        CEffectData in_sa_health_drain;      //0x22C9D3C
        CEffectData in_sa_wild_dance;        //0x22C9E68
        CEffectData in_sa_slasher;           //0x22C9F94
        CEffectData in_md_generic;           //0x22CA0C0
        CEffectData in_me_generic;           //0x22CA1EC
        CEffectData in_mf_generic;           //0x22CA318
        CEffectData in_ma_commercial;        //0x22CA444
        CEffectData in_mb_commercial;        //0x22CA570
        // 201, 208, 264
        CEffectData eftDaSpRemedy;           //0x22CA69C  203  da_target_spremedy
        // 202,207,256,257,258,263
        CEffectData eftDaHpRemedy;           //0x22CA7C8  204  da_target_hpremedy
        // 203,209,265
        CEffectData eftDaMpRemedy;           //0x22CA8F4  205  da_target_mpremedy
        // 199,204,205,206,210,211,212,213,214,215,242,
        // 243,244,259,260,266,267,276
        CEffectData eftDaNostrum;            //0x22CAA20  206  da_target_nostrum
        // 216,217,218,219,220,221,277,278,279,280
        CEffectData eftDaRemedy;             //0x22CAB4C  207  da_target_remedy
        // 223,225,227,230,235,236
        CEffectData eftDaCommercialA;        //0x22CAC78  208  da_target_commerciala
        // 222,224,226,228,229,234,240,245,249,250,251,
        // 252,253,255,260,261,268,269,270
        CEffectData eftDaCommercialB;        //0x22CADA4  209  da_target_commercialb
        CEffectData eftFlareBomb01;          //0x22CAED0  210  1flarebomb
        CEffectData eftFlareBomb02;          //0x22CAFFC  211  2flarebomb
        CEffectData eftFlareBomb03;          //0x22CB128  212  3flarebomb
        CEffectData eftFlareBomb04;          //0x22CB254  213  4flarebomb
        CEffectData effectData214;           //0x22CB380
        CEffectData effectData215;           //0x22CB4AC
        CEffectData effectData216;           //0x22CB5D8
        CEffectData effectData217;           //0x22CB704
        CEffectData eftItemE;                //0x22CB830  218  item_e
        CEffectData eftItemW;                //0x22CB95C  219  item_w
        CEffectData effectData220;           //0x22CBA88
        CEffectData effectData221;           //0x22CBBB4
        CEffectData effectData222;           //0x22CBCE0
        CEffectData effectData223;           //0x22CBE0C
        CEffectData effectData224;           //0x22CBF38
        CEffectData effectData225;           //0x22CC064
        CEffectData effectData226;           //0x22CC190
        CEffectData effectData227;           //0x22CC2BC
        CEffectData effectData228;           //0x22CC3E8
        CEffectData effectData229;           //0x22CC514
        CEffectData eftSkill346;             //0x22CC640  230  absortionaura  346
        CEffectData eftSkill353;             //0x22CC76C  231  arrowbombershot  353,355,415
        CEffectData eftSkill363;             //0x22CC898  232  completerestore  363
        CEffectData eftSkill347;             //0x22CC9C4  233  danceofdeath  347
        CEffectData eftSkill354;             //0x22CCAF0  234  deadlypoisonshot  354
        CEffectData eftSkill344;             //0x22CCC1C  235  detonation  344
        CEffectData eftSkill345;             //0x22CCD48  236  elate  345
        CEffectData eftSkill341;             //0x22CCE74  237  energyblackhole  341
        CEffectData eftSkill340;             //0x22CCFA0  238  explosivesting  340
        CEffectData eftSkill364;             //0x22CD0CC  239  frostbarrier  364
        CEffectData eftSkill343;             //0x22CD1F8  240  mentalimpact  343
        CEffectData eftSkill349;             //0x22CD324  241  mentalstormconfusing  349
        CEffectData eftSkill350;             //0x22CD450  242  mentalstormdistortion  350
        CEffectData eftSkill348;             //0x22CD57C  243  mentalstormlure  348
        CEffectData eftSkill356;             //0x22CD6A8  244  misslerage  356
        CEffectData eftSkill352;             //0x22CD7D4  245  soulmenace  352
        CEffectData eftSkill351;             //0x22CD900  246  stunningdisruptionl  351
        CEffectData effectData247;           //0x22CDA2C
        CEffectData effectData248;           //0x22CDB58
        CEffectData effectData249;           //0x22CDC84
        CEffectData eftSkill398;             //0x22CDDB0  250  power_of_firem  398
        CEffectData eftSkill399;             //0x22CDEDC  251  int_of_burtal  399
        CEffectData eftSkill400;             //0x22CE008  252  dex_of_brutal  400
        CEffectData eftSkill401;             //0x22CE134  253  luc_of_rediant  401
        CEffectData eftSkill411;             //0x22CE260  254  mind_of_med  411
        CEffectData eftSkill394;             //0x22CE38C  255  mp_recover  394
        CEffectData eftSkill396;             //0x22CE4B8  256  rec_protection  396
        CEffectData eftSkill397;             //0x22CE5E4  257  resist  397 
        CEffectData eftFreezingArrow;        //0x22CE710  258  freezing_arrow
        CEffectData eftFreezingArrowArrow;   //0x22CE83C  259  freezing_arrow_arrow
        CEffectData effectData260;           //0x22CE968
        CEffectData effectData261;           //0x22CEA94
        CEffectData eftRevengeMarkNotice01;  //0x22CEBC0  262  revengemark_notice_01
        CEffectData eftRevengeMarkNotice02;  //0x22CECEC  263  revengemark_notice_02
        CEffectData eftRevengeMarkNotice03;  //0x22CEE18  264  revengemark_notice_03
        CEffectData eftRevengeMarkLoop01;    //0x22CEF44  265  revengemark_loop_01
        CEffectData eftRevengeMarkLoop02;    //0x22CF070  266  revengemark_loop_02
        CEffectData eftRevengeMarkLoop03;    //0x22CF19C  267  revengemark_loop_03
        CEffectData eftRevengeMarkLoop04;    //0x22CF2C8  268  revengemark_loop_04
        CEffectData eftRevengeMarkLoop05;    //0x22CF3F4  269  revengemark_loop_05
        CEffectData eftRevengeMarkLoop06;    //0x22CF520  270  revengemark_loop_06
        CEffectData eftRevengeMarkLoop07;    //0x22CF64C  271  revengemark_loop_07
        CEffectData eftRevengeMarkLoop08;    //0x22CF778  272  revengemark_loop_08
        CEffectData effectData273;           //0x22CF8A4
        CEffectData effectData274;           //0x22CF9D0
        CEffectData effectData275;           //0x22CFAFC
        CEffectData effectData276;           //0x22CFC28
        CEffectData effectData277;           //0x22CFD54
        CEffectData effectData278;           //0x22CFE80
        CEffectData effectData279;           //0x22CFFAC
        // Champion of Shaiya
        CEffectData eftCharacterEffect01;    //0x22D00D8  280  character_effect_01
        CEffectData effectData281;           //0x22D0204
        CEffectData effectData282;           //0x22D0330
        CEffectData effectData283;           //0x22D045C
        CEffectData effectData284;           //0x22D0588
        CEffectData effectData285;           //0x22D06B4
        CEffectData effectData286;           //0x22D07E0
        CEffectData effectData287;           //0x22D090C
        CEffectData effectData288;           //0x22D0A38
        CEffectData effectData289;           //0x22D0B64
        CEffectData effectData290;           //0x22D0C90
        CEffectData eftPetGold;              //0x22D0DBC  291  pet_gold
        CEffectData eftPetItem;              //0x22D0EE8  292  pet_item
        CEffectData eftPetGoldItem;          //0x22D1014  293  pet_gold_item
        CEffectData effectData294;           //0x22D1140
        CEffectData effectData295;           //0x22D126C
        CEffectData effectData296;           //0x22D1398
        CEffectData effectData297;           //0x22D14C4
        CEffectData effectData298;           //0x22D15F0
        CEffectData effectData299;           //0x22D171C
        // 0x22D1848
        PAD(132976);
        LPDIRECTSOUND8 directSound8;         //0x22F1FB8
        PAD(33608);
        int socket;                          //0x22FA304
        PAD(21368);
        CharArray<MAX_PATH> exeFileName;     //0x22FF680
        // 0x22FF784
        PAD(708);
        HMODULE hModule;                     //0x22FFA48
        PAD(116);
        FARPROC gdi32_GetCharABCWidthsI;     //0x22FFAC0
        FARPROC gdi32_GetCharWidthI;         //0x22FFAC4
        FARPROC gdi32_GetFontUnicodeRanges;  //0x22FFAC8
        PAD(4);
        FARPROC usp10_ScriptItemize;         //0x22FFAD0
        FARPROC usp10_ScriptShape;           //0x22FFAD4
        FARPROC usp10_ScriptPlace;           //0x22FFAD8
        FARPROC usp10_ScriptBreak;           //0x22FFADC
        FARPROC usp10_ScriptJustify;         //0x22FFAE0
        FARPROC usp10_ScriptTextOut;         //0x22FFAE4
        FARPROC usp10_ScriptGetProperties;   //0x22FFAE8
        FARPROC usp10_ScriptFreeCache;       //0x22FFAEC
        // 0x22FFAF0
        FARPROC usp10_ScriptRecordDigitSubstitution;
        // 0x22FFAF4
        FARPROC usp10_ScriptApplyDigitSubstitution;
        // 0x22FFAF8
        FARPROC usp10_ScriptGetFontProperties;
        FARPROC usp10_ScriptStringAnalyze;   //0x22FFAFC
        FARPROC usp10_ScriptStringOut;       //0x22FFB00
        FARPROC usp10_ScriptStringFree;      //0x22FFB04
        FARPROC usp10_ScriptStringCPtoX;     //0x22FFB08
        FARPROC usp10_ScriptString_pSize;    //0x22FFB0C
        PAD(21744);
        // 0x2305000 (.rsrc)

        // static functions

        static void DrawSystemMessage(int type, int lineNumber, int unknown);
        static int GetDaSkillEffectDataId(int skillId);
    };
    #pragma pack(pop)

    static_assert(sizeof(Static) == 0x1B5A000);
    static auto g_var = (Static*)0x7AB000;
}
