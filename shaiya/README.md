# Documentation

This library contains common types and packet definitions. The other projects depend on this library.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

# DateTime

The encoded date/time value type is an unsigned 32-bit integer.

## Range

```
2000-01-01 00:00:00 // 4325376
2063-12-31 23:59:59 // 4282351355
```

## References

[Eden](https://github.com/tristonplummer/Eden/blob/master/eden/common/include/shaiya/common/datatypes/ShaiyaTime.hpp)
