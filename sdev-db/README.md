# Documentation

This library is for the dbAgent service. It adds support for the character list packet (equipment slots) and the name availability packet. Incoming and outgoing packet types are named relative to the dbAgent service.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

## Binary

The file was patched to undo an edit that causes an item mall purchase duplicate.

```
// bug
00407942  mov dword ptr [ebx+8],1

// original code
00407942  mov dword ptr [ebx+8],0
```
