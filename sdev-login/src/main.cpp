#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/SDatabase.h"
using namespace shaiya;

short get_user_hook(SDatabase* db, char* username, char* password, uint lowPart, uint highPart, char* ipv4)
{
    short ret = 0;
    ULARGE_INTEGER sessionId{ lowPart, highPart };

    std::string query("EXEC [PS_UserData].[dbo].[usp_Try_GameLogin_Taiwan] ?,?,?,?");
    if (SDatabase::PrepareSql(db, query.c_str()))
        return -1;

    ret = SQLBindParameter(db->stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, std::strlen(username), 0, username, 32, nullptr);
    ret = SQLBindParameter(db->stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, std::strlen(password), 0, password, 32, nullptr);
    ret = SQLBindParameter(db->stmt, 3, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 0, 0, &sessionId, 0, nullptr);
    ret = SQLBindParameter(db->stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, std::strlen(ipv4), 0, ipv4, 16, nullptr);

    if (FAILED(ret))
        return -1;

    return SDatabase::ExecuteSql(db);
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

        push ebp // ipv4

        // sessionId
        push eax
        push ecx

        push esi // password
        push edi // username
        push ebx // database
        call get_user_hook
        add esp,0x18
        test ax,ax

        popad

        jne _0x406B24
        jmp u0x406ADF

        _0x406B24:
        jmp u0x406B24
    }
}

// Author: Cups
// Date: 31/10/2017

unsigned u0x404E89 = 0x404E89;
unsigned u0x404FAE = 0x404FAE;
void __declspec(naked) naked_0x404E84()
{
    __asm
    {
        // original
        push eax
        mov ebx,ecx
        mov eax,esi

        // rsa key length
        cmp ecx,0x80
        jne _0x404FAE
        jmp u0x404E89

        _0x404FAE:
        jmp u0x404FAE
    }
}

void Main()
{
    // GetUser
    util::detour((void*)0x406A8C, naked_0x406A8C, 7);
    // CUserCrypto::KeyInit
    util::detour((void*)0x404E84, naked_0x404E84, 5);
}
