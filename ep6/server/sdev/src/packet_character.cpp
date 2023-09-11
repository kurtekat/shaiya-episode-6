#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0101.h>
#include <shaiya/packets/0119.h>
#include <shaiya/packets/0403.h>
#include <shaiya/packets/0711.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
#include <shaiya/include/SConnectionTServerReconnect.h>
using namespace shaiya;

namespace packet_character
{
    // custom packets

    #pragma pack(push, 1)
    struct DBCharNameAvailableRequest
    {
        UINT16 opcode; // 0x40D
        UserId userId;
        char charName[19];
    };

    struct DBCharNameAvailableResponse
    {
        UINT16 opcode; // 0x40D
        UserId userId;
        bool available;
    };
    #pragma pack(pop)

    void name_available_handler(CUser* user, const char* name)
    {
        int packet_size_without_name = 6;

        DBCharNameAvailableRequest request{};
        request.opcode = 0x40D;
        request.userId = user->userId;
        strncpy_s(request.charName, name, sizeof(request.charName));

        int packet_size = packet_size_without_name + std::strlen(request.charName) + 1;
        SConnectionTServerReconnect::Send(&request, packet_size);
    }

    void send_name_available(CUser* user, Packet packet)
    {
        auto available = util::read_bytes<bool>(packet, 6);
        CharNameAvailableResponse response{ 0x119, available };
        SConnection::Send(user, &response, sizeof(CharNameAvailableResponse));
    }

    void send_warehouse(CUser* user)
    {
        constexpr int max_warehouse_item_count = 240;
        // the packet length within the loop
        // 
        // ep5: 1657 = 7 + (33 * 50)
        // ep6: 2057 = 7 + (41 * 50)
        //
        // 2057 bytes will crash ps_game (max is 2048)
        // shen1l changed 50 to 40
        constexpr int max_item_send_count = 40;
        constexpr int packet_size_without_list = 7;

        WarhouseItemList warehouse{};
        warehouse.opcode = 0x711;
        warehouse.money = user->bankMoney;
        warehouse.itemCount = 0;

        for (int slot = 0; slot < max_warehouse_item_count; ++slot)
        {
            if (!user->warehouse[slot])
                continue;

            WarehouseItem warehouse_item{};

            warehouse_item.slot = slot;
            warehouse_item.type = user->warehouse[slot]->type;
            warehouse_item.typeId = user->warehouse[slot]->typeId;
            warehouse_item.quality = user->warehouse[slot]->quality;
            std::memcpy(&warehouse_item.gems, &user->warehouse[slot]->gems, sizeof(warehouse_item.gems));
            warehouse_item.count = user->warehouse[slot]->count;

            // to-do: implement dates
            warehouse_item.fromDate = 0;
            warehouse_item.toDate = 0;

            std::memcpy(warehouse_item.craftName, &user->warehouse[slot]->craftName, sizeof(CraftName));
            std::memcpy(&warehouse.list[warehouse.itemCount], &warehouse_item, sizeof(WarehouseItem));
            ++warehouse.itemCount;

            if (warehouse.itemCount != max_item_send_count)
                continue;
            else
            {
                int packet_size = packet_size_without_list + (warehouse.itemCount * sizeof(WarehouseItem));
                SConnection::Send(user, &warehouse, packet_size);

                std::memset(&warehouse.list, 0, sizeof(warehouse.list));
                warehouse.itemCount = 0;
            }
        }

        if (warehouse.itemCount <= 0)
            return;

        int packet_size = packet_size_without_list + (warehouse.itemCount * sizeof(WarehouseItem));
        SConnection::Send(user, &warehouse, packet_size);
    }

    void send_character(CUser* user, Character0403* dbCharacter)
    {
        CharacterList character{};
        character.opcode = 0x101;
        character.slot = dbCharacter->slot;
        character.charId = dbCharacter->id;
        character.regDate = dbCharacter->regDate;
        character.level = dbCharacter->level;
        character.family = dbCharacter->family;
        character.grow = dbCharacter->grow;
        character.hair = dbCharacter->hair;
        character.face = dbCharacter->face;
        character.size = dbCharacter->size;
        character.job = dbCharacter->job;
        character.sex = dbCharacter->sex;
        character.mapId = dbCharacter->mapId;
        character.strength = dbCharacter->strength;
        character.dexterity = dbCharacter->dexterity;
        character.reaction = dbCharacter->reaction;
        character.intelligence = dbCharacter->intelligence;
        character.wisdom = dbCharacter->wisdom;
        character.luck = dbCharacter->luck;
        character.health = dbCharacter->health;
        character.mana = dbCharacter->mana;
        character.stamina = dbCharacter->stamina;
        std::memcpy(&character.equipment, &dbCharacter->equipment, sizeof(Equipment0403));
        strncpy_s(character.charName, dbCharacter->charName, sizeof(character.charName));
        character.deleted = dbCharacter->deleted;
        character.nameChange = dbCharacter->nameChange;
        memcpy(&character.cloakBadge, &dbCharacter->cloakBadge, sizeof(character.cloakBadge));
        SConnection::Send(user, &character, sizeof(character));
    }
}

unsigned u0x47A237 = 0x47A237;
unsigned u0x47A574 = 0x47A574;
void __declspec(naked) naked_0x47A231()
{
    __asm
    {
        // original
        add eax,-0x102
        push ebx

        cmp eax,0x17
        je case_0x119
        jmp u0x47A237

        case_0x119:
        pushad

        lea eax,[edi+0x2]
        push eax // name
        push esi // user
        call packet_character::name_available_handler
        add esp,0x8

        popad

        jmp u0x47A574
    }
}

void __declspec(naked) naked_0x492660()
{
    __asm
    {
        pushad

        push ebp // user
        call packet_character::send_warehouse
        add esp,0x4

        popad
        
        retn 0x4
    }
}

unsigned u0x47B9B8 = 0x47B9B8;
void __declspec(naked) naked_0x47B8FB()
{
    __asm
    {
        pushad
        
        push esi // packet
        push ebp // user
        call packet_character::send_character
        add esp,0x8

        popad

        jmp u0x47B9B8
    }
}

unsigned u0x47B3EC = 0x47B3EC;
unsigned u0x47BDCC = 0x47BDCC;
void __declspec(naked) naked_0x47B3E7()
{
    __asm
    {
        // original
        add eax,-0x401
        cmp eax,0xC
        je case_0x40D
        jmp u0x47B3EC

        case_0x40D:
        pushad

        push edi // packet
        push ebp // user
        call packet_character::send_name_available
        add esp,0x8

        popad

        mov al,0x1
        jmp u0x47BDCC
    }
}

void hook::packet_character()
{
    // CUser::PacketCharacter switch
    util::detour((void*)0x47A231, naked_0x47A231, 6);
    // CUser::SendCharacterBank
    util::detour((void*)0x492660, naked_0x492660, 6);
    // CUser::PacketUserDBChar case 0x403
    util::detour((void*)0x47B8FB, naked_0x47B8FB, 6);
    // CUser::PacketUserDBChar
    util::detour((void*)0x47B3E7, naked_0x47B3E7, 5);

    std::uint8_t character_data_size = 104;
    // CUser::PacketUserDBChar
    util::write_memory((void*)0x47B4EC, &character_data_size, 1);
    util::write_memory((void*)0x47B9C9, &character_data_size, 1);
}
