using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Huhu
{
    public partial class MainForm : Form
    {
        private SocketClient client;

        public MainForm()
        {
            InitializeComponent();
        }

        private void button_Connect_Click(object sender, EventArgs e)
        {
            string server = textBox_Server.Text.Trim().ToString();
            string port = textBox_Port.Text.Trim().ToString();
            string nickname = textBox_Nickname.Text.Trim().ToString();

            if (string.IsNullOrEmpty(nickname))
            {
                nickname = Utility.GetIPAddress();
                textBox_Nickname.Text = nickname;
            }


            bool flag = true;

            richTextBox_Messages.Clear();
            if (string.IsNullOrEmpty(server))
            {
                richTextBox_Messages.AppendText("请填上IP地址\r\n");
                flag = false;
            }
            if (string.IsNullOrEmpty(port))
            {
                richTextBox_Messages.AppendText("请填上端口\r\n");
                flag = false;
            }

            if (!flag)
            {
                return;
            }

            if (null != client)
            {
                client.Close();
                client = null;
            }

            button_Connect.Enabled = false;

            Thread thread = new Thread(() =>
            {
                //Console.WriteLine("当前线程ID = " + Thread.CurrentThread.ManagedThreadId); // 是子线程

                bool IsExit = false;
                bool IsRunning = false;
                int step = 1;
                while (!IsExit)
                {
                    if (!IsRunning)
                    {
                        switch (step)
                        {
                            case 1:
                                IsRunning = true;
                                this.BeginInvoke(new Action(delegate ()
                                {
                                    richTextBox_Messages.AppendText("正在连接\r\n");
                                }));
                                client = new SocketClient(server, port);
                                this.BeginInvoke(new Action(delegate ()
                                {
                                    if (!client.IsConnected)
                                    {
                                        button_Connect.Enabled = true;
                                        richTextBox_Messages.AppendText("连接失败\r\n");
                                        IsExit = true;
                                    }
                                    else
                                    {
                                        button_Close.Enabled = true;
                                        richTextBox_Messages.AppendText("连接成功\r\n");
                                        step = 2;
                                    }
                                    IsRunning = false;
                                }));
                                break;

                            case 2:
                                IsRunning = true;
                                this.BeginInvoke(new Action(delegate ()
                                {
                                    richTextBox_Messages.AppendText("正在登录\r\n");
                                }));
                                int msgLen = client.Send("{login:nickname}");
                                Console.WriteLine("登录发送 {0} bytes.", msgLen);
                                client.GetAsyn();
                                /*
                                this.BeginInvoke(new Action(delegate ()
                                {
                                    if (string.IsNullOrEmpty(msg))
                                    {
                                        richTextBox_Messages.AppendText("登录失败\r\n");
                                        IsExit = true;
                                    }
                                    else
                                    {
                                        richTextBox_Messages.AppendText("登录成功\r\n");
                                        step = 3;
                                    }
                                    IsRunning = false;
                                }));*/
                                break;
                        }
                    }
                }
            })
            {
                IsBackground = true
            };
            thread.Start();

            Thread receThread = new Thread(() =>
            {
                bool IsRunning = true;
                while (IsRunning)
                {
                    try
                    {
                        if(null == client)
                        {
                            continue;
                        }
                        Console.WriteLine(5555555);
                        byte[] buffer = new byte[1024 * 1024 * 3];
                        //实际接收到的有效字节数
                        int len = client.Get(buffer); Console.WriteLine(444);
                        if (len == 0)
                        {
                            continue;
                        }
                        string str = Encoding.UTF8.GetString(buffer, 0, len);
                        Console.WriteLine(str);
                        //ShowMsg(socketSend.RemoteEndPoint + ":" + str);
                    }
                    catch { }
                }
            })
            {
                IsBackground = true
            };
            //receThread.Start();


            
        }

        private void button_Close_Click(object sender, EventArgs e)
        {
            if (client != null && client.Close())
            {
                client = null;
                richTextBox_Messages.AppendText("断开成功\r\n");
            }
            else
            {
                richTextBox_Messages.AppendText("断开失败\r\n");
            }
        }

        private void button_Send_Click(object sender, EventArgs e)
        {
            string msg = richTextBox_Chat.Text.ToString();

            if (string.IsNullOrEmpty(msg))
            {
                return;
            }

            int recvmsg = client.Send(msg);
            if (recvmsg > 0)
            {
                richTextBox_Chat.Clear();
            }
            else
            {
                richTextBox_Messages.AppendText("发送失败\r\n");
            }
        }
    }
}
