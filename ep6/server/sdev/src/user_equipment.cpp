#pragma unmanaged
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0101.h>
#include <shaiya/include/CGameData.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace user_equipment
{
    using namespace System;
    using namespace System::Data;

    constexpr int slot_out_of_range = 17;

    #pragma pack(push, 1)
    struct Equipment
    {
        UINT8 type[8];
        UINT8 typeId[8];
    };

    // the data read from the ps_dbAgent 0x403 payload
    // see CUser::SendCharacterList (0x40AA20)
    struct DBCharacter
    {
        ULONG charId;           //0x00
        ULONG regDate;          //0x04
        bool deleted;           //0x08
        UINT8 slot;             //0x09
        Family family;          //0x0A
        Grow grow;              //0x0B
        UINT8 hair;             //0x0C
        UINT8 face;             //0x0D
        UINT8 size;             //0x0E
        Job job;                //0x0F
        Sex sex;                //0x10
        UINT16 level;           //0x11
        UINT16 strength;        //0x13
        UINT16 dexterity;       //0x15
        UINT16 recovery;        //0x17
        UINT16 intelligence;    //0x19
        UINT16 wisdom;          //0x1B
        UINT16 luck;            //0x1D
        UINT16 health;          //0x1F
        UINT16 mana;            //0x21
        UINT16 stamina;         //0x23
        UINT16 mapId;           //0x25
        bool nameChange;        //0x27
        PAD(3);
        Equipment equipment;    //0x2B
        CloakBadge cloakBadge;  //0x3B
        char charName[19];      //0x41
        char nullByte;          //0x55
        // 0x56
    };
    #pragma pack(pop)

    #pragma managed

    void init_equipment(ULONG charId, Equipment0101* equipment)
    {
        try
        {
            auto connectionString = gcnew String("Data Source=localhost;Database=master;Integrated Security=True;");
            SqlClient::SqlConnection connection(connectionString);

            auto text = String::Format(
                "SELECT Slot, [Type], [TypeID] FROM [PS_GameData].[dbo].[CharItems] WHERE Bag=0 AND CharID={0} ORDER BY Slot ASC;",
                charId
            );

            SqlClient::SqlCommand command(text, %connection);
            connection.Open();

            auto reader = command.ExecuteReader();
            while (reader->Read())
            {
                auto slot = reader->GetByte(0);
                equipment->type[slot] = reader->GetByte(1);
                equipment->typeId[slot] = reader->GetByte(2);
            }

            reader->Close();
            connection.Close();
        }
        catch (Exception^ ex)
        {
            util::log(ex->ToString());
        }
    }

    #pragma unmanaged

    void send_character(CUser* user, DBCharacter* dbCharacter)
    {
        CharacterList character{};
        character.opcode = 0x101;
        character.slot = dbCharacter->slot;
        character.charId = dbCharacter->charId;
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
        character.recovery = dbCharacter->recovery;
        character.intelligence = dbCharacter->intelligence;
        character.wisdom = dbCharacter->wisdom;
        character.luck = dbCharacter->luck;
        character.health = dbCharacter->health;
        character.mana = dbCharacter->mana;
        character.stamina = dbCharacter->stamina;
        init_equipment(dbCharacter->charId, &character.equipment);
        strncpy_s(character.charName, dbCharacter->charName, sizeof(character.charName));
        character.deleted = dbCharacter->deleted;
        character.nameChange = dbCharacter->nameChange;
        memcpy(&character.cloakBadge, &dbCharacter->cloakBadge, sizeof(character.cloakBadge));
        SConnection::Send(user, &character, sizeof(character));
    }

    bool enable_slot(CGameData::ItemInfo* info, EquipmentSlot slot)
    {
        switch (static_cast<ItemType>(info->type))
        {
        case ItemType::Pet:
            return slot == EquipmentSlot::Pet;
        case ItemType::Wings:
            return slot == EquipmentSlot::Wings;
        case ItemType::Costume:
            return slot == EquipmentSlot::Costume;
        default:
            return true;
        }
    }

    void send_view(CUser* user, EquipmentSlot slot)
    {
        switch (slot)
        {
        case EquipmentSlot::Pet:
        case EquipmentSlot::Costume:
        case EquipmentSlot::Wings:
            CUser::SendEquipment(user, slot);
            break;
        default:
            break;
        }
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
        call user_equipment::send_character
        add esp,0x8

        popad

        jmp u0x47B9B8
    }
}

unsigned u0x468474 = 0x468474;
void __declspec(naked) naked_0x46846F()
{
    __asm
    {
        pushad

        push eax
        push esi
        call user_equipment::enable_slot
        add esp,0x8
        test al,al

        popad

        je wrong_slot
        // original
        mov eax,0x1
        jmp u0x468474

        wrong_slot:
        xor al,al
        pop esi
        retn
    }
}

unsigned u0x4686C9 = 0x4686C9;
void __declspec(naked) naked_0x4686C4()
{
    __asm
    {
        pushad
            
        push ebx
        push esi
        call user_equipment::send_view
        add esp,0x8

        popad

        // original
        mov ecx,0x703
        jmp u0x4686C9
    }
}

unsigned u0x4689D4 = 0x4689D4;
void __declspec(naked) naked_0x4689CF()
{
    __asm
    {
        pushad
            
        push ebx
        push esi
        call user_equipment::send_view
        add esp,0x8

        popad

        // original
        mov edx,0x703
        jmp u0x4689D4
    }
}

unsigned u0x468AFF = 0x468AFF;
void __declspec(naked) naked_0x468AFA()
{
    __asm
    {
        pushad
            
        push ebx
        push esi
        call user_equipment::send_view
        add esp,0x8

        popad

        // original
        mov eax,0x703
        jmp u0x468AFF
    }
}

void hook::user_equipment()
{
    // CUser::PacketUserDBChar case 0x403
    util::detour((void*)0x47B8FB, naked_0x47B8FB, 6);
    // CUser::EnableEquipment default case (slot)
    util::detour((void*)0x46846F, naked_0x46846F, 5);
    // CUser::ItemBagToBag
    util::detour((void*)0x4686C4, naked_0x4686C4, 5);
    util::detour((void*)0x4689CF, naked_0x4689CF, 5);
    util::detour((void*)0x468AFA, naked_0x468AFA, 5);

    std::uint8_t slot_out_of_range = 17;
    // CUser::InitEquipment
    util::write_memory((void*)0x461528, &slot_out_of_range, 1);
    // CUser::InitEquipment (overload)
    util::write_memory((void*)0x4615B3, &slot_out_of_range, 1);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x46862D, &slot_out_of_range, 1);
    util::write_memory((void*)0x468722, &slot_out_of_range, 1);
    util::write_memory((void*)0x468955, &slot_out_of_range, 1);
    // CUser::ClearEquipment
    util::write_memory((void*)0x46BCCF, &slot_out_of_range, 1);
    // CUser::PacketAdminCmdD
    util::write_memory((void*)0x482896, &slot_out_of_range, 1);
    // CUser::SendDBAgentCharGetInfo
    util::write_memory((void*)0x47AEAA, &slot_out_of_range, 1);
}
