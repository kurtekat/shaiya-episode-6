# Environment

Windows 10

Visual Studio 2019

C++ 20

# String

| Container        | Literal    | Char    | 
|------------------|------------|---------|
| `std::string`    | `"abc"s`   | `'x'`   |
| `std::wstring`   | `L"abc"s`  | `L'x'`  |
| `std::u8string`  | `u8"abc"s` | `u8'x'` |
| `std::u16string` | `u"abc"s`  | `u'x'`  |
| `std::u32string` | `U"abc"s`  | `U'x'`  |

## `split`

Splits a string into a maximum number of substrings based on a specified delimiting string.

```cpp
template<template<typename...> class Container, class Char>
inline auto split(const std::basic_string<Char>& str, const std::basic_string_view<Char> sep, int max);
```

```cpp
template<template<typename...> class Container, class Char>
inline auto split(const std::basic_string<Char>& str, const Char* sep, int max);
```

Splits a string into substrings based on a specified delimiting string.

```cpp
template<template<typename...> class Container, class Char>
inline auto split(const std::basic_string<Char>& str, const std::basic_string_view<Char> sep);
```

```cpp
template<template<typename...> class Container, class Char>
inline auto split(const std::basic_string<Char>& str, const Char* sep);
```

Splits a string into a maximum number of substrings based on a specified delimiting character.

```cpp
template<template<typename...> class Container, class Char>
inline auto split(const std::basic_string<Char>& str, const Char sep, int max);
```

Splits a string into substrings based on a specified delimiting character.

```cpp
template<template<typename...> class Container, class Char>
inline auto split(const std::basic_string<Char>& str, const Char sep);
```

### Example

```cpp
#include <iostream>
#include <set>
#include <string>
#include <extensions/include/string.hpp>

int main(int argc, char** argv)
{
    std::string str("1,2,3,4");
    auto set = ext::string::split<std::set>(str, ",");
    
    for (const auto& key : set)
    {
        std::cout << key << '\n';
    }

    return 0;
}
```

## `ltrim`

Removes leading white-space characters.

```cpp
template<class Char>
inline void ltrim(std::basic_string<Char>& str, const std::locale& loc = std::locale());
```

Removes leading elements that are equal to the specified character.

```cpp
template<class Char>
inline void ltrim(std::basic_string<Char>& str, const Char rhs);
```

Removes leading elements that are equal to any of the specified characters.

```cpp
template<class Char>
inline void ltrim(std::basic_string<Char>& str, const Char* rhs);
```

```cpp
template<class Char>
inline void ltrim(std::basic_string<Char>& str, const std::basic_string_view<Char> rhs);
```

## `rtrim`

Removes trailing white-space characters.

```cpp
template<class Char>
inline void rtrim(std::basic_string<Char>& str, const std::locale& loc = std::locale());
```

Removes trailing elements that are equal to the specified character.

```cpp
template<class Char>
inline void rtrim(std::basic_string<Char>& str, const Char rhs);
```

Removes trailing elements that are equal to any of the specified characters.

```cpp
template<class Char>
inline void rtrim(std::basic_string<Char>& str, const Char* rhs);
```

```cpp
template<class Char>
inline void rtrim(std::basic_string<Char>& str, const std::basic_string_view<Char> rhs);
```

## `trim`

Removes leading and trailing white-space characters.

```cpp
template<class Char>
inline void trim(std::basic_string<Char>& str, const std::locale& loc = std::locale());
```

Removes leading and trailing elements that are equal to the specified character.

```cpp
template<class Char>
inline void trim(std::basic_string<Char>& str, const Char rhs);
```

Removes leading and trailing elements that are equal to any of the specified characters.

```cpp
template<class Char>
inline void trim(std::basic_string<Char>& str, const Char* rhs);
```

```cpp
template<class Char>
inline void trim(std::basic_string<Char>& str, const std::basic_string_view<Char> rhs);
```

## `ltrim_if`

Removes leading elements for which the unary predicate returns true.

```cpp
template<class Char, class UnaryPred>
inline void ltrim_if(std::basic_string<Char>& str, UnaryPred pred);
```

## `rtrim_if`

Removes trailing elements for which the unary predicate returns true.

```cpp
template<class Char, class UnaryPred>
inline void rtrim_if(std::basic_string<Char>& str, UnaryPred pred);
```

## `trim_if`

Removes leading and trailing elements for which the unary predicate returns true.

```cpp
template<class Char, class UnaryPred>
inline void trim_if(std::basic_string<Char>& str, UnaryPred pred);
```

## `ltrim_copy`

Removes leading white-space characters.

```cpp
template<class Char>
inline auto ltrim_copy(const std::basic_string<Char>& str, const std::locale& loc = std::locale());
```

Removes leading elements that are equal to the specified character.

```cpp
template<class Char>
inline auto ltrim_copy(const std::basic_string<Char>& str, const Char rhs);
```

Removes leading elements that are equal to any of the specified characters.

```cpp
template<class Char>
inline auto ltrim_copy(const std::basic_string<Char>& str, const Char* rhs);
```

```cpp
template<class Char>
inline auto ltrim_copy(const std::basic_string<Char>& str, const std::basic_string_view<Char> rhs);
```

## `rtrim_copy`

Removes trailing white-space characters.

```cpp
template<class Char>
inline auto rtrim_copy(const std::basic_string<Char>& str, const std::locale& loc = std::locale());
```

Removes trailing elements that are equal to the specified character.

```cpp
template<class Char>
inline auto rtrim_copy(const std::basic_string<Char>& str, const Char rhs);
```

Removes trailing elements that are equal to any of the specified characters.

```cpp
template<class Char>
inline auto rtrim_copy(const std::basic_string<Char>& str, const Char* rhs);
```

```cpp
template<class Char>
inline auto rtrim_copy(const std::basic_string<Char>& str, const std::basic_string_view<Char> rhs);
```

## `trim_copy`

Removes leading and trailing white-space characters.

```cpp
template<class Char>
inline auto trim_copy(const std::basic_string<Char>& str, const std::locale& loc = std::locale());
```

Removes leading and trailing elements that are equal to the specified character.

```cpp
template<class Char>
inline auto trim_copy(const std::basic_string<Char>& str, const Char rhs);
```

Removes leading and trailing elements that are equal to any of the specified characters.

```cpp
template<class Char>
inline auto trim_copy(const std::basic_string<Char>& str, const Char* rhs);
```

```cpp
template<class Char>
inline auto trim_copy(const std::basic_string<Char>& str, const std::basic_string_view<Char> rhs);
```

## `ltrim_copy_if`

Removes leading elements for which the unary predicate returns true.

```cpp
template<class Char, class UnaryPred>
inline auto ltrim_copy_if(const std::basic_string<Char>& str, UnaryPred pred);
```

## `rtrim_copy_if`

Removes trailing elements for which the unary predicate returns true.

```cpp
template<class Char, class UnaryPred>
inline auto rtrim_copy_if(const std::basic_string<Char>& str, UnaryPred pred);
```

## `trim_copy_if`

Removes leading and trailing elements for which the unary predicate returns true.

```cpp
template<class Char, class UnaryPred>
inline auto trim_copy_if(const std::basic_string<Char>& str, UnaryPred pred);
```

# Inspiration

[Boost.Algorithm](https://github.com/boostorg/algorithm)

[C++ Standard Library](https://github.com/microsoft/STL) (Microsoft)

# References

https://en.cppreference.com/w/cpp/types/type_identity.html

https://stackoverflow.com/a/77072188
