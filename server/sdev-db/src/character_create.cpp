#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/include/CUser.h>
#include <sdev/include/shaiya/include/SConnection.h>
#include <sdev/include/shaiya/include/SDatabase.h>
#include <sdev/include/shaiya/include/SDatabasePool.h>
using namespace shaiya;

namespace character_create
{
    #pragma pack(push, 1)
    // custom
    struct NameAvailableOutgoing
    {
        UINT16 opcode{ 0x40D };
        UserId userId;
        bool available;
    };
    #pragma pack(pop)

    bool is_name_available(SQLPOINTER name)
    {
        auto db = SDatabasePool::AllocDB();
        if (!db)
            return false;

        SDatabase::Prepare(db);

        std::string query("SELECT CharName FROM [PS_GameData].[dbo].[Chars] WHERE CharName=CAST(? AS VARCHAR) AND Del=0;");
        SQLBindParameter(db->stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 19, 0, name, 0, nullptr);
        SQLPrepareA(db->stmt, reinterpret_cast<SQLCHAR*>(query.data()), SQL_NTS);

        if (SQLExecute(db->stmt))
        {
            SDatabase::WriteErrorLog(db);
            SDatabasePool::FreeDB(db);
            return false;
        }

        SQLINTEGER rowCount = -1;
        SQLRowCount(db->stmt, &rowCount);

        SDatabasePool::FreeDB(db);
        return !rowCount;
    }

    void name_available_handler(CUser* user, SQLPOINTER name)
    {
        NameAvailableOutgoing packet{ 0x40D, user->userId, is_name_available(name) };

        if (!user->connection)
            return;

        SConnection::Send(user->connection, &packet, sizeof(NameAvailableOutgoing));
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

        lea edx,[eax+0x6]

        push edx // name
        push ecx // user
        call character_create::name_available_handler
        add esp,0x8

        popad

        mov al,0x1
        retn
    }
}

void hook::character_create()
{
    // CUser::PacketUserChar switch
    util::detour((void*)0x4061D3, naked_0x4061D3, 6);
}
