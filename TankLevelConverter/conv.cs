using System;
using System.IO;
using System.Threading;

public partial class Program
{
    public static void Main(string[] args)
    {
        string outputFilePath = "tank_level_percentage.txt";

        while (true)
        {
            Console.WriteLine("Enter the resistance value in ohms (0 to 100, or type 'exit' to quit):"); // Example input to test funtion WILL replace with sensor input
            string input = Console.ReadLine();

            if (input.ToLower() == "exit")
            {
                break; // Exit the loop if the user types 'exit'
            }

            if (double.TryParse(input, out double resistance))
            {
                double percentage = ConvertResistanceToPercentage(resistance);
                // Output only the percentage value to a file
                File.WriteAllText(outputFilePath, percentage.ToString());
                Console.WriteLine($"Percentage written to {outputFilePath}: {percentage}");
            }
            else
            {
                Console.WriteLine("Invalid input. Please enter a numeric value.");
            }

            // Optional: Wait for a moment before the next input
            Thread.Sleep(1000);
        }
    }

    public static double ConvertResistanceToPercentage(double resistance)
    {
        // Resistance range
        const double R_100 = 100; // 100 ohms = 0% tank level
        const double R_0 = 0;     // 0 ohms = 100% tank level

        if (resistance < R_0)
        {
            return 100; // If resistance is less than 0 ohms, return 100%
        }
        else if (resistance > R_100)
        {
            return 0; // If resistance is greater than 100 ohms, return 0%
        }
        else
        {
            // Linear interpolation
            return 100 - (resistance / R_100) * 100;
        }
    }
}
