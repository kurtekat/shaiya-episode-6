# Shaiya Episode 6 - Server

A library that modifies ps_game to make it compatible with episode 6 clients.

## Getting Started

Navigate to the `bin` directory and read the documentation. Install the binaries to `SERVER\PSM_Client\Bin` and execute the store procedures in SQL Server Management Studio. Open the project in Visual Studio, target the x86 platform, and build the solution. Copy the library to `SERVER\PSM_Client\Bin` and use `ps_game.ct` to inject the library. 

Note: calling `LoadLibraryA` before ps_session packet `0x105` arrives will result in `g_nPayLetterEnable` being set to `false`.

When the library attempts to establish a trusted connection with SQL Server, it will try to log in with the `NT AUTHORITY\SYSTEM` account. One way to ensure the login succeeds is to add `NT AUTHORITY\SYSTEM` to the `sysadmin` role.

```sql
ALTER SERVER ROLE [sysadmin] ADD MEMBER [NT AUTHORITY\SYSTEM]

```

To use this library with episode 5 projects, comment the `SHAIYA_EP6` macro and the episode 6 functions.

```cpp
// common.h
//#define SHAIYA_EP6
```

```cpp
// main.cpp
/*
hook::packet_character();
hook::packet_gem();
hook::packet_market();
hook::packet_myshop();
hook::user_equipment();
hook::user_shape();
hook::user_status();
*/
```

## Contributors

Everyone is welcome to submit a pull request or open an issue. Whether or not the code is merged, your time and effort is appreciated. The life cycle of this project will end if the community does not support it in some way or another. There are many ways people can contribute. Please browse the [issues](https://github.com/kurtekat/Shaiya/issues) before contributing.

### Guidelines

#### C++

Most expressions in the `shaiya` namespace match the debug information, etc. The intent is to keep it that way. Aside from that, use as little as machine code as possible. Please follow the style in the code block below. It shows the address of the detour and where it returns without having to look elsewhere.

```
unsigned u0x47A00C = 0x47A00C;
void __declspec(naked) naked_0x47A003()
{
    __asm
    {
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_compose_handler
        add esp,0x8
        
        popad

        jmp u0x47A00C
    }
}
```

#### .NET

The source and headers contain `pragma` directives to tell the compiler whether the code is managed or unmanaged. It will default to managed, so please pay attention to the warnings. For example: the `naked` attribute and `DllMain` will emit a warning.

```
#pragma managed
#pragma unmanaged
```
