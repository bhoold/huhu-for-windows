using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Huhu
{
    class Utility
    {
        public static string GetIPAddress()
        {
            string resultIP = string.Empty;
            System.Net.IPAddress[] ips = System.Net.Dns.GetHostEntry(System.Net.Dns.GetHostName()).AddressList;
            foreach (System.Net.IPAddress ip in ips)
            {
                if (IsCorrentIP(ip.ToString()))
                {
                    resultIP = ip.ToString();
                    break;
                }
            }
            return resultIP;
        }
        private static bool IsCorrentIP(string ip)
        {
            string pattrn = @"(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])";
            if (System.Text.RegularExpressions.Regex.IsMatch(ip, pattrn))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// 获取当前系统时间的方法
        /// </summary>
        /// <returns>当前时间</returns>
        private static DateTime GetCurrentTime()
        {
            DateTime currentTime = new DateTime();
            currentTime = DateTime.Now;
            return currentTime;
        }
    }
}
