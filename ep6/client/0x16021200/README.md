#### Build Version

`0x16021200`

#### OEP

`0x637C68`

#### Sections

`.text`

`.rsrc`

`.code`

* The `.text` section contains the application machine code

* The `.rsrc` section contains resources

* The `.code` section contains the IAT, entry point, and a PE header

* The remaining sections left over from packing/unpacking have been filled with null bytes

#### Notes

A call to LoadLibraryA was added near the entry point.

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

#### sdev.dll

The project addresses the following issues:

* Appearance/sex change bug

* Weapon enchant bug

* HP/MP/SP bug

* Lag when adding/removing equipment

* Market search index

It also modifies the client to accept the older `0x2602` packet by ignoring the dates in the product item definition.

```cpp
struct ProductItemDefinition
{
    UINT8 bag;
    UINT8 slot;
    UINT8 type;
    UINT8 typeId;
    UINT8 count;
    // ep6 fields
    ULONG fromDate;
    ULONG toDate;
};
```
