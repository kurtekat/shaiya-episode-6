### ps_game

This file is optional. The machine code has no known modifications.

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
