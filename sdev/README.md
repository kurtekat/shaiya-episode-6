# Documentation

This library is for the game service. Please read the features section to learn more.

## Environment

Windows 10

Visual Studio 2019

C++ 20

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

## Binaries

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/

| NpcQuest | Max Level |
|----------|-----------|
| EP6      | 80        |

## Configuration

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/data/

## Stored Procedures

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db/bin/sql

# Features

All features are implemented based on client specifications. The intent is to keep everything as vanilla as possible.

## Item Mall

Install the following stored procedures:

```
[dbo].[usp_Read_User_CashPoint_UsersMaster]
[dbo].[usp_Save_User_BuyPointItems2]
[dbo].[usp_Save_User_GiftPointItems2]
[dbo].[usp_Update_UserPoint]
```

The stored procedures are original code. If you receive an error, change `ALTER` to `CREATE` and try again.

## Item Repair

The client endurance will not match the server endurance in real-time. Please relog to see the correct repair cost(s).

### EP5

```
RepairCost = (Item.Buy / 30.0) * (Damage / 400.0) 
```

### EP6.4

```
RepairCost = (Item.Buy / 15.0) * (Damage / 400.0) 
```

## Battlefield Move

The library expects **BattleFieldMoveInfo.ini** to be in the **PSM_Client/Bin/Data** directory. For each section in the file, assign a unique value to the `MAP_NO` key. The move will be instant, like the official server. Certain debuffs will prevent movement. Moving to the same zone is not allowed.

### Clients

| Locale | Patch | Supported |
|--------|-------|-----------|
| ES     | 171   | :x:       |
| PT     | 182   | :x:       |
| PT     | 189   | :x:       |

## Reward Item

Progress is account-wide. The progress of the current item will reset if a character leaves the game world. Do not expect the progress bar to synchronize perfectly. The index will reset when the last item is received.

### Configuration

The library expects **OnlineTimePrize.ini** to be in the **PSM_Client/Bin/Data** directory. The client expects to receive 20 item units.

### System Messages

```
2044		"The keep-alive event has ended."
...
7188		"Could not receive your reward because you do not have space in your inventory."
7189		"Bronze medal received"
7190		"Silver medal received"
7191		"Gold medal received"
7192		"Recurring player item received"
```

### Timeout

The client adds 15 seconds to the timeout, so the library will do the same.

```cpp
auto minutes = rewardItem[index].minutes;
auto timeout = GetTickCount() + ((minutes * 60000) + 15000);
```

### Clients

| Locale | Patch | Supported          |
|--------|-------|--------------------|
| ES     | 171   | :x:                |
| PT     | 182   | :white_check_mark: |
| PT     | 189   | :white_check_mark: |

## Alchemy (not implemented)

The client expects the merchant type of the npc to be 20 (Alchemist).

| NpcType | NpcTypeID |
|---------|-----------|
| 1       | 310       |

### Lapis Combination

The client does not allow more than one lapis from the same stack. `ReqIg` values 31 through 40 are allowed.

#### Materials

Requires 1 Crowley Essence for each `ReqIg` value greater than or equal to 36.

| ItemID | ItemName        | ItemEffect |
|--------|-----------------|------------|
| 100247 | Crowley Essence | 85         |

### Lapisian Combination

The client does not allow more than one lapisian from the same stack.

#### Materials

Requires 1 Crowley Liquid.

| ItemID | ItemName        | ItemEffect |
|--------|-----------------|------------|
| 100248 | Crowley Liquid  | 92         |

## Rune Combination

The function that adds support for recreation runes is disabled by default because of Cheat Engine scripts.

```cpp
// sdev\src\packet_gem.cpp
//#define SHAIYA_EP6_4_ENABLE_0806_HANDLER
```

The following items are supported:

### Vials

| ItemId | Effect |
|--------|--------|
| 101007 | 93     |
| 101008 | 94     |
| 101009 | 95     |
| 101010 | 96     |
| 101011 | 97     |
| 101012 | 98     |

### Recreation Runes

| ItemId | Effect |
|--------|--------|
| 100171 | 62     |
| 101001 | 86     |
| 101002 | 87     |
| 101003 | 88     |
| 101004 | 89     |
| 101005 | 90     |
| 101006 | 91     |

## NpcQuest

The episode 6 format has 6 quest results, each containing up to 3 items. The game service executable has been modified to read the file format.

## Revenge Mark

The kill count will determine which effect(s) will be rendered. The library will increment the kill count until 999.

