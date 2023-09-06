#pragma unmanaged
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0119.h>
#include <shaiya/packets/0711.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace packet_character
{
    using namespace System;
    using namespace System::Data;

    #pragma managed

    bool is_name_available(const char* name)
    {
        try
        {
            auto char_name = gcnew String(name);
            if (String::IsNullOrEmpty(char_name))
                return false;

            // respect client input restrictions
            if (char_name->Length < 3 || char_name->Length > 13 || char_name->Contains("'"))
                return false;

            auto connection_string = gcnew String("Data Source=localhost;Database=master;Integrated Security=True;");
            SqlClient::SqlConnection connection(connection_string);

            auto command_text = gcnew String(
                "SELECT ISNULL(COUNT(*),0) FROM [PS_GameData].[dbo].[Chars] WHERE CharName=@name AND Del=0;"
            );

            SqlClient::SqlCommand command(command_text, %connection);
            command.Parameters->Add("@name", SqlDbType::VarChar)->Value = char_name;
            connection.Open();

            int name_count = Convert::ToInt32(command.ExecuteScalar());
            connection.Close();
            return name_count ? false : true;
        }
        catch (Exception^ ex)
        {
            util::log(ex->ToString());
            return false;
        }
    }

    #pragma unmanaged

    void char_name_available_handler(CUser* user, const char* name)
    {
        CharNameAvailableResponse response{ 0x119, is_name_available(name) };
        SConnection::Send(user, &response, sizeof(response));
    }

    void send_warehouse(CUser* user)
    {
        constexpr int max_warehouse_item_count = 240;
        // the packet length within the loop
        // 
        // ep5: 1657 = 7 + (33 * 50)
        // ep6: 2057 = 7 + (41 * 50)
        //
        // 2057 bytes will crash ps_game
        // shen1l changed 50 to 40
        constexpr int max_item_send_count = 40;

        CharacterWarehouse warehouse{};
        warehouse.opcode = 0x711;
        warehouse.money = user->bankMoney;
        warehouse.itemCount = 0;

        constexpr int size_without_items = 7;

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
            std::memcpy(&warehouse.items[warehouse.itemCount], &warehouse_item, sizeof(WarehouseItem));
            ++warehouse.itemCount;

            if (warehouse.itemCount != max_item_send_count)
                continue;
            else
            {
                int packet_size = size_without_items + (warehouse.itemCount * sizeof(WarehouseItem));
                SConnection::Send(user, &warehouse, packet_size);

                std::memset(&warehouse.items, 0, sizeof(warehouse.items));
                warehouse.itemCount = 0;
            }
        }

        if (warehouse.itemCount <= 0)
            return;

        int packet_size = size_without_items + (warehouse.itemCount * sizeof(WarehouseItem));
        SConnection::Send(user, &warehouse, packet_size);
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
        call packet_character::char_name_available_handler
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

void hook::packet_character()
{
    // CUser::PacketCharacter switch
    util::detour((void*)0x47A231, naked_0x47A231, 6);
    // CUser::SendCharacterBank
    util::detour((void*)0x492660, naked_0x492660, 6);
}
