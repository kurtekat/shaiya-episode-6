#pragma unmanaged
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0101.h>
#include <shaiya/packets/0307.h>
#include <shaiya/include/CGameData.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace user_equipment
{
    using namespace System;
    using namespace System::Data;

    constexpr int max_equipment_slot_count = 17;

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
        UINT16 reaction;        //0x17
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

    // to-do: modify ps_dbAgent and ps_game to eliminate this
    void init_equipment(ULONG charId, Equipment0101* equipment)
    {
        try
        {
            auto connection_string = gcnew String("Data Source=localhost;Database=master;Integrated Security=True;");
            SqlClient::SqlConnection connection(connection_string);

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
        character.reaction = dbCharacter->reaction;
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

    void send(CUser* user, EquipmentSlot slot)
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

    void init(CUser* user)
    {
        user->isInitEquipment = true;

        for (int slot = 0; slot < max_equipment_slot_count; ++slot)
        {
            auto& item = user->inventory[0][slot];
            if (!item)
                continue;

            if (slot < EquipmentSlot::Vehicle)
                user->itemQuality[slot] = item->quality;

            CUser::ItemEquipmentAdd(user, item, slot);
        }

        user->isInitEquipment = false;
        CUser::SetAttack(user);
    }

    void send_inspect(CUser* user, CUser* target)
    {
        InspectResponse response{};
        response.opcode = 0x307;
        response.itemCount = 0;

        for (int slot = 0; slot < max_equipment_slot_count; ++slot)
        {
            auto& item = target->inventory[0][slot];
            if (!item)
                continue;

            InspectEquipment inspect_equipment{};
            inspect_equipment.slot = slot;
            inspect_equipment.type = item->type;
            inspect_equipment.typeId = item->typeId;

            if (slot < EquipmentSlot::Vehicle)
                inspect_equipment.quality = item->quality;

            std::memcpy(&inspect_equipment.gems, &item->gems, sizeof(item->gems));
            std::memcpy(inspect_equipment.craftName, &item->craftName, sizeof(CraftName));
            std::memcpy(&response.list[response.itemCount], &inspect_equipment, sizeof(InspectEquipment));
            ++response.itemCount;
        }

        constexpr int packet_size_without_list = 3;
        int packet_size = packet_size_without_list + (response.itemCount * sizeof(InspectEquipment));
        SConnection::Send(user, &response, packet_size);
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
        call user_equipment::send
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
        call user_equipment::send
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
        call user_equipment::send
        add esp,0x8

        popad

        // original
        mov eax,0x703
        jmp u0x468AFF
    }
}

unsigned u0x468A6E = 0x468A6E;
unsigned u0x468AC0 = 0x468AC0;
void __declspec(naked) naked_0x468A66()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x468AC0

        // original
        mov cx,[esi+ebx*2+0x1A6]
        jmp u0x468A6E

        _0x468AC0:
        jmp u0x468AC0
    }
}

unsigned u0x468669 = 0x468669;
unsigned u0x4686BA = 0x4686BA;
void __declspec(naked) naked_0x468661()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x4686BA

        // original
        mov di,[esi+ebx*2+0x1A6]
        jmp u0x468669

        _0x4686BA:
        jmp u0x4686BA
    }
}

unsigned u0x468817 = 0x468817;
unsigned u0x4687CF = 0x4687CF;
void __declspec(naked) naked_0x4687C7()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x468817

        // original
        mov dx,[esi+ebx*2+0x1A6]
        jmp u0x4687CF

        _0x468817:
        jmp u0x468817
    }
}

unsigned u0x46899A = 0x46899A;
void __declspec(naked) naked_0x468992()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x46899A

        // original
        mov [esi+ebx*2+0x1A6],cx

        _0x46899A:
        jmp u0x46899A
    }
}

unsigned u0x46153E = 0x46153E;
void __declspec(naked) naked_0x4614E3()
{
    __asm
    {
        pushad

        push esi
        call user_equipment::init
        add esp,0x4

        popad

        jmp u0x46153E
    }
}

unsigned u0x477E02 = 0x477E02;
void __declspec(naked) naked_0x477D4F()
{
    __asm
    {
        pushad

        push eax // target
        push edi // user
        call user_equipment::send_inspect
        add esp,0x8

        popad

        jmp u0x477E02
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
    util::detour((void*)0x468A66, naked_0x468A66, 8);
    util::detour((void*)0x468661, naked_0x468661, 8);
    util::detour((void*)0x4687C7, naked_0x4687C7, 8);
    util::detour((void*)0x468992, naked_0x468992, 8);
    // CUser::InitEquipment
    util::detour((void*)0x4614E3, naked_0x4614E3, 6);
    // CUser::PacketGetInfo case 0x307
    util::detour((void*)0x477D4F, naked_0x477D4F, 7);

    std::uint8_t max_equipment_slot_count = 17;
    // CUser::InitEquipment (overload)
    util::write_memory((void*)0x4615B3, &max_equipment_slot_count, 1);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x46862D, &max_equipment_slot_count, 1);
    util::write_memory((void*)0x468722, &max_equipment_slot_count, 1);
    util::write_memory((void*)0x468955, &max_equipment_slot_count, 1);
    // CUser::PacketGetInfo case 0x307
    //util::write_memory((void*)0x477DE5, &slot_out_of_range, 1);
    // CUser::ClearEquipment
    util::write_memory((void*)0x46BCCF, &max_equipment_slot_count, 1);
    // CUser::PacketAdminCmdD
    util::write_memory((void*)0x482896, &max_equipment_slot_count, 1);
}
