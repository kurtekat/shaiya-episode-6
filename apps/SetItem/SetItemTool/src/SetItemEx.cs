using System.Collections.Generic;
using System.Linq;
using Parsec.Extensions;
using Parsec.Serialization;
using Parsec.Shaiya.SData;

namespace SetItemTool
{
    internal class SetItemEx : SData
    {
        public List<Record> Records { get; set; }

        protected override void Read(SBinaryReader binaryReader)
        {
            Records = binaryReader.ReadList<Record>().ToList();
        }

        protected override void Write(SBinaryWriter binaryWriter)
        {
            binaryWriter.Write(Records.ToSerializable());
        }
    }
}
