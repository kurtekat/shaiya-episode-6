### ps_game

The max level is 70. It is possible to change, but there are some issues that need to be understood. I have seen this discussed more than once, so I will try my best to explain.

1. `CGameData::LoadExp` and `CGameData::LoadStatus` are not designed to support writing values beyond level 70 to memory. In the case of `ExpDefs`, modifying the loop to read more rows from the query result is not problem, but without checking the memory address of each level and grow, I cannot guarantee the integrity of the data once everything is loaded. 

2. The memory used to store values read from the database is not heap allocated. `StatusDefs` values will be overwritten at some point. I can only confirm this with a hard mode priest from level 72 and beyond. The data was either corrupted or non-existent.

3. `Exp` values should not exceed `4294967295`. The values in `PS_GameDefs.dbo.ExpDefs` will be 10 times the amount in memory.

I replaced the all the level 80 comparisons I found with 70. Since then, priest/oracle status bugs seem to have disappeared. More testing is required to confirm. The section named `.yong` that was removed from this file contained two hooks that appear to have been a workaround.

```
[ENABLE]
alloc(newmem,128)
label(original)
// CUser::InitEquipment
newmem:
// user->job
cmp byte ptr[esi+00000134],05 // priest/oracle
jl original
// user->level
cmp word ptr[esi+00000136],50 // 80
jl original
mov ebp,04
jmp 004613A0

original:
movzx ebp,byte ptr[esi+00000134]
jmp 004613A0

00461399:
jmp newmem

[DISABLE]
dealloc(newmem)
00461399:
movzx ebp,byte ptr[esi+00000134]

```

```
[ENABLE]
alloc(newmem,128)
label(original)
// CUser::StatResetStatus
newmem:
// user->job
cmp byte ptr[edi+00000134],05 // priest/oracle
jl original
// user->level
cmp byte ptr[edi+00000136],50 // 80
jl original
mov eax,04
jmp 0048F773
original:
movzx eax,byte ptr[edi+00000134]
jmp 0048F773

0048F76C:
jmp newmem

[DISABLE]
dealloc(newmem)
0048F76C:
movzx eax,byte ptr[edi+00000134]
```

### ps_dbAgent

This file has two modifications. The first is a dupe solution released by [Trayne01](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3798719-release-episode-5-4-packet-based-dupe-fix.html). It requires a modified version of the `[dbo].[usp_Save_Char_Info_E]` stored procedure, which can be found in the in this repository or in the archive released by the developer. The second calls `DBCharacter::ReloadPoint` which executes `[dbo].[usp_Read_User_CashPoint_UsersMaster]` get the user's cash points.

```
[ENABLE]
alloc(newmem,128)
label(return)
// CUser::OnDispatch
newmem:
call 004235D0 // DBCharacter::ReloadPoint
// original
call 00405380 // CUser::LoadCharacter
jmp return

0040478E:
jmp newmem
return:

[DISABLE]
dealloc(newmem)
0040478E:
call 00405380
```

### SQL Server

The procedures listed below need to be installed for the cash shop to work as intended. If you receive an error, change `ALTER` to `CREATE` and try again. The code in this repository works with modern versions of SQL Server so please do not use outdated software.

[dbo].[usp_Read_User_CashPoint_UsersMaster]

[dbo].[usp_Save_User_BuyPointItems2]

[dbo].[usp_Save_User_GiftPointItems2]

[dbo].[usp_Update_UserPoint]
