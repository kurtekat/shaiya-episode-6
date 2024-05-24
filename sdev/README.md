# Documentation

This library is for the **game** service. Macros are used to represent the differences in the episode 6 packets, etc.

## Macros

To use this library with episode 5 clients, comment the episode 6 macros. This is the default.

```cpp
// sdev/include/shaiya/common.h
//#define SHAIYA_EP6
//#define SHAIYA_EP6_4_PT
```

For episode 6.4 clients, expose the `SHAIYA_EP6_4_PT` macro.

```cpp
// sdev/include/shaiya/common.h
//#define SHAIYA_EP6
#define SHAIYA_EP6_4_PT
```

Do not expose the `SHAIYA_EP6_BLACKSMITH` macro if you use Cheat Engine scripts for the blacksmith.

```cpp
// sdev/include/shaiya/common.h
//#define SHAIYA_EP6_BLACKSMITH
```

## ps_game

### v1

| NpcQuest    | Max Level    |
|-------------|--------------|
| EP5         | 70           |

### v2

| NpcQuest    | Max Level    |
|-------------|--------------|
| EP6         | 70           |

### v3

| NpcQuest    | Max Level    | Item Duration    |
|-------------|--------------|------------------|
| EP6         | 80           | No               |

### v4

| NpcQuest    | Max Level    | Item Duration    |
|-------------|--------------|------------------|
| EP6         | 80           | Yes              |

## Item Mall

