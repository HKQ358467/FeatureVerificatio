using System.Net;
using System.Net.Sockets;
using System.Text;

namespace TCPServerVerificatio
{
    public class NetServer
    {  
        private Socket socWatch = null;
        private bool isBind = false;
        private Thread thrWatch = null;
        private Dictionary<string, OneServer> dicSockets = new Dictionary<string, OneServer>();
        string deviceIP = "192.168.0.10";
        int devicePort = 8080;
        bool isStart = false;

        static StreamWriter file = null;
        static string filePath = "";
        bool IsSave = false;
        public NetServer()
        {
           
        }
        ~NetServer()
        {
            StopWatch();
        }

        internal void StartWatch()
        {
            string basepath = AppContext.BaseDirectory;           
            IPAddress ip = IPAddress.Parse(deviceIP);
            StartWatch(ip, devicePort);
        }

        internal bool StartWatch(IPAddress ip, int port)
        {
            try
            {
                IPEndPoint iep = new IPEndPoint(ip, port);
                socWatch = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socWatch.Bind(iep);
                socWatch.Listen(10);
                isBind = true;
                thrWatch = new Thread(WatchConnecting);
                thrWatch.IsBackground = true;
                thrWatch.Start();
                return true;
            }
            catch (Exception ex)
            {
                StopWatch();
                return false;
            }
        }

        public void StopWatch()
        {
            try
            {
                isBind = false;
                if (socWatch != null)
                {
                    socWatch.Close();
                    socWatch = null;
                }
                if (dicSockets.Count > 0)
                {
                    Dispose();
                }
            
                if (thrWatch != null)
                {
                    thrWatch.Join();
                    thrWatch = null;
                }
                Dispose();
            }
            catch (Exception ex)
            {
            }
        }

        private void PrintInfo(string obj)
        {
            Console.WriteLine(obj);
        }

        private void SaveData(string obj)
        {
            if (IsSave && file != null)
            {
                file.WriteLine(obj);
                file.Flush();
            }
        }

        private void Dispose()
        {
            try
            {
                foreach (OneServer oneServer in dicSockets.Values)
                {
                    oneServer.Dispose();
                }
                dicSockets.Clear();
            }
            catch (Exception ex)
            {
            }
        }

        private void WatchConnecting()
        {
            while (isBind)
            {
                try
                {
                    if (socWatch == null) return;
                    Socket socket = socWatch.Accept();
                    //只保留一个连接
                    if (dicSockets.Count > 0)
                    {
                        Dispose();
                    }
                    OneServer oneServer = new OneServer(socket);
                    oneServer.CmdEvent += ParseCmd;
                    dicSockets.Add(socket.RemoteEndPoint.ToString(), oneServer);
                    string printResul = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff:");
                    printResul += "收到连接：" + socket.RemoteEndPoint.ToString();
                    PrintInfo(printResul);
                }
                catch (Exception ex)
                {
                    StopWatch();
                }
            }
        }

        private void ParseCmd(byte[] obj)
        {
            try
            {
                string strCmd = Encoding.ASCII.GetString(obj);
                Console.WriteLine(strCmd);
                SendData(obj);
            }
            catch (Exception ex)
            {
            }
        }

        public void SendData(byte[] data)
        {
            try
            {
                //实际只有一个客户端
                foreach (OneServer oneServer in dicSockets.Values)
                {
                    if (oneServer.socket != null && oneServer.socket.Connected &&
                        !oneServer.socket.Poll(500, SelectMode.SelectRead))
                    {
                        oneServer.socket.Send(data);
                    }
                }
            }
            catch (Exception ex)
            {
            }
        }
    }
}
