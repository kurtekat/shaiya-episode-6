# Documentation

This library is for Shaiya PT client 182 modifications. The DirectX SDK installer should create a system environment variable named `DXSDK_DIR` that specifies the installation directory.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

[Microsoft DirectX SDK (June 2010)](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

## Binaries

The files have been partially restored to their original condition. I recommend using [PE Bear](https://github.com/hasherezade/pe-bear) to add new imports.

![Capture](https://github.com/user-attachments/assets/6cc6d390-aaae-4f36-b362-f08ce9f243f5)

### SData Formats

| Name     | Format |
|----------|--------|
| Item     | EP6.4  |
| Monster  | EP5    |
| NpcQuest | EP6    |
| NpcSkill | EP6    |
| Skill    | EP6    |

### Chat Color Exploit

```
STATUS_STACK_BUFFER_OVERRUN encountered
A breakpoint instruction (__debugbreak() statement or a similar call) was executed in game.exe.
```

I believe this blog post explains what happens:

https://devblogs.microsoft.com/oldnewthing/20080404-00/?p=22863

Increasing the stack allocation in two functions seems to be a good solution.

```
// ps0182 (PT)
0047DB76:
sub esp,000005BC

0047DB83:
mov [esp+000005B8],eax

0047E871:
mov ecx,[esp+000005C4]

0057C280:
sub esp,0000054C

0057C28D:
mov [esp+00000548],eax

0057C297:
mov esi,[esp+0000055C]

0057C9F9:
mov ecx,[esp+00000558]

0057CA0B:
add esp,0000054C
```

```
// ps0171 (ES)
0047D896:
sub esp,000005BC

0047D8A3:
mov [esp+000005B8],eax

0047E591:
mov ecx,[esp+000005C4]

0057C670:
sub esp,0000054C

0057C67D:
mov [esp+00000548],eax

0057C687:
mov esi,[esp+0000055C]

0057CDE9:
mov ecx,[esp+00000558]

0057CDFB:
add esp,0000054C
```

### Recovery

Episode 6.4 (and greater) clients do not add the values in the 0x505 packet handler.

```
// ps0171 (ES)
00594AC8  MOV DWORD PTR DS:[EAX+158],ESI
00594ACE  MOV DWORD PTR DS:[EAX+160],EDX
00594AD4  MOV DWORD PTR DS:[EAX+168],ECX

00594AEB  MOV DWORD PTR DS:[914478],ESI
00594AF1  MOV DWORD PTR DS:[91447C],EDX
00594AF7  MOV DWORD PTR DS:[914480],ECX
```

```
// ps0182 (PT)
005942D8  MOV DWORD PTR DS:[EAX+158],ESI
005942DE  MOV DWORD PTR DS:[EAX+160],EDX
005942E4  MOV DWORD PTR DS:[EAX+168],ECX

005942FB  MOV DWORD PTR DS:[914478],ESI
00594301  MOV DWORD PTR DS:[91447C],EDX
00594307  MOV DWORD PTR DS:[914480],ECX
```
