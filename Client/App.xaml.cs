using System.Configuration;
using System.Data;
using System.Runtime.CompilerServices;
using System.Windows;
using System.IO;
using static Client.Server;
using static Client.Helper;
using System.Diagnostics;
using System.Threading;
using static Client.Requests;

namespace Client
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    /// 

    public partial class App : Application
    {
        public Server _server;

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            ServerData connDetails = new ServerData();
            _server = new Server();

            try
            {
                connDetails = _server.getServerConnData();
            }
            catch(Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }

            if (!_server.connectToServer(connDetails))
            {
                raiseErrorBox("Can't connect to server");
                System.Environment.Exit(0);
            }


            MainWindow mainWindow = new MainWindow();
            mainWindow.Show();
        }

        
    }

}
