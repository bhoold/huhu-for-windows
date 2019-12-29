namespace Huhu
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox_Server = new System.Windows.Forms.TextBox();
            this.textBox_Port = new System.Windows.Forms.TextBox();
            this.button_Connect = new System.Windows.Forms.Button();
            this.richTextBox_UserList = new System.Windows.Forms.RichTextBox();
            this.richTextBox_Messages = new System.Windows.Forms.RichTextBox();
            this.richTextBox_Chat = new System.Windows.Forms.RichTextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button_Send = new System.Windows.Forms.Button();
            this.textBox_Nickname = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.button_Close = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(615, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Server";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(627, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "Port";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(597, 177);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "用户列表";
            // 
            // textBox_Server
            // 
            this.textBox_Server.Location = new System.Drawing.Point(688, 25);
            this.textBox_Server.Name = "textBox_Server";
            this.textBox_Server.Size = new System.Drawing.Size(100, 21);
            this.textBox_Server.TabIndex = 3;
            this.textBox_Server.Text = "172.18.18.210";
            // 
            // textBox_Port
            // 
            this.textBox_Port.Location = new System.Drawing.Point(688, 55);
            this.textBox_Port.Name = "textBox_Port";
            this.textBox_Port.Size = new System.Drawing.Size(100, 21);
            this.textBox_Port.TabIndex = 4;
            this.textBox_Port.Text = "9501";
            // 
            // button_Connect
            // 
            this.button_Connect.Location = new System.Drawing.Point(688, 124);
            this.button_Connect.Name = "button_Connect";
            this.button_Connect.Size = new System.Drawing.Size(75, 23);
            this.button_Connect.TabIndex = 5;
            this.button_Connect.Text = "连接";
            this.button_Connect.UseVisualStyleBackColor = true;
            this.button_Connect.Click += new System.EventHandler(this.button_Connect_Click);
            // 
            // richTextBox_UserList
            // 
            this.richTextBox_UserList.Location = new System.Drawing.Point(599, 200);
            this.richTextBox_UserList.Name = "richTextBox_UserList";
            this.richTextBox_UserList.Size = new System.Drawing.Size(189, 238);
            this.richTextBox_UserList.TabIndex = 6;
            this.richTextBox_UserList.Text = "";
            // 
            // richTextBox_Messages
            // 
            this.richTextBox_Messages.Location = new System.Drawing.Point(12, 12);
            this.richTextBox_Messages.Name = "richTextBox_Messages";
            this.richTextBox_Messages.Size = new System.Drawing.Size(542, 248);
            this.richTextBox_Messages.TabIndex = 7;
            this.richTextBox_Messages.Text = "";
            // 
            // richTextBox_Chat
            // 
            this.richTextBox_Chat.Location = new System.Drawing.Point(12, 319);
            this.richTextBox_Chat.Name = "richTextBox_Chat";
            this.richTextBox_Chat.Size = new System.Drawing.Size(542, 90);
            this.richTextBox_Chat.TabIndex = 8;
            this.richTextBox_Chat.Text = "";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 293);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 9;
            this.label4.Text = "To: 全体";
            // 
            // button_Send
            // 
            this.button_Send.Location = new System.Drawing.Point(479, 415);
            this.button_Send.Name = "button_Send";
            this.button_Send.Size = new System.Drawing.Size(75, 23);
            this.button_Send.TabIndex = 10;
            this.button_Send.Text = "发送";
            this.button_Send.UseVisualStyleBackColor = true;
            this.button_Send.Click += new System.EventHandler(this.button_Send_Click);
            // 
            // textBox_Nickname
            // 
            this.textBox_Nickname.Location = new System.Drawing.Point(688, 84);
            this.textBox_Nickname.Name = "textBox_Nickname";
            this.textBox_Nickname.Size = new System.Drawing.Size(100, 21);
            this.textBox_Nickname.TabIndex = 11;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(627, 87);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "Name";
            // 
            // button_Close
            // 
            this.button_Close.Enabled = false;
            this.button_Close.Location = new System.Drawing.Point(599, 124);
            this.button_Close.Name = "button_Close";
            this.button_Close.Size = new System.Drawing.Size(75, 23);
            this.button_Close.TabIndex = 13;
            this.button_Close.Text = "断开";
            this.button_Close.UseVisualStyleBackColor = true;
            this.button_Close.Click += new System.EventHandler(this.button_Close_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button_Close);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox_Nickname);
            this.Controls.Add(this.button_Send);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.richTextBox_Chat);
            this.Controls.Add(this.richTextBox_Messages);
            this.Controls.Add(this.richTextBox_UserList);
            this.Controls.Add(this.button_Connect);
            this.Controls.Add(this.textBox_Port);
            this.Controls.Add(this.textBox_Server);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "huhu客户端";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox_Server;
        private System.Windows.Forms.TextBox textBox_Port;
        private System.Windows.Forms.Button button_Connect;
        private System.Windows.Forms.RichTextBox richTextBox_UserList;
        private System.Windows.Forms.RichTextBox richTextBox_Messages;
        private System.Windows.Forms.RichTextBox richTextBox_Chat;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button_Send;
        private System.Windows.Forms.TextBox textBox_Nickname;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button_Close;
    }
}

