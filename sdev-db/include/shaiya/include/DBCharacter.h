#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    struct CUser;

    struct DBCharacter
    {
        static BOOL ReloadPoint(CUser* user/*esi*/);
    };
}
