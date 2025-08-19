using System.Runtime.InteropServices;

namespace MonsterDropEditor.Models
{
    /// <summary>
    /// Represents the MobItemDropInfo structure from Shaiya Episode 6
    /// Size: 8 bytes (0x8)
    /// </summary>
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct MobItemDropInfo
    {
        /// <summary>
        /// Item grade/quality level
        /// </summary>
        public ushort Grade;

        /// <summary>
        /// Padding (2 bytes)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] Padding;

        /// <summary>
        /// Drop rate probability
        /// </summary>
        public uint Rate;

        public MobItemDropInfo(ushort grade, uint rate)
        {
            Grade = grade;
            Rate = rate;
            Padding = new byte[2];
        }

        public override string ToString()
        {
            return $"Grade: {Grade}, Rate: {Rate}";
        }
    }

    /// <summary>
    /// Represents the MobInfo structure from Shaiya Episode 6
    /// Size: 268 bytes (0x10C)
    /// </summary>
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct MobInfo
    {
        public ushort MobId;                    // 0x00
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] MobName;                  // 0x02
        public ushort Level;                    // 0x22
        public ushort Exp;                      // 0x24
        public byte AI;                         // 0x26
        public byte Padding1;                   // 0x27
        public ushort Money;                    // 0x28
        public ushort MoneyAdd;                 // 0x2A
        public byte QuestItemType;              // 0x2C
        public byte QuestItemTypeId;            // 0x2D
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] Padding2;                 // 0x2E
        public uint Health;                     // 0x30
        public ushort Stamina;                  // 0x34
        public ushort Mana;                     // 0x36
        public ushort Dexterity;               // 0x38
        public ushort Wisdom;                  // 0x3A
        public ushort Luck;                    // 0x3C
        public byte Height;                    // 0x3E
        public byte Size;                      // 0x3F
        public byte Attribute;                 // 0x40
        public byte Padding3;                  // 0x41
        public ushort Defense;                 // 0x42
        public ushort Resistance;              // 0x44
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 15)]
        public byte[] ResistStates;            // 0x46 - 0x54
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public byte[] ResistSkills;            // 0x55 - 0x5A
        public byte Padding4;                  // 0x5B
        public uint NormalTime;                // 0x5C
        public byte NormalStep;                // 0x60
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] Padding5;                // 0x61 - 0x63
        public uint ChaseTime;                 // 0x64
        public byte ChaseStep;                 // 0x68
        public byte ChaseRange;                // 0x69
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] Padding6;                // 0x6A - 0x6B
        public uint RespawnTime;               // 0x6C
        public uint DefenseAdd;                // 0x70
        public uint RecoverValue;              // 0x74
        public int Country;                    // 0x78 (MobTeam enum)
        public bool IsObelisk;                 // 0x7C
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] Padding7;                // 0x7D - 0x7F
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 60)]
        public byte[] Attacks;                 // 0x80 - 0xBB (MobAttackInfo array)
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public MobItemDropInfo[] DropInfo;     // 0xBC - 0x10B (10 drop slots)

        public string GetMobName()
        {
            if (MobName == null) return string.Empty;
            
            // Find null terminator
            int nullIndex = Array.IndexOf(MobName, (byte)0);
            if (nullIndex < 0) nullIndex = MobName.Length;
            
            return System.Text.Encoding.UTF8.GetString(MobName, 0, nullIndex);
        }
    }

    /// <summary>
    /// Represents a mob entry with its memory address and information
    /// </summary>
    public class MobEntry
    {
        public IntPtr Address { get; set; }
        public MobInfo Info { get; set; }
        public bool IsModified { get; set; }
        public MobItemDropInfo[] OriginalDropInfo { get; set; }

        public MobEntry(IntPtr address, MobInfo info)
        {
            Address = address;
            Info = info;
            IsModified = false;
            OriginalDropInfo = new MobItemDropInfo[10];
            if (info.DropInfo != null)
            {
                Array.Copy(info.DropInfo, OriginalDropInfo, Math.Min(10, info.DropInfo.Length));
            }
        }

        public string DisplayName => $"[{Info.MobId}] {Info.GetMobName()} (Lv.{Info.Level})";
    }

    /// <summary>
    /// Enum for mob teams
    /// </summary>
    public enum MobTeam : int
    {
        Light = 0,
        Fury = 1,
        Neutral = 2
    }
}