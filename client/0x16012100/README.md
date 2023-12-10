# Build Version

`0x16012100`

## OEP

`0x637B38`

## Sections

`.text` (application machine code)

`.rsrc` (resources)

`.code` (IAT, entry point, and PE header)

# Notes

This is a 6.4 PT client. The sections left over from packing/unpacking have been filled with null bytes. A call to LoadLibraryA was added near the entry point.

```
02B61600  60             PUSHAD
02B61601  BD F815B602    MOV EBP,game.02B615F8
02B61606  BF 00004000    MOV EDI,game.00400000
02B6160B  55             PUSH EBP
02B6160C  6A 04          PUSH 4
02B6160E  68 00100000    PUSH 1000
02B61613  57             PUSH EDI
02B61614  FF15 002FB602  CALL DWORD PTR DS:[<&kernel32.VirtualProtect>]
02B6161A  B9 00100000    MOV ECX,1000
02B6161F  BE 0000B602    MOV ESI,game.02B60000
02B61624  F3:A4          REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
02B61626  68 3816B602    PUSH game.02B61638 // sdev.dll
02B6162B  FF15 58637400  CALL DWORD PTR DS:[<&kernel32.LoadLibraryA>]
02B61631  61             POPAD
02B61632  E9 0165ADFD    JMP game.00637B38 // OEP
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
