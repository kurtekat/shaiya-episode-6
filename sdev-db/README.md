# Documentation

This library is for the dbAgent service. It adds support for the character list packet (equipment) and the name availability packet.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

## Binary

The file was patched to undo an edit that causes item mall purchase duplicates.

```
// bug
00407942  mov dword ptr [ebx+8],1

// original code
00407942  mov dword ptr [ebx+8],0
```
