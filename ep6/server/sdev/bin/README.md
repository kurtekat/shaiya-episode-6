### ps_game

The max level is 70. Of course, it can be increased with Cheat Engine, but there are some issues that need to be understood. I have seen this discussed more than once, so I will try my best to explain.

`CGameData::LoadExp` and `CGameData::LoadStatus` are not designed to support writing values higher than level 70 to memory. In the case of `ExpDefs`, modifying the loop to read more rows from the query result is possible, but without checking the address of each level and grow, (which I will not do) I cannot guarantee the values in memory will match what is stored the database.

The memory used to store values read from the database is not heap allocated. `StatusDefs` values for level 72 and greater will be overwritten at some point. `Exp` values should not exceed `4294967295`. The values in `ExpDefs` will become around 10 times the amount stored in the database.
