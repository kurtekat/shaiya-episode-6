# Documentation

This library contains memory utilities, etc. The other projects depend on this library.

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

# String

Constants require a template parameter.

```cpp
#include <iostream>
#include <util/string/string.hpp>

int main(int argc, char** argv)
{
    std::locale::global(std::locale("es-ES"));

    const wchar_t* str = L"Kurt <3 Bebé";
    auto vec = util::string::split<wchar_t>(str, L' ');
    for (const auto& e : vec)
        std::wcout << e << L'\n';

    return 0;
}
```

Containers do not require a template parameter.

```cpp
#include <iostream>
#include <util/string/string.hpp>

int main(int argc, char** argv)
{
    std::locale::global(std::locale("es-ES"));

    std::wstring str(L"Kurt <3 Bebé");
    auto vec = util::string::split(str, L' ');
    for (const auto& e : vec)
        std::wcout << e << L'\n';

    return 0;
}
```