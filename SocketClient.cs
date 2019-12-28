﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace huhu_for_windows
{
    class SocketClient
    {
        private Socket clientSocket;
        private Thread threadServer;
        private IPEndPoint endpoint;
        private string server;
        private string port;
        private string nickname;
        public bool IsConnected = false;
        
        public SocketClient(string server, string port)
        {
            this.server = server;
            this.port = port;


            /*
            Socket s = null;
            IPHostEntry hostEntry = null;

            // Get host related information.
            hostEntry = Dns.GetHostEntry(server);

            // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid
            // an exception that occurs when the host IP Address is not compatible with the address family
            // (typical in the IPv6 case).
            foreach (IPAddress address in hostEntry.AddressList)
            {
                IPEndPoint ipe = new IPEndPoint(address, int.Parse(port));
                Socket tempSocket = new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                try
                {
                    tempSocket.Connect(ipe);
                }
                catch
                {
                    continue;
                }


                if (tempSocket.Connected)
                {
                    s = tempSocket;
                    break;
                }
                else
                {
                    continue;
                }
            }

            if(s != null)
            {
                clientSocket = s;
                IsConnected = true;
            }
            else
            {
                IsConnected = false;
            }
            */




            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            IPAddress ip = IPAddress.Parse(server);
            endpoint = new IPEndPoint(ip, int.Parse(port));

            clientSocket.Connect(endpoint);
            if (clientSocket.Connected)
            {
                IsConnected = true;
            }
            else
            {
                clientSocket = null;
            }




            /*
            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            IPAddress ip = IPAddress.Parse(server);
            endpoint = new IPEndPoint(ip, int.Parse(port));

            threadServer = new Thread(RecMsg);
            threadServer.IsBackground = true;
            threadServer.Start();
            */

        }

        public string Send(string message)
        {
            string page = "";
            Byte[] bytesReceived = new Byte[256];

            if (!IsConnected)
            {
                return page;
            }
            try
            {
                byte[] sendMsg = Encoding.UTF8.GetBytes(message);
                clientSocket.Send(sendMsg, sendMsg.Length, 0);

                int bytes = 0;
                do
                {
                    bytes = clientSocket.Receive(bytesReceived, bytesReceived.Length, 0);
                    page = page + Encoding.UTF8.GetString(bytesReceived, 0, bytes);
                }
                while (bytes > 0);
            }
            catch
            {

            }

            return page;
        }

        public void RecMsg()
        {
            while (true) //持续监听服务端发来的消息
            {
                //定义一个1M的内存缓冲区 用于临时性存储接收到的信息
                byte[] arrRecMsg = new byte[1024 * 1024];
                int length = 0;
                try
                {
                    //将客户端套接字接收到的数据存入内存缓冲区, 并获取其长度
                    length = clientSocket.Receive(arrRecMsg);
                }
                catch
                {
                    return;

                }

                //将套接字获取到的字节数组转换为人可以看懂的字符串
                string strRecMsg = Encoding.UTF8.GetString(arrRecMsg, 0, length);



            }
        }

        public void callback()
        {

        }

        public bool Close()
        {
            if(IsConnected)
            {
                clientSocket.Close();
                clientSocket = null;
                threadServer = null;

                IsConnected = false;
                return true;
            }
            else
            {
                return false;
            }
            
        }
    }
}
