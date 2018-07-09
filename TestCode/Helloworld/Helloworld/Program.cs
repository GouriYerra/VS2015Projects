using System;

namespace Helloworld
{
    class Hello
    {
        static void Main()
        {
            Console.WriteLine("Hello world!");

            //Keep console windown open in debug mode
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}