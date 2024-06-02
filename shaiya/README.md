# Documentation

This library contains types that two or more projects have in common. It also contains all the packet definitions.

# Notes

## Sending Notices

```cpp
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <sdev/include/shaiya/include/CUser.h>
#include <sdev/include/shaiya/include/CWorld.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/game/outgoing/F900.h>
using namespace shaiya;

void sendNoticeAll(const std::string& message)
{
    AdminCmdNoticeAllOutgoing notice(message);
    CWorld::SendAll(&notice, notice.length());
}

void sendNoticeTo(CUser* user, const std::string& message)
{
    AdminCmdNoticeToOutgoing notice(message);
    SConnection::Send(&user->connection, &notice, notice.length());
}

void sendNoticeTo(ULONG charId, const std::string& message)
{
    auto user = CWorld::FindUser(charId);
    if (!user)
        return;

    AdminCmdNoticeToOutgoing notice(message);
    SConnection::Send(&user->connection, &notice, notice.length());
}
```
