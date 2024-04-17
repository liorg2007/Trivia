using System.Configuration;
using System.Data;
using System.Runtime.CompilerServices;
using System.Windows;
using System.IO;
using static Client.Helper;

namespace Client
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    /// 

    struct ServerData
    {
        public string ip;
        public int port;
    }

    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            try
            {
                ServerData connDetails = getServerConnData();
            }
            catch(Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }

            MainWindow mainWindow = new MainWindow();

            mainWindow.Show();
        }

        private ServerData getServerConnData()
        {
            const string serverDataFileName = "serverConfig.txt";
            var serverData = new ServerData();

            if (!File.Exists(serverDataFileName))
                throw new Exception("No serverConfig.txt file!");

            string[] data = File.ReadAllLines(serverDataFileName);

            try
            {
                serverData.ip = data[0];
                serverData.port = int.Parse(data[1]);
            }
            catch
            {
                throw new Exception("Can't read from config file!");
            }

            return serverData;
        }
    }

}
