#include <array>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/SDatabase.h"
using namespace shaiya;

short hook_0x406A8C(SDatabase* db, char* username, char* password, unsigned lowPart, unsigned highPart, char* ipv4)
{
    ULARGE_INTEGER sessionId{ lowPart, highPart };

    std::array<char, 1024> buffer{};
    std::snprintf(buffer.data(), buffer.size(), "EXEC [PS_UserData].[dbo].[usp_Try_GameLogin_Taiwan] ?,?,%llu,'%s';",
        sessionId.QuadPart, ipv4);

    if (SDatabase::PrepareSql(db, buffer.data()))
        return -1;

    // Parameterize user-supplied data

    short result = 0;
    result = SDatabase::BindParameter(db, 1, 32, SQL_C_CHAR, SQL_VARCHAR, username, nullptr, SQL_PARAM_INPUT);
    result = SDatabase::BindParameter(db, 2, 32, SQL_C_CHAR, SQL_VARCHAR, password, nullptr, SQL_PARAM_INPUT);

    if (result)
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
        call hook_0x406A8C
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
