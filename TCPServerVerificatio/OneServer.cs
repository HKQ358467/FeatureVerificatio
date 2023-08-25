using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TCPServerVerificatio
{
    public class OneServer
    {
        public Socket socket;
        public bool isSend;
        private bool isRev;

        public event Action<byte[]> CmdEvent;

        public OneServer(Socket soc)
        {
            socket = soc;
            Thread thrRev = new Thread(ReceiveProc);
            thrRev.IsBackground = true;
            isRev = true;
            thrRev.Start(socket);
        }

        public void Dispose()
        {
            try
            {
                isRev = false;
                isSend = false;
                Thread.Sleep(100);
                socket.Close();
            }
            catch (Exception ex)
            {
            }
        }

        private void ReceiveProc(object socket)
        {
            Socket soc = (Socket)socket;
            byte[] buffer = new byte[4096];
            while (isRev)
            {
                try
                {
                    int cnt = 0;
                    if (soc != null && soc.Connected && !soc.Poll(500, SelectMode.SelectRead))
                    {
                        cnt = soc.Receive(buffer);
                    }
                    else
                    {
                        Dispose();
                    }
                    if (cnt > 0)
                    {
                        byte[] cmd = new byte[cnt];
                        Array.Copy(buffer, cmd, cnt);
                        CmdEvent(cmd);
                    }
                    else
                    {
                        Thread.Sleep(1);
                    }
                }
                catch (SocketException socEx)
                {
                    Dispose();
                }
                catch (Exception ex)
                {
                    //Dispose();
                }
            }
        }
    }
}
