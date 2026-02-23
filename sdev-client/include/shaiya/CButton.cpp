#include "CButton.h"
using namespace shaiya;

void CButton::Init(CButton* button)
{
    typedef void(__thiscall* LPFN)(CButton*);
    (*(LPFN)0x54FCE0)(button);
}

void CButton::Draw(CButton* button, int windowPosX, int windowPosY)
{
    typedef void(__thiscall* LPFN)(CButton*, int, int);
    (*(LPFN)0x551B40)(button, windowPosX, windowPosY);
}

BOOL CButton::Func_0x54FEB0(CButton* button, int unknown)
{
    typedef BOOL(__thiscall* LPFN)(CButton*, int);
    return (*(LPFN)0x54FEB0)(button, unknown);
}

void CButton::Func_0x551860(
    CButton* button,int windowPosX,int windowPosY, int param3, int param4, int param5, int param6, int param7, int param8, int param9, 
    const char* fileName, int param11, int param12, 
    int param13, 
    float param14, float param15, float param16, float param17,
    float param18, float param19, float param20, float param21,
    float param22, float param23, float param24, float param25,
    float param26, float param27, float param28, float param29,
    float param30, float param31, float param32, float param33,
    int param34
)
{
    typedef void(__thiscall* LPFN)(
        CButton*, int, int, int, int, int, int, int, int, int, 
        const char*, 
        int, int, int, 
        float, float, float, float, 
        float, float, float, float, 
        float, float, float, float, 
        float, float, float, float, 
        float, float, float, float, 
        int);

    (*(LPFN)0x551860)(
        button, windowPosX, windowPosY,
        param3, param4, param5, param6, param7, param8, param9,
        fileName, param11, param12, 
        param13, 
        param14, param15, param16, param17, 
        param18, param19, param20, param21, 
        param22, param23, param24, param25, 
        param26, param27, param28, param29, 
        param30, param31, param32, param33, 
        param34);
}

BOOL CButton::Func_0x550A10(CButton* button)
{
    typedef BOOL(__thiscall* LPFN)(CButton*);
    return (*(LPFN)0x550A10)(button);
}

void CButton::Reset(CButton* button)
{
    typedef void(__thiscall* LPFN)(CButton*);
    (*(LPFN)0x54FE50)(button);
}
