#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <util/util.h>
#include <shaiya/include/network/dbAgent/incoming/0400.h>
#include <shaiya/include/network/dbAgent/outgoing/0400.h>
#include "include/main.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/SDatabase.h"
#include "include/shaiya/SDatabasePool.h"
using namespace shaiya;

namespace character
{
    int check_char_name(char* name)
    {
        auto db = SDatabasePool::AllocDB();
        if (!db)
            return SQL_ERROR;

        SDatabase::Prepare(db);

        std::array<char, 1024> query{};
        std::snprintf(query.data(), query.size(), "{?=call usp_Check_Char_Name(?)}");

        int output = 0;
        int cbBlob = SQL_DATA_AT_EXEC;
        int result = 0;
        result = SDatabase::BindParameter(db, 1, 4, SQL_C_LONG, SQL_INTEGER, &output, &cbBlob, SQL_PARAM_OUTPUT);
        result = SDatabase::BindParameter(db, 2, 21, SQL_C_CHAR, SQL_VARCHAR, name, nullptr, SQL_PARAM_INPUT);
        result = SDatabase::PrepareSql(db, query.data());

        if (result)
        {
            SDatabasePool::FreeDB(db);
            return SQL_ERROR;
        }

        if (SDatabase::Query(db, query.data()))
        {
            SDatabasePool::FreeDB(db);
            return SQL_ERROR;
        }

        if (SDatabase::MoreResults(db))
        {
            SDatabasePool::FreeDB(db);
            return SQL_ERROR;
        }

        SDatabasePool::FreeDB(db);
        return output;
    }

    /// <summary>
    /// Handles incoming 0x410 packets.
    /// </summary>
    void handler_0x410(CUser* user, DBAgentCharNameAvailableIncoming* incoming)
    {
        incoming->name[incoming->name.size() - 1] = '\0';
        int result = check_char_name(incoming->name.data());

        if (!user->connection)
            return;

        DBAgentCharNameAvailableOutgoing outgoing{};
        outgoing.billingId = user->billingId;
        outgoing.available = result == TRUE;
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
        cmp edx,0xE
        je case_0x410
        jmp u0x4061D9

        case_0x410:
        pushad

        push eax // packet
        push ecx // user
        call character::handler_0x410
        add esp,0x8

        popad

        mov al,0x1
        retn
    }
}

void hook::character()
{
    // CUser::PacketUserChar switch
    util::detour((void*)0x4061D3, naked_0x4061D3, 6);
}
