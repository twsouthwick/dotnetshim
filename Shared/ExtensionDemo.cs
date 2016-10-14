using System;

namespace Demo
{
    public class Extension
    {
        public static int Run(string arg)
        {
            Console.WriteLine($"Extension Runtime: {Environment.Version}");

            return 5;
        }
    }
}
