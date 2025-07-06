#pragma once

namespace util
{
    int detour(void* addr, void* dest, size_t size);
    int read_memory(void* addr, void* dest, size_t size);
    int write_memory(void* addr, const void* src, size_t size);
    int write_memory(void* addr, int value, size_t size);
}
