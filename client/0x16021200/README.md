# Build Version

`0x16021200`

## OEP

`0x637C68`

## Sections

`.text` (application machine code)

`.rsrc` (resources)

`.code` (IAT, entry point, and PE header)

# Notes

This is a 6.4 PT client that arrived in patch 182. The sections left over from packing/unpacking have been filled with null bytes. A call to LoadLibraryA was added near the entry point.

```
02B11600  60             PUSHAD
02B11601  BD F815B102    MOV EBP,game.02B115F8
02B11606  BF 00004000    MOV EDI,game.00400000
02B1160B  55             PUSH EBP
02B1160C  6A 04          PUSH 4
02B1160E  68 00100000    PUSH 1000
02B11613  57             PUSH EDI
02B11614  FF15 002FB102  CALL DWORD PTR DS:[<&kernel32.VirtualProtect>]
02B1161A  B9 00100000    MOV ECX,1000
02B1161F  BE 0000B102    MOV ESI,game.02B10000
02B11624  F3:A4          REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
02B11626  68 3816B102    PUSH game.02B11638 // sdev.dll
02B1162B  FF15 58637400  CALL DWORD PTR DS:[<&kernel32.LoadLibraryA>]
02B11631  61             POPAD
02B11632  E9 3166B2FD    JMP game.00637C68 // OEP
```

## SData Specifications

| Name          | Format   |
|---------------|----------|
| Item          | EP6      |
| Monster       | EP5      |
| NpcQuest      | EP6      |
| NpcSkill      | EP6      |
| Skill         | EP6      |

## Features

* Pets, Costumes, and Wings
* Item Duration
* Synergies
* Toggleable Skills
* Chaotic Squares
* Town Teleport Scrolls
* Rune Combination
* Revenge Mark
