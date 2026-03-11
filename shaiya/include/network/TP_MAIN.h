#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct TP_MAIN_COMMAND
    {
        uint16_t opcode;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct TP_MAIN
    {
        uint16_t opcode;
        Array<uint8_t, 2044> command;
    };
    #pragma pack(pop)

    struct TP_MAIN_PTR
    {
        explicit TP_MAIN_PTR(TP_MAIN* ptr)
            : m_ptr{ ptr }
        {
        }

        template<class T>
        operator T* () const
        {
            return reinterpret_cast<T*>(m_ptr);
        }

        TP_MAIN* operator->() const
        {
            return m_ptr;
        }

    private:

        TP_MAIN* m_ptr{ nullptr };
    };

    #define SHAIYA_TP_MAIN_CAST(x) TP_MAIN_PTR(x)
}
