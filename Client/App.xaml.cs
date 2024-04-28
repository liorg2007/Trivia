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
using System.Media;
using System.ComponentModel;
using System.Windows.Media;
using System.Windows.Controls;

namespace Client
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    /// 

    public partial class App : Application
    {
        public BackgroundWorker? _musicWorker = null;
        public Server _server;

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            ServerData connDetails = new ServerData();
            _server = new Server();

            try
            {
                connDetails = _server.getServerConnData();
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }

            // ((App)Application.Current)._sound.Stop();
            //   _musicWorker.CancelAsync();

            if (!_server.connectToServer(connDetails))
            {
                raiseErrorBox("Can't connect to server");
                System.Environment.Exit(0);
            }

            _musicWorker = new BackgroundWorker();
            _musicWorker.WorkerSupportsCancellation = true;
            _musicWorker.WorkerReportsProgress = false;
            _musicWorker.DoWork += music_player;

            _musicWorker.RunWorkerAsync();

            LoginWindow mainWindow = new LoginWindow();
            mainWindow.Show();
        }


        static void music_player(object sender, DoWorkEventArgs e)
        {
            var rand = new Random();
            var files = Directory.GetFiles("../../../Music", "*.wav");
            var selected = files[rand.Next(files.Length)];

            SoundPlayer player = new SoundPlayer(selected);
            player.Play();

            while (true)
            {
                if (((App)Application.Current)._musicWorker.CancellationPending)
                {
                    player.Stop();
                    e.Cancel = true;
                    break;
                }
                Thread.Sleep(50);
            }
        }
    }

}
