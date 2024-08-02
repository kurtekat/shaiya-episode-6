# Shaiya Episode 6

An open-source effort to make episode 5 servers compatible with episode 6 clients.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

[Microsoft DirectX SDK (June 2010)](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

## Injection

Cheat Engine isn't guaranteed to work for everyone. It's not an issue with the application or the libraries. The libraries have an export defined in the main headers.

## Inspiration

[Cups](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/4653021-shaiya-library.html)

[EricDutra-16](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/4189218-release-wip-ep6-source-code.html)

[shen1l](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3669922-release-ep6-itemmall-fixed.html)

## References

[Eden](https://github.com/tristonplummer/Eden)

[Teos](https://github.com/ShaiyaTeos/Teos)

[Parsec](https://github.com/matigramirez/Parsec)

## Support

Older versions of the software are not supported. Report bugs via email when the issues tab is closed.

## Issues

Please provide a description and reproduction steps.

### Template

Description: 

Explain the problem

Reproduction steps:

1. Enter the game and do something
2. Do something else
3. Do something else
4. See the error

Optional:

Add images, links, etc.

## Pull Requests

Pull requests are not welcome. GitHub doesn't allow the pull requests tab to be disabled.

# Documentation

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

## Libraries

The **shaiya** library contains common types and packet definitions. The other projects depend on this library.

https://github.com/kurtekat/shaiya-episode-6/tree/main/shaiya

The **sdev-client** library is for build version `0x16021200` modifications. The DirectX SDK installer should create a system environment variable named `DXSDK_DIR` that specifies the installation directory.

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-client

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-client/bin

The **sdev-db** library is for the **dbAgent** service. It adds support for the character list packet and the name availability packet. Episode 5.4 and 6.0 servers do not require the support of this library.

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db/bin

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db/bin/sql

The binary was patched to undo an edit that causes an item mall purchase dupe.

```
// bug
00407942  mov dword ptr [ebx+8],1

// original code
00407942  mov dword ptr [ebx+8],0
```

The **sdev-login** library is for the **login** service. It fixes a well-known bug (thanks, Cups) and parameterizes the login query. Use SQL Server Profiler to see the result.

```sql
declare @p1 int
set @p1=1
exec sp_prepexec @p1 output,N'@P1 text,@P2 text,@P3 bigint,@P4 text',N'EXEC usp_Try_GameLogin_Taiwan @P1,@P2,@P3,@P4','a','a',6998436556411240449,'127.0.0.1'
select @p1
```

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-login

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-login/bin

The **sdev** library is for the **game** service. Continue reading for more information.

## Binaries

### Server

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v1

| NpcQuest | Max Level |
|----------|-----------|
| EP5      | 70        |

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v2

| NpcQuest | Max Level | Item Duration      |
|----------|-----------|--------------------|
| EP6      | 80        | :white_check_mark: |

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v3

| NpcQuest | Max Level | Item Duration |
|----------|-----------|---------------|
| EP6      | 80        | :x:           |

### Client

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-client/bin

The file is a 6.4 PT client from patch 182. It was unpacked by a friend of mine. (thanks, Ye)

#### Build Version

`0x16021200`

#### OEP

`0x637C68`

#### SData Specs

| Name     | Format |
|----------|--------|
| Item     | EP6.4  |
| Monster  | EP5    |
| NpcQuest | EP6    |
| NpcSkill | EP6    |
| Skill    | EP6    |

#### Chat Color Exploit

```
STATUS_STACK_BUFFER_OVERRUN encountered
A breakpoint instruction (__debugbreak() statement or a similar call) was executed in game.exe.
```

I believe this blog post explains what happens:

https://devblogs.microsoft.com/oldnewthing/20080404-00/?p=22863

Increasing the stack allocation in two functions seems to be a good solution. I wouldn't call it a fix. I added 512 bytes to the following instructions:

```
0047DB76:
sub esp,000005BC

0047DB83:
mov [esp+000005B8],eax

0047E871:
mov ecx,[esp+000005C4]
```

```
0057C280:
sub esp,0000054C

0057C28D:
mov [esp+00000548],eax

0057C297:
mov esi,[esp+0000055C]

0057C9F9:
mov ecx,[esp+00000558]

0057CA0B:
add esp,0000054C
```

#### Recovery

Episode 6.4 (and greater) clients do not add the values in the 0x505 packet handler.

**0x16021200**

https://archive.openshaiya.org/shaiya-es/clients/ps0171-21-1-2016-game.exe

```
005942D8  MOV DWORD PTR DS:[EAX+158],ESI
005942DE  MOV DWORD PTR DS:[EAX+160],EDX
005942E4  MOV DWORD PTR DS:[EAX+168],ECX

005942FB  MOV DWORD PTR DS:[914478],ESI
00594301  MOV DWORD PTR DS:[91447C],EDX
00594307  MOV DWORD PTR DS:[914480],ECX
```


**0x16012100**

https://archive.openshaiya.org/shaiya-pt/clients/ps0182-27-1-2016-game.exe

```
00594AC8  MOV DWORD PTR DS:[EAX+158],ESI
00594ACE  MOV DWORD PTR DS:[EAX+160],EDX
00594AD4  MOV DWORD PTR DS:[EAX+168],ECX

00594AEB  MOV DWORD PTR DS:[914478],ESI
00594AF1  MOV DWORD PTR DS:[91447C],EDX
00594AF7  MOV DWORD PTR DS:[914480],ECX
```

The game service library makes the recovery methods send the expected values to the client.

## Item Mall

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db/bin

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev-db/bin/sql

Install the following procedures:

```
[dbo].[usp_Read_User_CashPoint_UsersMaster]
[dbo].[usp_Save_User_BuyPointItems2]
[dbo].[usp_Save_User_GiftPointItems2]
[dbo].[usp_Update_UserPoint]
```

If you receive an error, change `ALTER` to `CREATE` and try again.

# Features

## NpcQuest

The episode 6 format has 6 quest results, each containing up to 3 items. The following items are supported:

| ItemId | SkillId | SkillLv |
|--------|---------|---------|
| 101112 | 432     | 2       |
| 101113 | 432     | 3       |

The library will divide the ability value by 100. The exp value in the client result window comes from the data; not the packet. Please don't report it as a bug.

## Item Duration

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v2

https://github.com/kurtekat/shaiya-episode-6/tree/main/sdev/bin/v2/sql

Warning: the **Items** script will create an empty table.

[ItemSqlWriter.zip](https://github.com/user-attachments/files/16039051/ItemSqlWriter.zip)

### Duration

The library expects the same day(s) to seconds conversion as the client.

| Days | Duration |
|------|----------|
| 1    | 86400    |
| 7    | 604800   |
| 15   | 1296000  |
| 30   | 2592000  |

Items **will not** be removed from guild warehouses. Items **will not** be deleted without sending a notification to the client. The client does not copy dates to items in the bank or guild warehouse.

```
; bags 200 and 255
00596FE6  83C4 0C  ADD ESP,0C  ;  Cases C8,FF of switch 00596F55
00596FE9  C2 0C00  RETN 0C
```

### ExtDuration

This feature will not be implemented.

| Value | Definition   |
|-------|--------------|
| 0     | None         |
| 1     | Unexpandable |
| 2     | Expandable   |

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

The **sdev-client** library adds support for system message 509.

```
508    "Your revenge to <t> has succeeded!"
509    "<t> killed  you <v> time(s)."
```

## Skills

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

## Chaotic Squares

### ItemSynthesis.ini

Use the following example to get started:

```ini
;PSM_Client\Bin\Data\ItemSynthesis.ini

[ItemSynthesis_1]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=6
CreateCount=1

[ItemSynthesis_2]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=13
CreateCount=1

[ItemSynthesis_3]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=19,19,19,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=20
CreateCount=1

[ItemSynthesis_4]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=26,26,26,26,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=27
CreateCount=1

[ItemSynthesis_5]
ItemID=102073
SuccessRate=80
MaterialType=30,30,30,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialTypeID=33,33,33,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
MaterialCount=1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
CreateType=30
CreateTypeID=34
CreateCount=1

[ItemSynthesis_6]
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
constexpr auto gold_per_percentage = 100'000'000;
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

| Version    | Locale | Patch     | Supported          |
|------------|--------|-----------|--------------------|
| 0x16012100 | ES     | ps0171    | :white_check_mark: |
| 0x16021200 | PT     | ps0182    | :x:                |
| 0x16032100 | PT     | ps0189    | :x:                |

## Perfect Lapisian Combination

Use item `101101` to activate the window. The `ReqLuc` value is the number of lapisian required for combination. See system message `510` for more information.

## Safety Enchant Scroll

| ItemId | Effect |
|--------|--------|
| 101090 | 103    |
| 101132 | 103    |

## Mailbox

This feature will not be implemented.