The procedures in the [SQL](https://github.com/kurtekat/shaiya-episode-6/tree/main/server/sdev/sql) directory need to be installed. If you skip this step, the item mall will not work. If you receive an error, change `ALTER` to `CREATE` and try again. This solution does not require a connection to SQL Server.

# Features

## NpcQuest

The episode 6 format has 6 quest results, each containing up to 3 items. The library reads the item count from memory. The original code passes 1 to **CUser::QuestAddItem**, which is why increasing the item count has no effect.

## Item Duration

Expose the `SHAIYA_EP6_ITEM_DURATION` macro to enable the code. The SQL procedures, items table, and **game** service in [this](https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v4) directory are required to support the additional database columns. Warning: the **Items** script will create an empty table.

```cpp
// sdev/include/shaiya/common.h
#define SHAIYA_EP6_ITEM_DURATION
```

### Duration

The library expects the same day(s) to seconds conversion as the client.

| Days  | Duration    |
|-------|-------------|
| 1     | 86400       |
| 7     | 604800      |
| 15    | 1296000     |
| 30    | 2592000     |

Items **will not** be removed from guild warehouses. Items **will not** be deleted without sending a notification to the client. Check the **PS_GameData** database for modified stored procedures and custom triggers before opening an issue.

### ExtDuration

The data is supported but the feature is not implemented.

| Value  | Definition      |
|--------|-----------------|
| 0      | None            |
| 1      | Unexpandable    |
| 2      | Expandable      |

## Revenge Mark

The kill count will determine which effect will be rendered. Notice effects are not supported.

| KillCount         | Effect                     |
|-------------------|----------------------------|
| 0                 | N/A                        |
| 1                 | RevengeMark_Loop_01.EFT    |
| 2                 | RevengeMark_Loop_02.EFT    |
| 3                 | RevengeMark_Loop_03.EFT    |
| 4                 | RevengeMark_Loop_04.EFT    |
| 5                 | RevengeMark_Loop_05.EFT    |
| 6                 | RevengeMark_Loop_06.EFT    |
| 7                 | RevengeMark_Loop_07.EFT    |
| 8 (or greater)    | RevengeMark_Loop_08.EFT    |

The 6.4 PT client in this repository supports message 508, but does not support message 509.

```
508    "Your revenge to <t> has succeeded!"
509    "<t> killed  you <v> time(s)."
```

## Frenzied Skills

Skill ability 70 will be used for evaluation. The following skills are supported.

| SkillID    | SkillName           |
|------------|---------------------|
| 398        | Frenzied Force      |
| 399        | Frenzied Focus      |
| 400        | Frenzied Finesse    |
| 401        | Frenzied Fortune    |

## Mailbox

This feature will not be implemented.

## Chaotic Squares

### ItemSynthesis.ini

Use the following example to get started.

```ini
;PSM_Client\Bin\Data\ItemSynthesis.ini

[ItemSynthesis_0]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=6
CreateCount=1

[ItemSynthesis_1]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=13
CreateCount=1

[ItemSynthesis_2]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=19,19,19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=20
CreateCount=1

[ItemSynthesis_3]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=26,26,26,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=27
CreateCount=1

[ItemSynthesis_4]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=33,33,33,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=34
CreateCount=1

[ItemSynthesis_5]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=40,40,40,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=41
CreateCount=1
```

### Free Combination

This feature will not be implemented.

### Money

The client uses the following math to determine the maximum gold input.

```
goldPerPercentage * 4 + goldPerPercentage
```

Set the minimum and maximum constants in **Synthesis.h** to change the result. The minimum will be used as a divisor (see packet_gem.cpp line 561), so don't set it to zero. The maximum money is the same as the official server.

```cpp
constexpr auto synthesis_min_money = 100000000U;
constexpr auto synthesis_max_money = 500000000U;
```

### Crafting Hammers

The item effect is expected to be 102. Use the **ReqVg** column in the **Items** table to store the success rate. The library will multiply the value by 100.

| ItemID    | ReqVg    |
|-----------|----------|
| 102074    | 5        |
| 102075    | 10       |

## Synergy

The library expects **SetItem.SData** to be in the **PSM_Client/Bin/Data** directory. I chose binary format because it's less error-prone than fetching the values from a database.

### Client Format

The client expects the file to be encrypted.

![Capture2](https://github.com/kurtekat/shaiya-episode-6/assets/142125482/01b93010-05a5-4323-b8d5-e890551ed4b7)

#### Bonus Description

`" Sinergia [5]\n- LUC +20\n- DEX +50\n- STR +70"`


### Server Format

The library expects the file to be decrypted. The bonus text is expected to be 12 comma-separated values.

![Capture](https://github.com/kurtekat/shaiya-episode-6/assets/142125482/a0a0c116-c5a0-4443-953e-35077e29f065)

The values are signed 32-bit integers, expected to be in the following order.

```cpp
int strength;
int dexterity;
int intelligence;
int wisdom;
int reaction;
int luck;
int health;
int mana;
int stamina;
int attackPower;
int rangedAttackPower;
int magicPower;
```

## Item Ability Transfer

Use item `101150` to activate the window. The `CraftName` and `Gems` are removed from the original item if the transfer is successful.

### Success Rate

The base success rate is 30 percent.

| ItemID    | ItemName        | ReqVg    | Rate    |
|-----------|-----------------|----------|---------|
| 101156    | Catalyst Lv1    | 20       | 50      |
| 101157    | Catalyst Lv2    | 50       | 80      |
| 101158    | Catalyst Lv3    | 60       | 90      |

### Client Versions

| Version       | Supported    |
|---------------|--------------|
| 0x16012100    | Yes          |
| 0x16021200    | No           |
| 0x16032100    | No           |

# Notes

This section will document some things that may be of interest. Some of the notes are based on modifications.

## StatusDefs

### Method

```
0x4D8210 CGameData::LoadStatus
```

### Data

| Column    | Size    |
|-----------|---------|
| Level     | 2       |
| Job       | 1       |
| HP        | 2       |
| SP        | 2       |
| MP        | 2       |

### Math

```cpp
// requires 36 bytes per level
(numJobs * (sizeof(hp) + sizeof(sp) + sizeof(mp))) * (maxLevel + 1)
```

```
// max level 70
(6 * 6) * 71 = 2556 (0x9FC)
// max level 80
(6 * 6) * 81 = 2916 (0xB64)
```

### Static Memory

```cpp
struct Status
{
    ushort hp;
    ushort sp;
    ushort mp;
};

struct StatusDefs
{
    array<Status, 71> job0;
    array<Status, 71> job1;
    array<Status, 71> job2;
    array<Status, 71> job3;
    array<Status, 71> job4;
    array<Status, 71> job5;
    // 0x9FC
};
```

#### Max Level 70

| Job  | Start       | End         | Size     |
|------|-------------|-------------|----------|
| 0    | 0x588808    | 0x5889B2    | 0x1AA    |
| 1    | 0x5889B2    | 0x588B5C    | 0x1AA    |
| 2    | 0x588B5C    | 0x588D06    | 0x1AA    |
| 3    | 0x588D06    | 0x588EB0    | 0x1AA    |
| 4    | 0x588EB0    | 0x58905A    | 0x1AA    |
| 5    | 0x58905A    | 0x589204    | 0x1AA    |

#### Max Level 80

| Job  | Start       | End         | Size     |
|------|-------------|-------------|----------|
| 0    | 0x588808    | 0x5889E8    | 0x1E0    |
| 1    | 0x5889E8    | 0x588BC8    | 0x1E0    |
| 2    | 0x588BC8    | 0x588DA8    | 0x1E0    |
| 3    | 0x588DA8    | 0x588F88    | 0x1E0    |
| 4    | 0x588F88    | 0x589168    | 0x1E0    |
| 5    | 0x589168    | 0x589348    | 0x1E0    |

### Points per level

| Job  | HP     | SP    | MP    |
|------|--------|-------|-------|
| 0    | 66     | 15    | 7     |
| 1    | 110    | 5     | 11    |
| 2    | 90     | 25    | 7     |
| 3    | 82     | 40    | 20    |
| 4    | 51     | 4     | 75    |
| 5    | 59     | 5     | 65    |

## ExpDefs

### Method

```
0x4D8440 CGameData::LoadExp
```

### Data

| Column    | Size    |
|-----------|---------|
| Level     | 2       |
| Grow      | 1       |
| Exp       | 4       |

### Math

```cpp
// requires 16 bytes per level
(numModes * sizeof(exp)) * (maxLevel + 1)
```

```
// max level 70
16 * 71 = 1136 (0x470)
// max level 80
16 * 81 = 1296 (0x510)
```

### Static Memory

```cpp
struct ExpDefs
{
    array<uint, 71> easy;
    array<uint, 71> normal;
    array<uint, 71> hard;
    array<uint, 71> ultimate;
    // 0x470
};
```

#### Max Level 70

| Grow  | Start       | End         | Size     |
|-------|-------------|-------------|----------|
| 0     | 0x589204    | 0x589320    | 0x11C    |
| 1     | 0x589320    | 0x58943C    | 0x11C    |
| 2     | 0x58943C    | 0x589558    | 0x11C    |
| 3     | 0x589558    | 0x589674    | 0x11C    |

#### Max Level 80

| Grow  | Start       | End         | Size     |
|-------|-------------|-------------|----------|
| 0     | 0x589204    | 0x589348    | 0x144    |
| 1     | 0x589348    | 0x58948C    | 0x144    |
| 2     | 0x58948C    | 0x5895D0    | 0x144    |
| 3     | 0x5895D0    | 0x589714    | 0x144    |

## Lua

### Parameters

The developers used Hungarian notation to express the data type of parameters.

### Event Handlers

```lua
OnAttacked(dwTime, dwCharId)
OnAttackable(dwTime, dwCharId)
OnNormalReset(dwTime)
OnDeath(dwTime, dwAttackedCount)
OnReturnHome(dwTime, dwAttackedCount)
OnMoveEnd(dwTime)
```

### Functions

```lua
Init()
WhileCombat(dwTime, dwHPPercent, dwAttackedCount)
```

### Methods

```lua
Mob:LuaGetNumberAggro(dwNumber)
Mob:LuaGetMinAggroEx()
Mob:LuaAttackOrderSurroundMob(dwCharId, dlPosX, dlPosZ)
Mob:LuaSay(szMessage, fDist)
Mob:LuaSayByIndex(wIndex, fDist)
Mob:LuaSayByVoice(szFileName, fDist)
Mob:LuaGetName(dwCharId)
Mob:LuaCreateMob(dwMobId, nCount, dlPosX, dlPosZ)
Mob:LuaAttackAI(dwSkillId, dwCharId)
Mob:LuaSetTarget(dwCharId)
Mob:LuaResetTargetingTerm(dwTerm)
Mob:LuaSetOnlyAttack(bLuaAttack)
Mob:LuaHoldPosion(bHoldPosion)
Mob:LuaGetMobCountByType(dwType, dlPosX, dlPosZ, nAddDist)
Mob:LuaSetUnBeatable(bUnBeatable)
Mob:LuaResetAggro()
Mob:LuaDeleteMob(dwMobId, byCount, dlPosX, dlPosZ)
Mob:LuaFixedMove(nMoveMode, dlPosX, dlPosZ)
Mob:LuaRecallUser(byJob, fDist, wMap, dlPosX, dlPosY, dlPosZ)
Mob:LuaRecover(byType, dlValue)
Mob:LuaGetMobPos(dwId, fPosX, fPosZ)
Mob:LuaGetMobHP(dwId)
Mob:LuaUpdateInZonePortal(nPortalId, nCountry)
```

### Usage

```lua
Mob = LuaMob(CMob)
math.randomseed(os.time())

bOnAttacked = 0
dwNextCreateTime = 0
bMobSay	= 0
bMobCreate = 0

function Init()
end

function OnAttacked(dwTime, dwCharId)
    if (bOnAttacked == 0) then
        szCharName = Mob:LuaGetName(dwCharId)
        Mob:LuaSay(szCharName..", you are a fool to challenge me!", 100.0)	
        bOnAttacked = 1
    end
end

function OnAttackable(dwTime, dwCharId)
end

function OnNormalReset(dwTime)
end

function OnDeath(dwTime, dwAttackedCount)
    Mob:LuaSay("I will have my revenge!", 100.0)
end

function OnReturnHome(dwTime, dwAttackedCount)
    Mob:LuaSay("You will not defeat me!", 100.0)
	
    bOnAttacked = 0
    dwNextCreateTime = 0
    bMobSay = 0
    bMobCreate = 0
end

function OnMoveEnd(dwTime)
end

function WhileCombat(dwTime, dwHPPercent, dwAttackedCount)
    Mob:LuaRecover(1, 0.1)

    if (dwHPPercent > 20) then
        nResult = math.random(1, 20)
		
        if (nResult == 1) then		
            byJob = math.random(0, 5)
            Mob:LuaSay("Leave my presence at once!", 30.0)		
            Mob:LuaResetAggro()
            Mob:LuaRecallUser(byJob, 30.0, 73, 40.077, 4.683, 59.303)
        end
    end
end
```
