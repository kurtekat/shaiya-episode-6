using Newtonsoft.Json;
using Parsec.Serialization;
using Parsec.Shaiya.Core;

namespace SetItemTool
{
    internal class Synergy : ISerializable
    {
        private readonly int _abilityCount = 12;

        [JsonIgnore]
        public string Text { get; set; } = string.Empty;
        public int Strength { get; set; }
        public int Dexterity { get; set; }
        public int Intelligence { get; set; }
        public int Wisdom { get; set; }
        public int Reaction { get; set; }
        public int Luck { get; set; }
        public int Health { get; set; }
        public int Mana { get; set; }
        public int Stamina { get; set; }
        public int AttackPower { get; set; }
        public int RangedAttackPower { get; set; }
        public int MagicPower { get; set; }

        public void Read(SBinaryReader binaryReader)
        {
            Text = binaryReader.ReadString();
            if (string.IsNullOrEmpty(Text))
                return;

            var text = Text.Split(',');
            if (text.Length != _abilityCount)
                return;

            Strength = int.Parse(text[0]);
            Dexterity = int.Parse(text[1]);
            Intelligence = int.Parse(text[2]);
            Wisdom = int.Parse(text[3]);
            Reaction = int.Parse(text[4]);
            Luck = int.Parse(text[5]);
            Health = int.Parse(text[6]);
            Mana = int.Parse(text[7]);
            Stamina = int.Parse(text[8]);
            AttackPower = int.Parse(text[9]);
            RangedAttackPower = int.Parse(text[10]);
            MagicPower = int.Parse(text[11]);
        }

        public void Write(SBinaryWriter binaryWriter)
        {
            var text = string.Format(
            "{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11}",
            Strength,
            Dexterity,
            Intelligence,
            Wisdom,
            Reaction,
            Luck,
            Health,
            Mana,
            Stamina,
            AttackPower,
            RangedAttackPower,
            MagicPower
            );

            binaryWriter.Write(text);
        }
    }
}
