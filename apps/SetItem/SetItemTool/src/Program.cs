using System;
using System.IO;
using System.Text;
using Parsec;
using Parsec.Common;
using Parsec.Shaiya.SetItem;

namespace SetItemTool
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
                Console.WriteLine();
                Console.WriteLine("Please choose a format");
                Console.WriteLine("1. Client");
                Console.WriteLine("2. Server");
                option = Console.ReadKey().KeyChar;

                if (option == '1')
                {
                    var data = ParsecReader.FromFile<SetItem>("SetItem.SData", Episode.EP6, encoding);
                    data.WriteJson("SetItem.json");
                }
                else
                {
                    var data = ParsecReader.FromFile<SetItemEx>("SetItem.SData", Episode.EP6, encoding);
                    data.WriteJson("SetItem.json");
                }
            }
            else
            {
                Console.WriteLine();
                Console.WriteLine("Please choose a format");
                Console.WriteLine("1. Client");
                Console.WriteLine("2. Server");
                option = Console.ReadKey().KeyChar;

                if (option == '1')
                {
                    Directory.CreateDirectory("output/client");
                    var data = ParsecReader.FromJsonFile<SetItem>("SetItem.json", encoding);
                    data.WriteEncrypted("output/client/SetItem.SData");
                }
                else
                {
                    Directory.CreateDirectory("output/server");
                    var data = ParsecReader.FromJsonFile<SetItemEx>("SetItem.json", encoding);
                    data.WriteDecrypted("output/server/SetItem.SData");
                }
            }
        }
    }
}
