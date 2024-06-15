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
        public Server _server { get; } = new();
        private SoundPlayer _musicPlayer = new();

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            new QuestionWindow("what?" , "1", "2", "3", "4", 20, 3, 3).Show();
            /*ServerData connDetails = new ServerData();

            try
            {
                connDetails = _server.getServerConnData();
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }

            if (!_server.connectToServer(connDetails))
            {
                raiseErrorBox("Can't connect to server");
                System.Environment.Exit(0);
            }

            startMusic();

            LoginWindow mainWindow = new LoginWindow();
            mainWindow.Show();*/
        }

        public void startMusic()
        {
            Random rand = new();
            var files = Directory.GetFiles("../../../Music", "*.wav");
            var selectedMusicFile = files[rand.Next(files.Length)];
            _musicPlayer.SoundLocation = selectedMusicFile;
            continueMusic();
        }

        public void continueMusic()
        {
            _musicPlayer.Play();
        }

        public void stopMusic()
        {
            _musicPlayer.Stop();
        }
    }
}
