using System;
using System.IO;
using System.Text;
using Parsec;
using Parsec.Common;
using Parsec.Shaiya.NpcQuest;

namespace NpcQuestTool
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Please choose an option");
            Console.WriteLine("1. Extract");
            Console.WriteLine("2. Compile");
            var option = Console.ReadKey().KeyChar;

            Console.WriteLine();
            Console.WriteLine("Please enter a code page identifier (e.g. 1252)");
            var codepage = Console.ReadLine();
            var encoding = CodePagesEncodingProvider.Instance.GetEncoding(int.Parse(codepage));

            if (encoding == null)
            {
                Console.WriteLine("Invalid encoding");
                return;
            }

            if (option == '1')
            {
                var data = ParsecReader.FromFile<NpcQuest>("NpcQuest.SData", Episode.EP6, encoding);
                data.WriteJson("NpcQuest.json");
            }
            else
            {
                Console.WriteLine();
                Console.WriteLine("Please choose an option");
                Console.WriteLine("1. Client");
                Console.WriteLine("2. Server");
                option = Console.ReadKey().KeyChar;

                if (option == '1')
                {
                    Directory.CreateDirectory("output/client");
                    var data = ParsecReader.FromJsonFile<NpcQuest>("NpcQuest.json", encoding);
                    data.WriteEncrypted("output/client/NpcQuest.SData");
                }
                else
                {
                    Directory.CreateDirectory("output/server");
                    var data = ParsecReader.FromJsonFile<NpcQuest>("NpcQuest.json", encoding);
                    data.WriteDecrypted("output/server/NpcQuest.SData");
                }
            }
        }
    }
}
