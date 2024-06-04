# Documentation

The file is a 6.4 PT client that arrived in patch 182. The only ones that have touched it are the person who unpacked it (thanks, NatS0e) and yours truly. Since I can account for what's been done to the file, I'll make an effort to support it.

## Build Version

`0x16021200`

## OEP

`0x637C68`

## Sections

It appears the original import address table was wiped from the file when it was packed. Sections 3, 4, 5 and 6 have been filled with null bytes.

1: `.text` (application machine code)

2: `.rsrc` (resources)

7: `.code` (IAT, EP and a PE header)

## Imports

There are two duplicate imports. I recommend editing one of them instead of adding a new import to the table.

| DllName     | Function          | Thunk RVA    |
|-------------|-------------------|--------------|
| kernel32    | VirtualProtect    | 0x2732F00    |
| kernel32    | Sleep             | 0x2732F04    |

Example:

| DllName     | Function          | Thunk RVA    |
|-------------|-------------------|--------------|
| kernel32    | VirtualProtect    | 0x2732F00    |
| sdev        | DllExport         | 0x2732F04    |

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

## Entry Point

```
02B31600  60             PUSHAD // EP
02B31601  BD F815B102    MOV EBP,game.02B115F8 // the page protection output variable
02B31606  BF 00004000    MOV EDI,game.00400000 // the base address
02B3160B  55             PUSH EBP
02B3160C  6A 04          PUSH 4 // PAGE_READWRITE
02B3160E  68 00100000    PUSH 1000 // 4096
02B31613  57             PUSH EDI
02B31614  FF15 002FB102  CALL DWORD PTR DS:[<&kernel32.VirtualProtect>]
02B3161A  B9 00100000    MOV ECX,1000 // 4096
// the bytes from 0x2B10000 to 0x2B11000 are a PE header
02B3161F  BE 0000B102    MOV ESI,game.02B10000
02B31624  F3:A4          REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
// hint: this is a good place to add a LoadLibraryA call
02B31626  61             POPAD
02B31627  E9 3C66B0FD    JMP game.00637C68 // OEP
```

## Notes

The following patch fixes the recovery packet handler.

```
005942D8  01B0 58010000  ADD DWORD PTR DS:[EAX+158],ESI
005942DE  0190 60010000  ADD DWORD PTR DS:[EAX+160],EDX
005942E4  0188 68010000  ADD DWORD PTR DS:[EAX+168],ECX
```

This modification is in the library. I'll leave this note here in case someone wants to patch the file.

```
// speed recreation
004C4D2E  6A 02  PUSH 2
```
```
// speed enhance
005015FF  6A 02  PUSH 2
00501601  6A 02  PUSH 2
00501630  6A 02  PUSH 2
00501632  6A 02  PUSH 2
00501643  6A 03  PUSH 3
0050164C  6A 03  PUSH 3
```
