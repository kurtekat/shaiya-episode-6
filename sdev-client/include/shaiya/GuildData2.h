#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // GUILD_DATA2
    struct GuildData2
    {
        uint32_t id;            //0x00
        String<25> name;        //0x04
        String<21> masterName;  //0x1D
        String<65> remark;      //0x32
        uint8_t rank;           //0x73
        uint32_t rankPoints;    //0x74
        // 0x78

        static GuildData2* Find(unsigned guildId);
    };
    #pragma pack(pop)

    static_assert(sizeof(GuildData2) == 0x78);
}
