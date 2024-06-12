#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/common/SDatabase.h>
#include <shaiya/include/common/SDatabasePool.h>
#include <shaiya/include/network/dbAgent/incoming/0400.h>
#include <shaiya/include/network/dbAgent/outgoing/0400.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CUser.h"
using namespace shaiya;

namespace user_character
{
    bool is_name_available(char* name)
    {
        auto db = SDatabasePool::AllocDB();
        if (!db)
            return false;

        SDatabase::Prepare(db);

        std::string query("SELECT CharName FROM [PS_GameData].[dbo].[Chars] WHERE CharName=? AND Del=0;");
        if (SDatabase::PrepareSql(db, query.c_str()))
            return false;

        if (FAILED(SQLBindParameter(db->stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, std::strlen(name), 0, name, 19, nullptr)))
            return false;

        if (SDatabase::ExecuteSql(db))
            return false;

        long rowCount = SQL_NULL_DATA;
        if (FAILED(SQLRowCount(db->stmt, &rowCount)))
            return false;

        SDatabasePool::FreeDB(db);
        return !rowCount;
    }

    void name_available_handler(CUser* user, DBAgentCharNameAvailableIncoming* incoming)
    {
        incoming->name[incoming->name.size() - 1] = '\0';
        bool available = is_name_available(incoming->name.data());

        if (!user->connection)
            return;

        DBAgentCharNameAvailableOutgoing outgoing(user->userId, available);
        SConnection::Send(user->connection, &outgoing, sizeof(DBAgentCharNameAvailableOutgoing));
    }
}

unsigned u0x4061D9 = 0x4061D9;
void __declspec(naked) naked_0x4061D3()
{
    __asm
    {
        // original
        add edx,-0x402
        cmp edx,0xB
        je case_0x40D
        jmp u0x4061D9

        case_0x40D:
        pushad

        push eax // packet
        push ecx // user
        call user_character::name_available_handler
        add esp,0x8

        popad

        mov al,0x1
        retn
    }
}

void hook::user_character()
{
    // CUser::PacketUserChar switch
    util::detour((void*)0x4061D3, naked_0x4061D3, 6);
}
