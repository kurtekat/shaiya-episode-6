#include <array>
#include <map>
#include <format>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0403.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
#include <shaiya/include/SDatabase.h>
#include <shaiya/include/SDatabasePool.h>
using namespace shaiya;

namespace ep6
{
    constexpr int max_character_slot_count = 5;
    constexpr int max_equipment_slot_count = 17;
    inline std::map<CUser*, std::array<Equipment0403, 5>> equipment_map{};

    #pragma pack(push, 1)
    // custom
    struct CharNameAvailableResponse
    {
        UINT16 opcode; // 0x40D
        ULONG userUid;
        bool available;
    };
    #pragma pack(pop)

    bool is_name_available(SQLPOINTER name)
    {
        auto db = SDatabasePool::AllocDB();

        if (!db)
            return false;

        SDatabase::Prepare(db);

        std::string query = "SELECT ISNULL(COUNT(*),0) FROM [PS_GameData].[dbo].[Chars] WHERE CharName=CAST(? AS VARCHAR) AND Del=0;";
        SQLBindParameter(db->stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 19, 0, name, 0, nullptr);
        SQLPrepareA(db->stmt, reinterpret_cast<SQLCHAR*>(query.data()), SQL_NTS);

        if (SQLExecute(db->stmt))
        {
            SDatabase::WriteErrorLog(db);
            SDatabasePool::FreeDB(db);
            return false;
        }

        if (SQLFetch(db->stmt))
        {
            SDatabase::WriteErrorLog(db);
            SDatabasePool::FreeDB(db);
            return false;
        }

        int count = 0;
        if (SQLGetData(db->stmt, 1, SQL_INTEGER, &count, 0, nullptr))
        {
            SDatabase::WriteErrorLog(db);
            SDatabasePool::FreeDB(db);
            return false;
        }

        SDatabasePool::FreeDB(db);
        return count == 0;
    }

    void char_name_available_handler(CUser* user, SQLPOINTER name)
    {
        CharNameAvailableResponse response{ 0x40D, user->userUid, is_name_available(name) };

        if (!user->connection)
            return;

        SConnection::Send(user->connection, &response, sizeof(CharNameAvailableResponse));
    }

    void send_character_list(CUser* user, bool sendCountry)
    {
        CharacterList character_list{};
        character_list.opcode = 0x403;
        character_list.userUid = user->userUid;
        character_list.sendCountry = sendCountry;
        character_list.count = 0;

        for (int i = 0; i < max_character_slot_count; ++i)
        {
            if (!user->character[i].id)
                continue;

            Character0403 character{};
            character.id = user->character[i].id;
            character.regDate = user->character[i].regDate;
            character.deleted = user->character[i].deleted;
            character.slot = user->character[i].slot;
            character.family = user->character[i].family;
            character.grow = user->character[i].grow;
            character.hair = user->character[i].hair;
            character.face = user->character[i].face;
            character.size = user->character[i].size;
            character.job = user->character[i].job;
            character.sex = user->character[i].sex;
            character.level = user->character[i].level;
            character.strength = user->character[i].strength;
            character.dexterity = user->character[i].dexterity;
            character.reaction = user->character[i].reaction;
            character.intelligence = user->character[i].intelligence;
            character.wisdom = user->character[i].wisdom;
            character.luck = user->character[i].luck;
            character.health = user->character[i].health;
            character.mana = user->character[i].mana;
            character.stamina = user->character[i].stamina;
            character.mapId = user->character[i].mapId;
            character.nameChange = user->character[i].nameChange;

            auto it = equipment_map.find(user);
            if (it != equipment_map.end())
                std::memcpy(&character.equipment, &it->second[i], sizeof(Equipment0403));
            else
                // better than nothing :P
                std::memcpy(&character.equipment, &user->character[i].equipment, sizeof(Equipment));

            std::memcpy(&character.cloakBadge, &user->character[i].cloakBadge, sizeof(CloakBadge));
            strncpy_s(character.charName, user->character[i].charName, sizeof(character.charName));

            std::memcpy(&character_list.list[i], &character, sizeof(Character0403));
            ++character_list.count;
        }

        if (!user->connection)
            return;

        constexpr int packet_size_without_list = 8;
        int packet_size = packet_size_without_list + (character_list.count * sizeof(Character0403));
        SConnection::Send(user->connection, &character_list, packet_size);
    }

    void hook_user_ctor(CUser* user)
    {
        auto it = equipment_map.find(user);
        if (it == equipment_map.end())
        {
            std::array<Equipment0403, 5> equipment{};
            auto pair = std::make_pair(user, equipment);
            equipment_map.insert(pair);
        }
    }

    void init_equipment(CUser* user, int characterSlot, int equipmentSlot, int type, int typeId)
    {
        auto it = equipment_map.find(user);
        if (it != equipment_map.end())
        {
            it->second[characterSlot].type[equipmentSlot] = type;
            it->second[characterSlot].typeId[equipmentSlot] = typeId;
        }
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
        call ep6::char_name_available_handler
        add esp,0x8

        popad

        mov al,0x1
        retn
    }
}

void __declspec(naked) naked_0x40AA20()
{
    __asm
    {
        pushad

        movzx edx,dl

        push edx // sendCountry
        push esi // user
        call ep6::send_character_list
        add esp,0x8

        popad

        retn
    }
}

unsigned u0x401798 = 0x401798;
void __declspec(naked) naked_0x401793()
{
    __asm
    {
        pushad

        push esi // user
        call ep6::hook_user_ctor
        add esp,0x4

        popad

        // original
        mov ecx,0xF0
        jmp u0x401798
    }
}

unsigned u0x444CC0 = 0x444CC0;
unsigned u0x4223FE = 0x4223FE;
void __declspec(naked) naked_0x4223F7()
{
    __asm
    {
        pushad

        movzx edx,byte ptr[esp+0x42]
        push edx // typeId
        movzx eax,byte ptr[esp+0x44]
        push eax // type
        movzx edx,byte ptr[esp+0x3E]
        push edx // equipmentSlot
        movzx edx,byte ptr[esp+0x54]
        push edx // characterSlot
        push edi // user
        call ep6::init_equipment
        add esp,0x14

        popad

        // original
        mov ecx,esi
        call u0x444CC0
        jmp u0x4223FE
    }
}

void hook::ep6()
{
    // CUser::PacketUserChar switch
    util::detour((void*)0x4061D3, naked_0x4061D3, 6);
    // CUser::SendCharacterList
    util::detour((void*)0x40AA20, naked_0x40AA20, 6);
    // CUser::CUser
    util::detour((void*)0x401793, naked_0x401793, 5);
    // DBCharacter::LoadCharacterList
    util::detour((void*)0x4223F7, naked_0x4223F7, 7);

    std::uint8_t read_items_param = 17;
    util::write_memory((void*)0x42220B, &read_items_param, 1);
}
