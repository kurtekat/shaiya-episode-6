#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#include <include/main.h>
#include <sdev/include/shaiya/include/SDatabase.h>
#include <util/include/util.h>
using namespace shaiya;

SQLRETURN get_user_ex(SDatabase* db, SQLPOINTER username, SQLPOINTER password, DWORD lowPart, LONG highPart, SQLPOINTER ipv4Addr)
{
    LARGE_INTEGER sessionId{ lowPart, highPart };
    std::string query("EXEC usp_Try_GameLogin_Taiwan ?,?,?,?");

    SQLBindParameter(db->stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_LONGVARCHAR, 32, 0, username, 0, nullptr);
    SQLBindParameter(db->stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_LONGVARCHAR, 32, 0, password, 0, nullptr);
    SQLBindParameter(db->stmt, 3, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &sessionId, 0, nullptr);
    SQLBindParameter(db->stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_LONGVARCHAR, 15, 0, ipv4Addr, 0, nullptr);
    SQLPrepareA(db->stmt, reinterpret_cast<SQLCHAR*>(query.data()), SQL_NTS);
    return SQLExecute(db->stmt);
}

unsigned u0x406B24 = 0x406B24;
unsigned u0x406ADF = 0x406ADF;
void __declspec(naked) naked_0x406A8C()
{
    __asm
    {
        pushad

        mov ebp,[esp+0x44C]
        mov eax,[esp+0x448]
        mov ecx,[esp+0x444]
        mov esi,[esp+0x440]
        mov edi,[esp+0x43C]

        push ebp // ipv4Addr

        // sessionId
        push eax
        push ecx

        push esi // password
        push edi // username
        push ebx // database
        call get_user_ex
        add esp,0x18
        test ax,ax

        popad

        jne _0x406B24
        jmp u0x406ADF

        _0x406B24:
        jmp u0x406B24
    }
}

void hook::get_user()
{
    // ps_login.GetUser
    util::detour((void*)0x406A8C, naked_0x406A8C, 7);
}
