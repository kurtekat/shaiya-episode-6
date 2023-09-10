# Shaiya Episode 6 - Server

A library that modifies ps_game and ps_dbAgent to make them compatible with episode 6 clients.

## Getting Started

Navigate to the `bin` directory in both projects and read the documentation. Copy the binaries to `SERVER\PSM_Client\Bin` and execute the store procedures in SQL Server Management Studio. Open the project in Visual Studio, target the x86 platform, and build the solution. Copy the libraries to `SERVER\PSM_Client\Bin` and start the services. Use the provided `.ct` files to inject the libraries.

Note: calling `LoadLibraryA` before ps_session packet `0x105` arrives will result in `g_nPayLetterEnable` being set to `false`.

To use this library with episode 5 projects, comment the `SHAIYA_EP6` macro and the episode 6 functions. `sdev-db.dll` is not required for episode 5 projects.

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
