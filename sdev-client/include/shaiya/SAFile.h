#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SAFile
    {
        PAD(4);
        char* name;          //0x04
        PAD(12);
        int32_t nameLength;  //0x14
        PAD(8);
        int64_t offset;      //0x20
        int32_t length;      //0x28
        int32_t timestamp;   //0x2C
        // 0x30

        static int Open(const char* fileName, const char* mode);
        static void Close(int handle);
        static void Read(char* buffer, int elemSize, int elemCount, int handle);
    };
    #pragma pack(pop)

    static_assert(sizeof(SAFile) == 0x30);
}
