# Documentation

This library is for the game service. Incoming and outgoing packet types are named relative to the services.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

## Binaries

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/

| NpcQuest | Max Level |
|----------|-----------|
| EP6      | 80        |

# Features

## Item Mall

Install the following procedures:

```
[dbo].[usp_Read_User_CashPoint_UsersMaster]
[dbo].[usp_Save_User_BuyPointItems2]
[dbo].[usp_Save_User_GiftPointItems2]
[dbo].[usp_Update_UserPoint]
```

If you receive an error, change `ALTER` to `CREATE` and try again.

## Lapis Combination && Lapisian Combination

The client expects the merchant type of the npc be 20 (Alchemist). Use the following example to get started:

```ini
;PSM_Client\Bin\Data\ItemRemake.ini
[ItemRemake_1]
ItemID1=95001
ItemID2=95001
ItemID3=95001
CreateType=95
CreateTypeID=2

[ItemRemake_2]
ItemID1=30005
ItemID2=30005
ItemID3=30005
CreateType=30
CreateTypeID=6
```

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

The episode 6 format has 6 quest results, each containing up to 3 items. The following items are supported:

| ItemId | SkillId | SkillLv |
|--------|---------|---------|
| 101112 | 432     | 2       |
| 101113 | 432     | 3       |

The library will divide the ability value by 100.

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
508    "Your revenge to <t> has succeeded!"
509    "<t> killed  you <v> time(s)."
```

## Skill Abilities

Unsupported ability types will not be implemented.

| SkillId | Ability | Supported          |
|---------|---------|--------------------|
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
| 432     | 87      | :white_check_mark: |

### Skill Ability 70

The effect(s) will be removed a few seconds after the skill has been stopped.

### Skill Ability 87

The ability value is expected to be greater than or equal to 200. The library will divide the ability value by 100.

## Chaotic Squares

### ChaoticSquare.ini

Use the following example to get started:

```ini
;PSM_Client\Bin\Data\ChaoticSquare.ini

[ChaoticSquare_1]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=6
CreateCount=1

[ChaoticSquare_2]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=13
CreateCount=1

[ChaoticSquare_3]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=19,19,19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=20
CreateCount=1

[ChaoticSquare_4]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=26,26,26,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=27
CreateCount=1

[ChaoticSquare_5]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=33,33,33,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=34
CreateCount=1

[ChaoticSquare_6]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=40,40,40,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=41
CreateCount=1
```

### Money

The gold per percentage value in the library is the same as the official server.

```cpp
// Synthesis.h
constexpr static int goldPerPercentage = 100'000'000;
```

### Crafting Hammers

The **ReqVg** value is the success rate. The library will multiply the value by 100.

| ItemId | Effect | ReqVg |
|--------|--------|-------|
| 102074 | 102    | 5     |
| 102075 | 102    | 10    |

### Free Combination

This feature will not be implemented.

## Synergy

The library expects **SetItem.SData** to be in the **PSM_Client/Bin/Data** directory.

### Client Format

The client expects the file to be encrypted.

![Capture2](https://github.com/kurtekat/shaiya-episode-6/assets/142125482/01b93010-05a5-4323-b8d5-e890551ed4b7)

#### Bonus Description

`" Sinergia [5]\n- LUC +20\n- DEX +50\n- STR +70"`

### Server Format

The library expects the file to be decrypted. The bonus text is expected to be 12 comma-separated values.

![Capture](https://github.com/kurtekat/shaiya-episode-6/assets/142125482/a0a0c116-c5a0-4443-953e-35077e29f065)

The values are signed 32-bit integers, expected to be in the following order:

* strength
* dexterity
* intelligence
* wisdom
* reaction
* luck
* health
* mana
* stamina
* attackPower
* rangedAttackPower
* magicPower

## Item Ability Transfer

Use item `101150` to activate the window. The `CraftName` and `Gems` will be removed from the original item if the transfer is successful.

| ItemId | Effect |
|--------|--------|
| 101150 | 105    |

### Success Rate

The base success rate is 30 percent.

| ItemId  | Effect | ReqVg | Success Rate |
|---------|--------|-------|--------------|
| 101156  | 106    | 20    | 50           |
| 101157  | 106    | 50    | 80           |
| 101158  | 106    | 60    | 90           |

### Clients

| Locale | Patch | Supported          |
|--------|-------|--------------------|
| ES     | 171   | :white_check_mark: |
| PT     | 182   | :x:                |
| PT     | 189   | :x:                |

## Perfect Lapisian Combination

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

| ItemId | Effect | GateKeeper |
|--------|--------|------------|
| 101102 | 104    | 111        |
| 101103 | 104    | 112        |
| 101104 | 104    | 101        |
| 101105 | 104    | 102        |
| 101106 | 104    | 103        |
| 101107 | 104    | 104        |
| 101108 | 104    | 105        |
| 101109 | 104    | 106        |
