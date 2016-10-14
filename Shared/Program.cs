using System;

namespace Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
#if NET45
                const string runtime = "v2.0.50727";
                const string Path = @"net35extension.dll";
#elif NET35
                const string runtime = "v4.0.30319";
                const string Path = @"net45extension.dll";
#endif
                const string TypeName = "Demo.Extension";
                const string Method = "Run";

                Console.WriteLine($"Host Runtime: {Environment.Version}");

                using (var host = new DotNetHost(runtime))
                {
                    var result = host.Run(Path, TypeName, Method);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine($"Failure: {e.Message}");
            }
        }
    }
}
