using System;
using System.Collections.Generic;
using System.IO;

namespace Converter
{
    class Program
    {
        static int PromptForSystem(string systemType)
        {
            ConsoleKey key;

            do
            {
                var promptText = $"\nChoose {systemType} numeral system: for binary press B, for octal press O, for decimal press D, for hexadecimal press H.";
                Console.WriteLine(promptText);
                key = Console.ReadKey().Key;

                if (key == ConsoleKey.B ||
                    key == ConsoleKey.O ||
                    key == ConsoleKey.D ||
                    key == ConsoleKey.H)
                    break;

                Console.Error.WriteLine("\nError. Invalid input");
            }
            while (key != ConsoleKey.B || key != ConsoleKey.O || key != ConsoleKey.D || key != ConsoleKey.H);

            int numeralSystem = (key) switch
            {
                (ConsoleKey.B) => 2,
                (ConsoleKey.O) => 8,
                (ConsoleKey.D) => 10,
                (ConsoleKey.H) => 16,
            };

            return numeralSystem;
        }

        static ConsoleKey PromptForInputMethod()
        {
            string promptText = "\nTo read input from console press C. To read from file press F.";
            Console.WriteLine(promptText);
            var inputMethod = Console.ReadKey().Key;

            if (inputMethod != ConsoleKey.C && inputMethod != ConsoleKey.F)
            {
                Console.Error.WriteLine("\nError. Invalid input");
                PromptForInputMethod();
            }

            return inputMethod;
        }
        static string PromptForFilePath(string action)
        {
            string filePath;

            do
            {
                Console.WriteLine($"\nEnter path to the file to {action}");
                filePath = Console.ReadLine();

                if (File.Exists(filePath))
                    break;

                Console.Error.WriteLine("\nError. Invalid file path");
            }
            while (!File.Exists(filePath));

            return filePath;
        }

        static string[] GetNumbers()
        {
            string input = Console.ReadLine();

            return Array.ConvertAll(input.Split(','), p => p.Trim());
        }

        static void ReadWriteFileContents(string readPath, string writePath, int currentSystem, int desiredSystem)
        {
            try
            {
                using (var writer = new StreamWriter(writePath))
                {
                    using (var reader = new StreamReader(readPath))
                    {
                        // Redirect output from the console to the file.
                        Console.SetOut(writer);

                        // Redirect input from the console to the file.
                        Console.SetIn(reader);

                        string[] userInput = GetNumbers();

                        string result = TranslateData(currentSystem, desiredSystem, userInput);
                        Console.WriteLine(result);
                    }
                }
            }
            catch (Exception ex)
            {
                // Redirect standard output stream back to console
                var stOut = new StreamWriter(Console.OpenStandardOutput());
                stOut.AutoFlush = true;
                Console.SetOut(stOut);

                Console.Error.WriteLine($"Error: {ex.Message}");
            }
        }

        static string TranslateData(int currentSystem, int desiredSystem, string[] userInput)
        {
            try
            {
                string baseChars = "0123456789ABCDEF";
                List<string> numsList = new List<string>();

                for (int n = 0; n < userInput.Length; n++)
                {
                    string num = userInput[n];

                    bool isNegative = false;
                    var number = num;

                    if (num.StartsWith("-")) {
                        isNegative = true;
                        number = num.TrimStart('-');
                    }

                    // Convert number into decimal.
                    int dec = 0;
                    for (int i = number.Length - 1, digit = 1; i >= 0; i--, digit *= currentSystem)
                    {
                        dec += baseChars.IndexOf(number[i]) * digit;
                    }

                    // Convert decimal into desired system.
                    var result = "";
                    do
                    {
                        result = baseChars[dec % desiredSystem] + result;
                        dec = dec / desiredSystem;
                    }
                    while (dec > 0);

                    if (isNegative)
                    {
                        result = $"-{result}";
                    }

                    numsList.Add(result);
                }

                return string.Join(", ", numsList);
            }
            catch
            {
                return $"Error while conversion: invalid chracter(s)";
            }
        }

        static void Main()
        {
            var console = ConsoleKey.C;

            int currentSystem = PromptForSystem("current");
            int desiredSystem = PromptForSystem("desired");
            var inputMethod = PromptForInputMethod();

            if (inputMethod == console)
            {
                Console.WriteLine("\nEnter comma separated numbers(s) to convert:");
                string[] userInput = GetNumbers();

                if (currentSystem == desiredSystem)
                {
                    Console.WriteLine($"Result: {string.Join(", ", userInput)}");
                    return;
                }

                string result = TranslateData(currentSystem, desiredSystem, userInput);
                Console.WriteLine($"Result: {string.Join(", ", result)}");
            }
            else
            {
                string readPath = PromptForFilePath("read");
                string writePath = PromptForFilePath("write");

                ReadWriteFileContents(readPath, writePath, currentSystem, desiredSystem);

                var stOut = new StreamWriter(Console.OpenStandardOutput());
                stOut.AutoFlush = true;
                Console.SetOut(stOut);
            }
        }
    }
}
