# Build Version

`0x13120600`

## OEP

`0x61E5E8`

## Sections

`.text` (application machine code)

`.rsrc` (resources)

`.code` (IAT, entry point, and PE header)

# Notes

This is a 6.3 PT client. The auction house board seems to be non-existent. The remaining sections left over from packing/unpacking have been filled with null bytes. A call to LoadLibraryA was added near the entry point.

```
02AF1600  60             PUSHAD
02AF1601  BD F815AF02    MOV EBP,game.02AF15F8
02AF1606  BF 00004000    MOV EDI,game.00400000
02AF160B  55             PUSH EBP
02AF160C  6A 04          PUSH 4
02AF160E  68 00100000    PUSH 1000
02AF1613  57             PUSH EDI
02AF1614  FF15 002FAF02  CALL DWORD PTR DS:[<&kernel32.VirtualProtect>]
02AF161A  B9 00100000    MOV ECX,1000
02AF161F  BE 0000AF02    MOV ESI,game.02AF0000
02AF1624  F3:A4          REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
02AF1626  68 3816AF02    PUSH game.02AF1638 // sdev.dll
02AF162B  FF15 58B37200  CALL DWORD PTR DS:[<&kernel32.LoadLibraryA>]
02AF1631  61             POPAD
02AF1632  E9 B1CFB2FD    JMP game.0061E5E8 // OEP
```

## SData Specifications

| Name          | Format   |
|---------------|----------|
| Item          | EP6      |
| Monster       | EP5      |
| NpcQuest      | EP5      |
| NpcSkill      | EP5      |
| Skill         | EP5      |

## Features

* Pets and Costumes
* Item Duration

# sdev.dll

The project addresses the following issues:

* Appearance/sex change bug

* Disguise removal bug

* Lag when adding/removing equipment

* Chat color exploit
