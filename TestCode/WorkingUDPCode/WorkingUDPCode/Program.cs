using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class UdpSrvrSendAndReceiveData
{
    public static void Main()
    {
        int ch;

        Console.WriteLine("Enter 1 for Send Data, and 2 for receive it: ");
        ch = Console.Read();


        if (ch == '1')
            SendData();
        else
            ReceiveData();
    }

    private static void ReceiveData()
    {
        byte[] data = new byte[1024];
        IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 8051);
        UdpClient newsock = new UdpClient(ipep);


        Console.WriteLine("Waiting for a client...");

        IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);

        byte[] data5 = newsock.Receive(ref sender);
        string test5 = Encoding.ASCII.GetString(data5);
        Console.WriteLine("test5 = {0}", test5);

        newsock.Close();
    }

    private static void SendData()
    {
        byte[] data = new byte[1024];

        UdpClient server = new UdpClient("192.168.1.63", 8051);  // unity box
        IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);

        int test1 = 45;
        double test2 = 3.14159;
        int test3 = -1234567890;
        bool test4 = false;
        string test5 = "This is a test.";

        byte[] data1 = BitConverter.GetBytes(test1);
        server.Send(data1, data1.Length);

        byte[] data2 = BitConverter.GetBytes(test2);
        server.Send(data2, data2.Length);

        byte[] data3 = BitConverter.GetBytes(test3);
        server.Send(data3, data3.Length);

        byte[] data4 = BitConverter.GetBytes(test4);
        server.Send(data4, data4.Length);

        byte[] data5 = Encoding.ASCII.GetBytes(test5);
        server.Send(data5, data5.Length);

        server.Close();
    }
}