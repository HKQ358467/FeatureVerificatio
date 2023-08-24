namespace TCPServerVerificatio
{
    internal class Program
    {
        static void Main(string[] args)
        {
            NetServer netServer = new NetServer();
            netServer.StartWatch();

            bool ToBeContinue = true;
            while (ToBeContinue)
            {
                ConsoleKeyInfo keyInfo;
                if (System.Console.KeyAvailable)
                {
                    keyInfo = System.Console.ReadKey(true);
                    if (keyInfo.KeyChar == (char)027)//如果按了Esc键，Esc键的ASCII码为十进制27
                        ToBeContinue = false;
                }
                else//没有按Esc键，时间一秒一秒走动
                {
                    Thread.Sleep(1000);//延迟1秒
                }
            }
            netServer.StopWatch();
        }
    }
}