| KillCount | EffectName                | EffectDataId |
|-----------|---------------------------|--------------|
| 1         | RevengeMark_Loop_01.EFT   | 265          |     
| 2         | RevengeMark_Loop_02.EFT   | 266          |
| 3         | RevengeMark_Loop_03.EFT   | 267          |
| 4         | RevengeMark_Loop_04.EFT   | 268          |
| 5         | RevengeMark_Loop_05.EFT   | 269          |
| 6         | RevengeMark_Loop_06.EFT   | 270          |
| 7         | RevengeMark_Loop_07.EFT   | 271          |
| 8-999     | RevengeMark_Loop_08.EFT   | 272          |
| odd       | RevengeMark_Notice_01.EFT | 262          |
| even      | RevengeMark_Notice_02.EFT | 263          |
| 999       | RevengeMark_Notice_03.EFT | 264          |

The client library adds support for system message 509.

```
508		"Your revenge to <t> has succeeded!"
509		"<t> killed  you <v> time(s)."
```

## Skill Abilities

The library adds support for episode 6 skill abilities 70, 87, and 35 (exp stones). **It does not affect other skills.**

| SkillId | Ability | Supported          |
|---------|---------|--------------------|
| 222     | 35      | :white_check_mark: |
| 223     | 35      | :white_check_mark: |
| 272     | 35      | :white_check_mark: |
| 375     | 52      | :x:                |
| 376     | 53      | :x:                |
| 377     | 54      | :x:                |
| 378     | 55      | :x:                |
| 379     | 56      | :x:                |
| 380     | 57      | :x:                |
| 398     | 70      | :white_check_mark: |
| 399     | 70      | :white_check_mark: |
| 400     | 70      | :white_check_mark: |
| 401     | 70      | :white_check_mark: |
| 396     | 73      | :x:                |
| 397     | 74      | :x:                |
| 412     | 78      | :x:                |
| 426     | 35      | :white_check_mark: |
| 427     | 35      | :white_check_mark: |
| 432     | 87      | :white_check_mark: |
| 434     | 35      | :white_check_mark: |

### Skill Ability 35

The original code multiplies exp depending on the value of two `CUser` variables:

```
// 00574080 (2.0)
bool32_t multiplyExp2;  //0x596C
// 00574090 (1.5)
bool32_t multiplyExp1;  //0x5970 (not used)
```

The library modifies `CUser::AddExpFromUser` to support 6.4 skill ability values.

| ItemId | SkillId | SkillLv | AbilityValue |
|--------|---------|---------|--------------|
| 100042 | 222     | 1       | 150          |
| 100043 | 223     | 1       | 150          |
| 101114 | 426     | 2       | 500          |
| 101115 | 426     | 3       | 1000         |
| 101117 | 427     | 2       | 500          |
| 101121 | 434     | 2       | 200          |
| 101122 | 434     | 3       | 200          |

The ability value is expected to be greater than 100. The library will divide the ability value by 100.

### Skill Ability 70

The effect(s) will be removed a few seconds after the skill has been stopped.

### Skill Ability 87

Use the following items to get started:

| ItemId | SkillId | SkillLv |
|--------|---------|---------|
| 101112 | 432     | 2       |
| 101113 | 432     | 3       |

The ability value is expected to be greater than 100. The library will divide the ability value by 100.

## Chaotic Squares

The library expects **ChaoticSquare.ini** to be in the **PSM_Client/Bin/Data** directory.

### Fortune Money

The default value is `100'000'000`. The value should be nonzero and evenly divisible by 100. The chance of successful synthesis will be increased by 1 percent per the whole value given (can be fractional) and will be limited to 5 percent.

### Crafting Hammers

The **ReqVg** value is the success rate. The library will multiply the value by 100.

| ItemId | Effect | ReqVg |
|--------|--------|-------|
| 102074 | 102    | 5     |
| 102075 | 102    | 10    |

### Free Combination

This feature will not be implemented.

## Synergy

The library expects **SetItem.ini** to be in the **PSM_Client/Bin/Data** directory.

### Client

The client expects **SetItem.SData** to be encrypted.

