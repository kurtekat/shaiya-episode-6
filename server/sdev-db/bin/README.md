# Documentation

The file is from [this](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3798719-release-episode-5-4-packet-based-dupe-fix.html) release. The following patch was applied to undo an edit that causes an item mall purchase dupe.

```
// bug
00407942  mov dword ptr [ebx+8],1

// original code
00407942  mov dword ptr [ebx+8],0
```
