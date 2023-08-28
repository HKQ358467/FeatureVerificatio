using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Xml;

namespace XMLConfigVerficatio
{
    public class ConfigLoad
    {
        static XmlDocument xmlDown;
        /// <summary>
        /// 加载配置文件
        /// </summary>
        private static void ConfigInit()
        {
            string basepath = AppContext.BaseDirectory;
            string configFile = basepath + "/config.xml";
            xmlDown = new XmlDocument();
            xmlDown.Load(configFile);
        }
        /// <summary>
        /// 读取配置信息
        /// </summary>
        /// <param name="config"></param>
        /// <returns></returns>
        private static string GetConfigValue(string config)
        {
            if (xmlDown == null)
            {
                ConfigInit();
            }
            XmlNode xn = xmlDown.SelectSingleNode(config);
            string result = "";
            if (xn != null)
            {
                result = xn.InnerText.Trim();
            }
            return result;
        }
        #region 常规配置
        /// <summary>
        /// 设备IP
        /// </summary>
        /// <returns></returns>
        public static string GetDeviceIP()
        {
            return GetConfigValue("/config/CommonConfig/DeviceIP/value");
        }

        /// <summary>
        /// 设备端口
        /// </summary>
        /// <returns></returns>
        public static string GetDevicePort()
        {
            return GetConfigValue("/config/CommonConfig/DevicePort/value");
        }       
        #endregion
    }
}
