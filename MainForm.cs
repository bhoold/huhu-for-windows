using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace huhu_for_windows
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

            if(string.IsNullOrEmpty(nickname))
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

            if(client == null)
            {
                client = new SocketClient(server, port);
                if(!client.IsConnected)
                {
                    richTextBox_Messages.AppendText("连接失败\r\n");
                    return;
                }
                else
                {
                    richTextBox_Messages.AppendText("连接成功\r\n");
                }
            }

            string msg = client.Send("{login:$nickname}");
            if (string.IsNullOrEmpty(msg))
            {
                richTextBox_Messages.AppendText("登录失败\r\n");
            }
            else
            {
                richTextBox_Messages.AppendText("登录成功\r\n");
            }

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

            string recvmsg = client.Send(msg);
            if (string.IsNullOrEmpty(recvmsg))
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
