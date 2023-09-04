# Shaiya Episode 5 - Server

A library that modifies ps_game and ps_dbAgent to make the cash shop work and more.

## Getting Started

Navigate to the `bin` directory and read the documentation. Install the binaries to `SERVER\PSM_Client\Bin` and execute the store procedures in SQL Server Management Studio. Open the project in Visual Studio, target the x86 platform, and build the solution. Copy the library to `SERVER\PSM_Client\Bin` and use `ps_game.ct` to inject the library. 

Note: calling `LoadLibraryA` before ps_session packet `0x105` arrives will result in `g_nPayLetterEnable` being set to `false`. The intent is to use functions that are available to accomplish a task and avoid machine code as much as possible.
