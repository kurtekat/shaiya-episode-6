#pragma once
#include "include/shaiya/common.h"
#include "include/shaiya/include/CAniListData.h"
#include "include/shaiya/include/CEffectData.h"
#include "include/shaiya/include/CMonsterData.h"
#include "include/shaiya/include/CObjectData.h"
#include "include/shaiya/include/CPlayerData.h"
#include "include/shaiya/include/CWorldMgr.h"

namespace shaiya
{
    struct CStaticText;

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
        CStaticText* staticText;   //0x22B6DD0  0x420
        PAD(3076);
        LPDIRECTDRAW directDraw;   //0x22B79D8  0x1028
        PAD(1544);
        // 0x1634
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // the .data section
    struct Static
    {
        PAD(216);                         //0x7AB000
        D2D_SIZE_U client;                //0x7AB0D8
        D3DVIEWPORT9 viewport;            //0x7AB0E0
        // 0x7AB0F8
        PAD(2788);
        // CUser->id, CMob->id, CNpc->id
        ULONG targetId;                   //0x7ABBDC
        TargetType targetType;            //0x7ABBE0
        PAD(84796);
        CharArray<MAX_PATH> iniFileName;  //0x7C0720
        // 0x7C0824
        PAD(1416);
        float fogStart;                   //0x7C0DAC
        float fogEnd;                     //0x7C0DB0
        PAD(28);
        CharArray<16> ipv4Addr;           //0x7C0DD0
        // 0x7C0DE0
        PAD(1468);
        HWND hwnd;                        //0x7C139C
        HINSTANCE hinst;                  //0x7C13A0
        PAD(1940);
        // <t>
        CharArray<512> t;                 //0x7C1B38
        PAD(1024);
        // <s>
        CharArray<512> s;                 //0x7C2138
        // <p>
        CharArray<512> p;                 //0x7C2338
        // <i>
        CharArray<512> i;                 //0x7C2538
        // 0x7C2738
        PAD(4);
        // <v>
        UINT32 v;                         //0x7C273C
        PAD(9000);
        CWorldMgr worldMgr;               //0x7C4A68
        // 0x906DE0
        PAD(25584);
        CPlayerData playerData;           //0x90D1D0
        // 0x22B0208
        PAD(6384);
        UINT32 killLv;                    //0x22B1AF8
        UINT32 deathLv;                   //0x22B1AFC
        PAD(2492);
        LPDIRECTINPUT8A directInput8;     //0x22B24BC
        PAD(6832);
        HIMC himc;                        //0x22B3F70
        PAD(6708);
        Array<wchar_t, 1024> wcharBuf1;   //0x22B59A8
        Array<wchar_t, 1024> wcharBuf2;   //0x22B61A8
        LPDIRECT3DDEVICE9 device;         //0x22B69A8
        PAD(4);
        Camera camera;                    //0x22B69B0
        // 0x22B7FE4
        PAD(16);
        float fps;                        //0x22B7FF4
        PAD(12816);
        CAniListData humf_action;         //0x22BB208
        CAniListData humm_action;         //0x22BB228
        CAniListData huwf_action;         //0x22BB248
        CAniListData huwm_action;         //0x22BB268
        CAniListData elmr_action;         //0x22BB288
        CAniListData elmm_action;         //0x22BB2A8
        CAniListData elwr_action;         //0x22BB2C8
        CAniListData elwm_action;         //0x22BB2E8
        CAniListData vimr_action;         //0x22BB308
        CAniListData vimm_action;         //0x22BB328
        CAniListData viwr_action;         //0x22BB348
        CAniListData viwm_action;         //0x22BB368
        CAniListData demf_action;         //0x22BB388
        CAniListData demr_action;         //0x22BB3A8
        CAniListData dewf_action;         //0x22BB3C8
        CAniListData dewr_action;         //0x22BB3E8
        CMonsterData vehicle_hu_01;       //0x22BB408
        CMonsterData vehicle_el_01;       //0x22BB41C
        CMonsterData vehicle_vi_01;       //0x22BB430
        CMonsterData vehicle_de_01;       //0x22BB444
        CObjectData objectData00;         //0x22BB458
        CObjectData itm01;                //0x22BB474
        CObjectData itm02;                //0x22BB490
        CObjectData itm03;                //0x22BB4AC
        CObjectData itm04;                //0x22BB4C8
        CObjectData itm05;                //0x22BB4E4
        CObjectData itm06;                //0x22BB500
        CObjectData itm07;                //0x22BB51C
        CObjectData itm08;                //0x22BB538
        CObjectData itm09;                //0x22BB554
        CObjectData itm10;                //0x22BB570
        CObjectData itm11;                //0x22BB58C
        CObjectData itm12;                //0x22BB5A8
        CObjectData itm13;                //0x22BB5C4
        CObjectData itm14;                //0x22BB5E0
        CObjectData itm15;                //0x22BB5FC
        CObjectData objectData16;         //0x22BB618
        CObjectData objectData17;         //0x22BB634
        CObjectData objectData18;         //0x22BB650
        CObjectData itm19;                //0x22BB66C
        CObjectData objectData20;         //0x22BB688
        CObjectData objectData21;         //0x22BB6A4
        CObjectData objectData22;         //0x22BB6C0
        CObjectData objectData23;         //0x22BB6DC
        CObjectData objectData24;         //0x22BB6F8
        CObjectData objectData25;         //0x22BB714
        CObjectData objectData26;         //0x22BB730
        CObjectData objectData27;         //0x22BB74C
        CObjectData objectData28;         //0x22BB768
        CObjectData objectData29;         //0x22BB784
        CObjectData objectData30;         //0x22BB7A0
        CObjectData objectData31;         //0x22BB7BC
        CObjectData objectData32;         //0x22BB7D8
        CObjectData objectData33;         //0x22BB7F4
        CObjectData itm34;                //0x22BB810
        CObjectData objectData35;         //0x22BB82C
        CObjectData objectData36;         //0x22BB848
        CObjectData objectData37;         //0x22BB864
        CObjectData objectData38;         //0x22BB880
        CObjectData objectData39;         //0x22BB89C
        CEffectData effectData00;         //0x22BB8B8
        CEffectData effectData01;         //0x22BB9E4
        CEffectData attack;               //0x22BBB10
        CEffectData level_up;             //0x22BBC3C
        CEffectData start;                //0x22BBD68
        CEffectData portal;               //0x22BBE94
        CEffectData point;                //0x22BBFC0
        CEffectData weather;              //0x22BC0EC
        CEffectData monster;              //0x22BC218
        CEffectData cwater;               //0x22BC344
        CEffectData crun;                 //0x22BC470
        CEffectData quest;                //0x22BC59C
        CEffectData up;                   //0x22BC6C8
        CEffectData effectData13;         //0x22BC7F4
        CEffectData effectData14;         //0x22BC920
        CEffectData bless;                //0x22BCA4C
        CEffectData strip_npc;            //0x22BCB78
        CEffectData effectData17;         //0x22BCCA4
        CEffectData effectData18;         //0x22BCDD0
        CEffectData guild;                //0x22BCEFC
        CEffectData in_ma_generic;        //0x22BD028
        CEffectData in_ma_fire;           //0x22BD154
        CEffectData in_ma_earth;          //0x22BD280
        CEffectData in_ma_wind;           //0x22BD3AC
        CEffectData in_ma_water;          //0x22BD4D8
        CEffectData in_ma_light;          //0x22BD604
        CEffectData in_ma_white;          //0x22BD730
        CEffectData in_sa_spirits;        //0x22BD85C
        CEffectData in_ma_red_flare;      //0x22BD988
        CEffectData in_ma_dark;           //0x22BDAB4
        CEffectData in_mb_generic;        //0x22BDBE0
        CEffectData in_mb_fire;           //0x22BDD0C
        CEffectData in_mb_earth;          //0x22BDE38
        CEffectData in_mb_wind;           //0x22BDF64
        CEffectData in_mb_water;          //0x22BE090
        CEffectData in_mb_white;          //0x22BE1BC
        CEffectData in_mb_red_flare;      //0x22BE2E8
        CEffectData in_mc_yellow;         //0x22BE414
        CEffectData in_mc_black;          //0x22BE540
        CEffectData in_mc_suicide;        //0x22BE66C
        CEffectData in_sc_cowardice;      //0x22BE798
        CEffectData in_mc_taunt;          //0x22BE8C4
        CEffectData in_mc_wind;           //0x22BE9F0
        CEffectData in_mc_water;          //0x22BEB1C
        CEffectData in_md_yellow;         //0x22BEC48
        CEffectData in_md_black;          //0x22BED74
        CEffectData in_sa_round;          //0x22BEEA0
        CEffectData in_sa_power;          //0x22BEFCC
        CEffectData in_sa_dragon;         //0x22BF0F8
        CEffectData in_sa_red;            //0x22BF224
        CEffectData in_sa_black;          //0x22BF350
        CEffectData in_sb_deathly;        //0x22BF47C
        CEffectData in_sc_rising;         //0x22BF5A8
        CEffectData in_sd_wind;           //0x22BF6D4
        CEffectData in_sd_m_wind;         //0x22BF800
        CEffectData in_se_protection;     //0x22BF92C
        CEffectData ca_magic;             //0x22BFA58
        CEffectData ca_fire;              //0x22BFB84
        CEffectData ca_ice;               //0x22BFCB0
        CEffectData ca_piercing;          //0x22BFDDC
        CEffectData ca_triple;            //0x22BFF08
        CEffectData ca_elemental;         //0x22C0034
        CEffectData ca_bomb;              //0x22C0160
        CEffectData ca_sharp;             //0x22C028C
        CEffectData ca_death;             //0x22C03B8
        CEffectData ca_sacrifice;         //0x22C04E4
        CEffectData ca_killer;            //0x22C0610
        CEffectData ca_jumping_airshot;   //0x22C073C
        CEffectData ca_shower;            //0x22C0868
        CEffectData ca_flame_q;           //0x22C0994
        CEffectData ca_earth_q;           //0x22C0AC0
        CEffectData ca_storm_q;           //0x22C0BEC
        CEffectData ca_surge_q;           //0x22C0D18
        CEffectData ca_souanlip;          //0x22C0E44
        CEffectData rc_mana;              //0x22C0F70
        CEffectData rc_stamina;           //0x22C109C
        CEffectData rc_health;            //0x22C11C8
        CEffectData da_self_fire;         //0x22C12F4
        CEffectData da_self_crag;         //0x22C1420
        CEffectData da_target_slumpshot;         //0x22C154C
        CEffectData da_target_untouchable;       //0x22C1678
        CEffectData da_self_confusion;           //0x22C17A4
        CEffectData da_target_dragon;            //0x22C18D0
        CEffectData da_self_power;               //0x22C19FC
        CEffectData da_area_fire;                //0x22C1B28
        CEffectData da_area_rock;                //0x22C1C54
        CEffectData da_area_gale;                //0x22C1D80
        CEffectData da_area_hailstorm;           //0x22C1EAC
        CEffectData da_area_meteor;              //0x22C1FD8
        CEffectData da_area_earthquake;          //0x22C2104
        CEffectData da_area_lightning;           //0x22C2230
        CEffectData da_area_blizzard;            //0x22C235C
        CEffectData da_area_elemental;           //0x22C2488
        CEffectData da_targer_valribomb;         //0x22C25B4
        CEffectData da_area_earth_pole;          //0x22C26E0
        CEffectData da_area_turbulent;           //0x22C280C
        CEffectData da_area_frozen;              //0x22C2938
        CEffectData da_target_suicidal;          //0x22C2A64
        CEffectData da_target_trap_bomb;         //0x22C2B90
        CEffectData da_area_disease;             //0x22C2CBC
        CEffectData da_area_mwind;               //0x22C2DE8
        CEffectData da_area_blood_shower;        //0x22C2F14
        CEffectData da_area_shower;              //0x22C3040
        CEffectData da_target_a_damage;          //0x22C316C
        CEffectData da_target_generic;           //0x22C3298
        CEffectData da_target_bash;              //0x22C33C4
        CEffectData da_target_concentration;     //0x22C34F0
        CEffectData da_target_slow;              //0x22C361C
        CEffectData da_target_root;              //0x22C3748
        CEffectData da_target_sonic;             //0x22C3874
        CEffectData da_target_slumber;           //0x22C39A0
        CEffectData da_target_agi;               //0x22C3ACC
        CEffectData da_target_long;              //0x22C3BF8
        CEffectData da_target_protect;           //0x22C3D24
        CEffectData da_target_beserk_fighter;    //0x22C3E50
        CEffectData da_target_hard;              //0x22C3F7C
        CEffectData da_target_mana;              //0x22C40A8
        CEffectData da_target_stun;              //0x22C41D4
        CEffectData da_target_stop;              //0x22C4300
        CEffectData da_target_stamina;           //0x22C442C
        CEffectData da_target_i_vision;          //0x22C4558
        CEffectData da_target_health_assist;     //0x22C4684
        CEffectData da_target_co_guard;          //0x22C47B0
        CEffectData da_target_darkness;          //0x22C48DC
        CEffectData da_target_transformation;    //0x22C4A08
        CEffectData da_target_silence;           //0x22C4B34
        CEffectData da_target_distraction;       //0x22C4C60
        CEffectData da_target_hellfire;          //0x22C4D8C
        CEffectData effectData128;               //0x22C4EB8
        CEffectData da_target_mirror;            //0x22C4FE4
        CEffectData da_target_e_bomb;            //0x22C5110
        CEffectData da_target_health;            //0x22C523C
        CEffectData da_target_m_attack;          //0x22C5368
        CEffectData da_target_dying;             //0x22C5494
        CEffectData da_target_power;             //0x22C55C0
        CEffectData ca_hellfire;                 //0x22C56EC
        CEffectData da_target_degeneration;      //0x22C5818
        CEffectData da_target_panic;             //0x22C5944
        CEffectData da_target_curse;             //0x22C5A70
        CEffectData da_target_misfortune;        //0x22C5B9C
        CEffectData da_target_healing;           //0x22C5CC8
        CEffectData da_target_dispel;            //0x22C5DF4
        CEffectData da_target_sacrifice;         //0x22C5F20
        CEffectData da_target_shot_pointer;      //0x22C604C
        CEffectData da_target_attribute;         //0x22C6178
        CEffectData da_target_blunt;             //0x22C62A4
        CEffectData da_target_tactical;          //0x22C63D0
        CEffectData da_target_leadership;        //0x22C64FC
        CEffectData da_target_manashot;          //0x22C6628
        CEffectData da_target_aurora;            //0x22C6754
        CEffectData da_target_support;           //0x22C6880
        CEffectData da_target_incantation;       //0x22C69AC
        CEffectData da_target_marksman;          //0x22C6AD8
        CEffectData da_target_prayer;            //0x22C6C04
        CEffectData da_target_heal_pole;         //0x22C6D30
        CEffectData da_target_soul;              //0x22C6E5C
        CEffectData da_target_resurrection;      //0x22C6F88
        CEffectData da_target_s_attack;          //0x22C70B4
        CEffectData da_target_body_protect;      //0x22C71E0
        CEffectData da_target_dizacent;          //0x22C730C
        CEffectData da_target_dilcritical;       //0x22C7438
        CEffectData da_target_d_control;         //0x22C7564
        CEffectData da_target_me_vision;         //0x22C7690
        CEffectData da_target_nemesis;           //0x22C77BC
        CEffectData da_target_sirsteindom;       //0x22C78E8
        CEffectData da_target_arouse_blow;       //0x22C7A14
        CEffectData da_tartet_s_bomb;            //0x22C7B40
        CEffectData da_target_m_wind;            //0x22C7C6C
        CEffectData da_target_dreinge;           //0x22C7D98
        CEffectData da_target_atthersing;        //0x22C7EC4
        CEffectData da_target_t_attack;          //0x22C7FF0
        CEffectData da_target_bomb;              //0x22C811C
        CEffectData da_target_mana_drain;        //0x22C8248
        CEffectData ca_disease;                  //0x22C8374
        CEffectData in_mc_generic;               //0x22C84A0
        CEffectData in_mc_cowardice;             //0x22C85CC
        CEffectData da_target_heavy_swat;        //0x22C86F8
        CEffectData in_mc_white;                 //0x22C8824
        CEffectData da_target_healing_prayer;    //0x22C8950
        CEffectData da_target_p_guard;           //0x22C8A7C
        CEffectData da_target_nuke;              //0x22C8BA8
        CEffectData da_target_dayfly;            //0x22C8CD4
        CEffectData da_target_pantera;           //0x22C8E00
        CEffectData da_self_kamain_breath;       //0x22C8F2C
        CEffectData da_target_e_breath;          //0x22C9058
        CEffectData da_target_recovery;          //0x22C9184
        CEffectData in_sa_solash;                //0x22C92B0
        CEffectData in_sa_g_attack;              //0x22C93DC
        CEffectData in_sa_trap;                  //0x22C9508
        CEffectData in_sa_vclash;                //0x22C9634
        CEffectData in_sa_phantom;               //0x22C9760
        CEffectData in_sa_saiarick;              //0x22C988C
        CEffectData in_sa_stinger;               //0x22C99B8
        CEffectData in_sa_d_damage;              //0x22C9AE4
        CEffectData in_sa_stop_blow;             //0x22C9C10
        CEffectData in_sa_heath_drain;           //0x22C9D3C
        CEffectData in_sa_wild_dance;            //0x22C9E68
        CEffectData in_sa_slasher;               //0x22C9F94
        CEffectData in_md_generic;               //0x22CA0C0
        CEffectData in_me_generic;               //0x22CA1EC
        CEffectData in_mf_generic;               //0x22CA318
        CEffectData in_ma_commercial;            //0x22CA444
        CEffectData in_mb_commercial;            //0x22CA570
        CEffectData da_target_sp_remedy;         //0x22CA69C
        CEffectData da_target_hp_remedy;         //0x22CA7C8
        CEffectData da_target_mp_remedy;         //0x22CA8F4
        CEffectData da_target_nostrum;           //0x22CAA20
        CEffectData da_target_remedy;            //0x22CAB4C
        CEffectData da_target_commercial_a;      //0x22CAC78
        CEffectData da_target_commercial_b;      //0x22CADA4
        CEffectData flarebomb1;                  //0x22CAED0
        CEffectData flarebomb2;                  //0x22CAFFC
        CEffectData flarebomb3;                  //0x22CB128
        CEffectData flarebomb4;                  //0x22CB254
        CEffectData effectData214;               //0x22CB380
        CEffectData effectData215;               //0x22CB4AC
        CEffectData effectData216;               //0x22CB5D8
        CEffectData effectData217;               //0x22CB704
        CEffectData item_e;                      //0x22CB830
        CEffectData item_w;                      //0x22CB95C
        CEffectData effectData220;               //0x22CBA88
        CEffectData effectData221;               //0x22CBBB4
        CEffectData effectData222;               //0x22CBCE0
        CEffectData effectData223;               //0x22CBE0C
        CEffectData effectData224;               //0x22CBF38
        CEffectData effectData225;               //0x22CC064
        CEffectData effectData226;               //0x22CC190
        CEffectData effectData227;               //0x22CC2BC
        CEffectData effectData228;               //0x22CC3E8
        CEffectData effectData229;               //0x22CC514
        CEffectData absorption_aura;             //0x22CC640
        CEffectData arrow_bomber_shot;           //0x22CC76C
        CEffectData complete_restore;            //0x22CC898
        CEffectData dance_of_death;              //0x22CC9C4
        CEffectData deadly_poison_shot;          //0x22CCAF0
        CEffectData detonation;                  //0x22CCC1C
        CEffectData elate;                       //0x22CCD48
        CEffectData energy_blackhole;            //0x22CCE74
        CEffectData explosive_sting;             //0x22CCFA0
        CEffectData frost_barrier;               //0x22CD0CC
        CEffectData mental_impact;               //0x22CD1F8
        CEffectData mental_storm_confusing;      //0x22CD324
        CEffectData mental_storm_distortion;     //0x22CD450
        CEffectData mental_storm_lure;           //0x22CD57C
        CEffectData missle_rage;                 //0x22CD6A8
        CEffectData soul_menace;                 //0x22CD7D4
        CEffectData stunning_disruption1;        //0x22CD900
        CEffectData effectData247;               //0x22CDA2C
        CEffectData effectData248;               //0x22CDB58
        CEffectData effectData249;               //0x22CDC84
        CEffectData power_of_fire_m;             //0x22CDDB0
        CEffectData int_of_brutal;               //0x22CDEDC
        CEffectData dex_of_brutal;               //0x22CE008
        CEffectData luc_of_radiant;              //0x22CE134
        CEffectData mind_of_med;                 //0x22CE260
        CEffectData mp_recover;                  //0x22CE38C
        CEffectData rec_protection;              //0x22CE4B8
        CEffectData resist;                      //0x22CE5E4
        CEffectData freezing_arrow;              //0x22CE710
        CEffectData freezing_arrow_arrow;        //0x22CE83C
        CEffectData effectData260;               //0x22CE968
        CEffectData effectData261;               //0x22CEA94
        CEffectData revenge_mark_notice1;        //0x22CEBC0
        CEffectData revenge_mark_notice2;        //0x22CECEC
        CEffectData revenge_mark_notice3;        //0x22CEE18
        CEffectData revenge_mark_loop1;          //0x22CEF44
        CEffectData revenge_mark_loop2;          //0x22CF070
        CEffectData revenge_mark_loop3;          //0x22CF19C
        CEffectData revenge_mark_loop4;          //0x22CF2C8
        CEffectData revenge_mark_loop5;          //0x22CF3F4
        CEffectData revenge_mark_loop6;          //0x22CF520
        CEffectData revenge_mark_loop7;          //0x22CF64C
        CEffectData revenge_mark_loop8;          //0x22CF778
        CEffectData effectData273;               //0x22CF8A4
        CEffectData effectData274;               //0x22CF9D0
        CEffectData effectData275;               //0x22CFAFC
        CEffectData effectData276;               //0x22CFC28
        CEffectData effectData277;               //0x22CFD54
        CEffectData effectData278;               //0x22CFE80
        CEffectData effectData279;               //0x22CFFAC
        CEffectData effectData280;               //0x22D00D8
        CEffectData effectData281;               //0x22D0204
        CEffectData effectData282;               //0x22D0330
        CEffectData effectData283;               //0x22D045C
        CEffectData effectData284;               //0x22D0588
        CEffectData effectData285;               //0x22D06B4
        CEffectData effectData286;               //0x22D07E0
        CEffectData effectData287;               //0x22D090C
        CEffectData effectData288;               //0x22D0A38
        CEffectData effectData289;               //0x22D0B64
        CEffectData effectData290;               //0x22D0C90
        CEffectData effectData291;               //0x22D0DBC
        CEffectData effectData292;               //0x22D0EE8
        CEffectData effectData293;               //0x22D1014
        CEffectData effectData294;               //0x22D1140
        CEffectData effectData295;               //0x22D126C
        CEffectData effectData296;               //0x22D1398
        CEffectData effectData297;               //0x22D14C4
        CEffectData effectData298;               //0x22D15F0
        CEffectData effectData299;               //0x22D171C
        // 0x22D1848
        PAD(132976);
        LPDIRECTSOUND8 directSound8;             //0x22F1FB8
        PAD(33608);
        int socket;                              //0x22FA304
        PAD(21368);
        CharArray<MAX_PATH> exeFileName;         //0x22FF680
        // 0x22FF784
        PAD(708);
        HMODULE hModule;                         //0x22FFA48
        PAD(21940);
        // 0x2305000 (.rsrc)

        // static functions

        static void GetMsg(int type, int line, int unknown);
    };
    #pragma pack(pop)

    // access global variables
    inline auto g_var = (Static*)0x7AB000;
}
