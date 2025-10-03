#pragma once

namespace util
{
    /// <summary>
    /// Redirects execution to the destination (e.g., address).
    /// </summary>
    int detour(void* addr, void* dest, size_t size);

    /// <summary>
    /// ReadProcessMemory (see Microsoft docs)
    /// </summary>
    int read_memory(void* addr, void* dest, size_t size);

    /// <summary>
    /// WriteProcessMemory (see Microsoft docs)
    /// </summary>
    int write_memory(void* addr, const void* src, size_t size);

    /// <summary>
    /// memset (see C or C++ docs)
    /// </summary>
    int write_memory(void* addr, int value, size_t size);
}
