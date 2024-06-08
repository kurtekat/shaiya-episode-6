# Documentation

This library is for the **game** service.

## Configuration

### Episode 5.4

```cpp
// shaiya/include/common.h
//#define SHAIYA_EP6_4_PT
```

### Episode 6.4

```cpp
// shaiya/include/common.h
#define SHAIYA_EP6_4_PT
```

The **sdev-db** library adds support for the character list packet and the name availability packet.

## ps_game

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v1

| NpcQuest    | Max Level    |
|-------------|--------------|
| EP5         | 70           |

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v2

| NpcQuest    | Max Level    | Item Duration    |
|-------------|--------------|------------------|
| EP6         | 80           | Yes              |

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v3

| NpcQuest    | Max Level    | Item Duration    |
|-------------|--------------|------------------|
| EP6         | 80           | No               |

## Item Mall

The following stored procedures need to be installed:

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db/bin/sql

```
[dbo].[usp_Read_User_CashPoint_UsersMaster]
[dbo].[usp_Save_User_BuyPointItems2]
[dbo].[usp_Save_User_GiftPointItems2]
[dbo].[usp_Update_UserPoint]
```

If you receive an error, change `ALTER` to `CREATE` and try again.

# Features

## NpcQuest

The episode 6 format has 6 quest results, each containing up to 3 items. The library reads the item count from memory. The original code passes 1 to **CUser::QuestAddItem**, which is why increasing the item count has no effect.

## Item Duration

The following stored procedure and **Items** table need to be installed:

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v2/sql

```
[dbo].[Items]
[dbo].[usp_Read_Items_R]
```

Warning: the **Items** script will create an empty table.

https://github.com/kurtekat/shaiya-episode-6/tree/main/tools/ItemSqlWriter

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

The **sdev-client** library adds support for system message 509.

```
508    "Your revenge to <t> has succeeded!"
509    "<t> killed  you <v> time(s)."
```

## Skill Ability 70

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

Use the following example to get started:

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

Set the `gold_per_percentage` constants in **packet_gem.cpp**. The value in the library is the same as the official server.

```cpp
constexpr auto gold_per_percentage = 100'000'000;
```

### Crafting Hammers

Use the **ReqVg** column in the **Items** table to store the success rate. The library will multiply the value by 100.

| ItemID    | ItemName                    | Effect    | ReqVg    |
|-----------|-----------------------------|-----------|----------|
| 102074    | Chaos Crafting Hammer       | 102       | 5        |
| 102075    | Infinite Crafting Hammer    | 102       | 10       |

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

Use item `101150` to activate the window. The `CraftName` and `Gems` are removed from the original item if the transfer is successful.

| ItemID    | ItemName                 | Effect    |
|-----------|--------------------------|-----------|
| 101150    | Transfer Rubik's Cube    | 105       |

### Success Rate

The base success rate is 30 percent.

| ItemID    | ItemName        | Effect    | ReqVg    | Success Rate    |
|-----------|-----------------|-----------|----------|-----------------|
| 101156    | Catalyst Lv1    | 106       | 20       | 50              |
| 101157    | Catalyst Lv2    | 106       | 50       | 80              |
| 101158    | Catalyst Lv3    | 106       | 60       | 90              |

### Client Versions

| Version       | Supported    |
|---------------|--------------|
| 0x16012100    | Yes          |
| 0x16021200    | No           |
| 0x16032100    | No           |

## Perfect Lapisian Cube

Use item 101101 to activate the window. There is no item effect. See system message 510 for more information.

## Enchantment Safety

The library will remove the first item it finds that has effect 103.

| ItemID    | ItemName                    | Effect    |
|-----------|-----------------------------|-----------|
| 101090    | Safety Enchant Scroll       | 103       |
| 101132    | [SP] Lapisia Lucky Charm    | 103       |
