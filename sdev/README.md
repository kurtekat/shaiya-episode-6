# Documentation

This library is for the game service. Please read the features section to learn more.

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

All features are implemented based on client specifications. The intent is to keep everything as vanilla as possible.

## Item Mall

Install the following procedures:

```
[dbo].[usp_Read_User_CashPoint_UsersMaster]
[dbo].[usp_Save_User_BuyPointItems2]
[dbo].[usp_Save_User_GiftPointItems2]
[dbo].[usp_Update_UserPoint]
```

If you receive an error, change `ALTER` to `CREATE` and try again.

## Reward Item Event

Event progress is account-wide. The progress of the current item will reset if a character leaves the game world. Do not expect the progress bar to synchronize perfectly.

### Configuration

The client expects no more than 20 items. Use the following example to get started:

```ini
; PSM_Client\Bin\Data\RewardItem.ini

[RewardItem_1]
; minutes
Delay=5
Type=100
TypeID=1
Count=1

[RewardItem_2]
Delay=10
Type=100
TypeID=1
Count=1

[RewardItem_3]
Delay=20
Type=100
TypeID=1
Count=1

[RewardItem_4]
Delay=40
Type=100
TypeID=1
Count=1

[RewardItem_5]
Delay=80
Type=100
TypeID=1
Count=1
```

Add the following system messages:

```
2044		"The keep-alive event has ended."
//
7186		"Medal event begins in 5 minutes! Make sure you have at least 3 open inventory slots or else you will not be able to receive a reward."
7187		"Medal event begins in 1 minute! Make sure you have at least 3 open inventory slots or else you will not be able to receive a reward."
7188		"Could not receive your reward because you do not have space in your inventory."
7189		"Bronze medal received"
7190		"Silver medal received"
7191		"Gold medal received"
7192		"Recurring player item received"
```

### Medal Event

This feature will not be implemented.

### Clients

| Locale | Patch | Supported          |
|--------|-------|--------------------|
| ES     | 171   | :x:                |
| PT     | 182   | :white_check_mark: |
| PT     | 189   | :white_check_mark: |

## Alchemy

The client expects the merchant type of the npc to be 20 (Alchemist).

| NpcType | NpcTypeID |
|---------|-----------|
| 1       | 310       |

### Lapis Combination

The client expects the remake items to be the same. Use the following example to get started:

```ini
; PSM_Client\Bin\Data\ItemRemake5.ini

[ItemRemake_1]
ItemID1=30005
ItemID2=30005
ItemID3=30005
NewItemType=30
NewItemTypeID=6

[ItemRemake_2]
ItemID1=30012
ItemID2=30012
ItemID3=30012
NewItemType=30
NewItemTypeID=13

[ItemRemake_3]
ItemID1=30019
ItemID2=30019
ItemID3=30019
NewItemType=30
NewItemTypeID=20

[ItemRemake_4]
ItemID1=30026
ItemID2=30026
ItemID3=30026
NewItemType=30
NewItemTypeID=27

[ItemRemake_5]
ItemID1=30033
ItemID2=30033
ItemID3=30033
NewItemType=30
NewItemTypeID=34

[ItemRemake_6]
ItemID1=30040
ItemID2=30040
ItemID3=30040
NewItemType=30
NewItemTypeID=41
```

Lapis combination requires 1 Crowley Essence for each `ReqIg` value greater than or equal to 36. The client does not allow more than one lapis from the same stack. `ReqIg` values 30 and 99 are not allowed.

| ItemID | ItemName        | ItemEffect |
|--------|-----------------|------------|
| 100247 | Crowley Essence | 85         |

### Lapisian Combination

The client expects the remake items to be the same. Use the following example to get started:

```ini
; PSM_Client\Bin\Data\ItemRemake4.ini

[ItemRemake_1]
ItemID1=95001
ItemID2=95001
ItemID3=95001
NewItemType=95
NewItemTypeID=2

[ItemRemake_2]
ItemID1=95006
ItemID2=95006
ItemID3=95006
NewItemType=95
NewItemTypeID=7

[ItemRemake_3]
ItemID1=95002
ItemID2=95002
ItemID3=95002
NewItemType=95
NewItemTypeID=4

[ItemRemake_4]
ItemID1=95007
ItemID2=95007
ItemID3=95007
NewItemType=95
NewItemTypeID=9
```

Lapisian combination requires 1 Crowley Liquid. The client does not allow more than one lapisian from the same stack.

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

This library adds support for episode 6 skill abilities 70, 87, and 35 (exp stones). **It does not affect other skills.**

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

The original code multiplies exp depending on the value of two `CUser` booleans:

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

### ChaoticSquare.ini

Use the following example to get started:

```ini
; PSM_Client\Bin\Data\ChaoticSquare.ini

[ChaoticSquare_1]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
NewItemType=30
NewItemTypeID=6
NewItemCount=1

[ChaoticSquare_2]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
NewItemType=30
NewItemTypeID=13
NewItemCount=1

[ChaoticSquare_3]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=19,19,19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
NewItemType=30
NewItemTypeID=20
NewItemCount=1

[ChaoticSquare_4]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=26,26,26,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
NewItemType=30
NewItemTypeID=27
NewItemCount=1

[ChaoticSquare_5]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=33,33,33,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
NewItemType=30
NewItemTypeID=34
NewItemCount=1

[ChaoticSquare_6]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=40,40,40,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
NewItemType=30
NewItemTypeID=41
NewItemCount=1
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