![Capture2](https://github.com/kurtekat/shaiya-episode-6/assets/142125482/01b93010-05a5-4323-b8d5-e890551ed4b7)

Bonus description:

`" Sinergia [5]\n- LUC +20\n- DEX +50\n- STR +70"`

### Server

The `Drop` field is the ID of the item set. The original item SData files can be used for testing.

```sql
USE PS_GameDefs
SELECT ItemName, ItemID, [Drop] FROM Items WHERE [Drop]=64
```

Output:

| ItemName                  | ItemID | Drop |
|---------------------------|--------|------|
| Bright Emperor's Helmet   | 72003  | 64   |
| Bright Emperor's Armor    | 73003  | 64   |
| Bright Emperor's Pants    | 74003  | 64   |
| Bright Emperor's Gauntlet | 76003  | 64   |
| Bright Emperor's Boots    | 77003  | 64   |

This machine code is incompatible:

```
// CGameData::LoadConstItem
// EBX = 0
004DB0DA  CMP WORD PTR SS:[ESP+70],6     // Drop
004DB0E0  JBE SHORT ps_game.004DB0E6
004DB0E2  MOV DWORD PTR SS:[ESP+70],EBX  // Overwrite with 0
```

The instruction at `004DB0E2` has been removed so we can use vanilla configuration.

```
004DB0DA  CMP WORD PTR SS:[ESP+70],6
004DB0E0  JBE SHORT ps_game.004DB0E6
004DB0E2  NOP
004DB0E3  NOP
004DB0E4  NOP
004DB0E5  NOP
```

I do not know if the change will cause an issue elsewhere.

## Item Ability Move

Use item `101150` to activate the window. The `CraftName` and `Gems` will be removed from the original item if the transfer is successful.

| ItemId | Effect |
|--------|--------|
| 101150 | 105    |

### Chance

The base chance is 30 percent.

| ItemId  | Effect | ReqVg | Chance |
|---------|--------|-------|--------|
| 101156  | 106    | 20    | 50     |
| 101157  | 106    | 50    | 80     |
| 101158  | 106    | 60    | 90     |

### Clients

| Locale | Patch | Supported          |
|--------|-------|--------------------|
| ES     | 171   | :white_check_mark: |
| PT     | 182   | :x:                |
| PT     | 189   | :x:                |

## Perfect Lapisian

The vanilla items define a perfect success rate (10000).

```cpp
auto materialCount = 10;
auto reqRec = 10000;

auto rate = reqRec * 100; // 1000000
rate += materialCount;    // 1000010
```

If `ReqRec` is zero, the game service will get the rate from `g_LapisianEnchantSuccessRate`.

### Configuration

| Column         | Value    | Description               |
|----------------|----------|---------------------------|
| Level          | 0:1      | Can use with Weapons      |
| Country        | 0:1      | Can use with Helmets      |
| AttackFighter  | 0:1      | Can use with Upper Armor  |
| DefenseFighter | 0:1      | Can use with Lower Armor  |
| PatrolRogue    | 0:1      | Can use with Shields      |
| ShootRogue     | 0:1      | Can use with Gloves       |
| AttackMage     | 0:1      | Can use with Boots        |
| ReqRec         | 0:10000  | Success rate              |
| Range          | 0:19     | Minimum item enchant step |
| AttackTime     | 1:20     | Maximum step              |
| ReqVg          | 0:1      | Needs item protection     |

## Lapisian Remake

Use item `101101` to activate the window. The `ReqLuc` value is the number of lapisian required for combination. See system message 510 for more information.

## Item Effects

### Pets

The function that adds support for pet item effects is disabled by default because of Cheat Engine scripts.

```cpp
// sdev\src\packet_gem.cpp
//#define SHAIYA_EP6_4_ENABLE_PET_ITEM_EFFECT
```

The following item effects are supported:

| ItemId | ItemEffect |
|--------|------------|
| 120120 | 212        | 
| 120121 | 213        |
| 120122 | 214        |

The item effect will determine which effect will be rendered when the pet is equipped.

| ItemEffect | EffectName        | EffectDataId |
|------------|-------------------|--------------|
| 212        | pet_gold.EFT      | 291          |
| 213        | pet_item.EFT      | 292          |
| 214        | pet_gold_item.EFT | 293          |

### Safety Charms

| ItemId | Effect |
|--------|--------|
| 101090 | 103    |
| 101132 | 103    |

### Town Move Scrolls

The library will read `TownMoveScroll` keys from `Map.ini` to determine whether the item effect is enabled or disabled.

```ini
[SET_ZONE_0]
MapType		 = F
WeatherState	  = 0
WeatherRate	  = 10
WeatherPower	  = 1
WeatherDelay	  = 10
WeatherNoneDelay	  = 60
TownMoveScroll   = 0
```

The move will be instant, like the official server. Certain debuffs will prevent movement. The library will use NPC data to determine the locations. The item `ReqVg` value is the NPC.

| ItemId | Effect | ReqVg |
|--------|--------|-------|
| 101102 | 104    | 111   |
| 101103 | 104    | 112   |
| 101104 | 104    | 101   |
| 101105 | 104    | 102   |
| 101106 | 104    | 103   |
| 101107 | 104    | 104   |
| 101108 | 104    | 105   |
| 101109 | 104    | 106   |

# Notes

## Warehouse Items

I received several reports over the course of this project about missing warehouse items. I just want to provide evidence that I believe will absolve me of this shit. I will also provide a solution to the underlying issue.

### Research

People who reported the issue had a teleport feature that sends invalid `0x50A` packets to the server.

```
SEND >> 0A 05 06 01
SEND >> 0A 05 06 02
SEND >> 0A 05 06 03
SEND >> 0A 05 06 04
SEND >> 0A 05 06 05
SEND >> 0A 05 06 06
SEND >> 0A 05 06 07
SEND >> 0A 05 06 08
SEND >> 0A 05 06 09
SEND >> 0A 05 06 0A
SEND >> 0A 05 06 0B
SEND >> 0A 05 06 0C
SEND >> 0A 05 06 0D
SEND >> 0A 05 06 0E
SEND >> 0A 05 06 0F
SEND >> 0A 05 06 10
```

The bag value is 6, which is an out-of-range subscript.

```cpp
Array<Array<CItem*, 24>, 6> inventory;  //0x1C0
Array<CItem*, 240> warehouse;           //0x400
```

The `CUser` memory alignment:

```
                   0x1C0 -> inventory[0][0]
(24 * 4) + 0x1C0 = 0x220 -> inventory[1][0]
(24 * 4) + 0x220 = 0x280 -> inventory[2][0]
(24 * 4) + 0x280 = 0x2E0 -> inventory[3][0]
(24 * 4) + 0x2E0 = 0x340 -> inventory[4][0]
(24 * 4) + 0x340 = 0x3A0 -> inventory[5][0]
(24 * 4) + 0x3A0 = 0x400 -> warehouse[0]
```

So...

```
inventory[6][0] = 0x400 -> warehouse[0]
inventory[6][1] = 0x404 -> warehouse[1]
inventory[6][2] = 0x408 -> warehouse[2]
inventory[6][3] = 0x40C -> warehouse[3]
inventory[6][4] = 0x410 -> warehouse[4]
inventory[6][5] = 0x414 -> warehouse[5]
...
```

### Solution

Replace the client code that sends the invalid packet.

```cpp
if (g_pPlayerData->mapId == mapId)
{
    Static::SysMsgToChatBox(ChatType::Default, 6602, 1);
    return;
}

GameMovePvPZoneIncoming outgoing{};
outgoing.mapId = mapId;
CNetwork::Send(&outgoing, sizeof(GameMovePvPZoneIncoming));
```

The sdev library will take care of the rest.

## File Operations

I think the reason for this code is unclear.

```cpp
std::wstring output(INT16_MAX, 0);
auto count = GetModuleFileNameW(nullptr, output.data(), INT16_MAX);
if (!count)
    return;

auto first = output.begin();
auto last = first + count;
m_root.assign(first, last).remove_filename();
```

Once upon a time, I told people to inject the libraries with an application. For whatever reason, some decided to import the libraries, which, in turn, bugged all the file operations.

### Research

This is what happens when `std::filesystem::current_path` is called before the current working directory is resolved.

```cpp
auto path = std::filesystem::current_path();
// result: "C:\\WINDOWS\\system32"
```

A relative path doesn't work out either.

### INT16_MAX

I looked at the machine code for `GetModuleFileNameW` because I couldn't find a clear answer regarding the `MAX_PATH` limitation.

```
KERNELBASE.GetModuleFileNameW+19 - B8 FF7F0000 - mov eax,00007FFF { 32767 }
KERNELBASE.GetModuleFileNameW+1E - 3B F0       - cmp esi,eax
KERNELBASE.GetModuleFileNameW+20 - 77 6A       - ja KERNELBASE.GetModuleFileNameW+8C
...
KERNELBASE.GetModuleFileNameW+8C - 8B F0       - mov esi,eax
KERNELBASE.GetModuleFileNameW+8E - EB 96       - jmp KERNELBASE.GetModuleFileNameW+26
```

I'll just pass the max size and be done with it.

## Cooldowns

1000 ticks = 1s (about)

### Item

| ReqIg | Ticks    |
|-------|----------|
| 0     | 0        |
| 1     | 15000    |
| 2     | 20000    |
| 3     | 25000    |
| 4     | 30000    |
| 5     | 60000    |
| 6     | 120000   |
| 7     | 0        |
| 8     | 0        |
| 9     | 0        |
| 10    | 600000   |
| 11    | 2000     |

### Monster

| AttackSpecial3 | Ticks     |
|----------------|-----------|
| 0              | 5000      |
| 1              | 30000     |
| 2              | 60000     |
| 3              | 180000    |
| 4              | 300000    |
| 5              | 900000    |
| 6              | 1800000   |
| 7              | 3600000   |
| 8              | 14400000  |
| 9              | 43200000  |
| 10             | 86400000  |
| 11             | 259200000 |
| 12             | 7200000   |
| 13             | 0         |
| 14             | 604800000 |
| 15             | 15000     |

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

### Example

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
