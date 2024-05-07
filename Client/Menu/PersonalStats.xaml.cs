using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static System.Byte;
using static Client.Helper;
using static Client.Requests;
using static Client.Menu.Statistics;
using static Client.DataStructs;

namespace Client
{
    /// <summary>
    /// Interaction logic for PersonalStats.xaml
    /// </summary>
    public partial class PersonalStats : Window
    {
        private string _username;

        public PersonalStats(string username)
        {
            InitializeComponent();
            _username = username;

            ShowStats();
        }

        private void ShowStats()
        {
            UserStatistics userStatistics = new UserStatistics();
            var message = CreateStatsRequest();

            ((App)Application.Current)._server.sendMessage(message);

            ServerResponse response = decodeProtocol(((App)Application.Current)._server.receiveMessage());

            try
            {
                userStatistics = GetStats(response);
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }

            //Put stats in labels
            score.Text = "Score: " + userStatistics.score.ToString();
            rightAns.Text = "Correct Answers: " + userStatistics.correctAnswers.ToString();
            wrongAns.Text = "Wrong Answers: " +  (userStatistics.totalAnswers - userStatistics.correctAnswers).ToString();
            avgTime.Text = "Average Time: " +   userStatistics.averageAnswerTime.ToString();
        }


        private void exitPress(object sender, RoutedEventArgs e)
        {
            this.Close();
        }


        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DragMove();
            }
        }

        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            ((App)Application.Current).stopMusic();
            Thread.Sleep(50);
            Close();
        }

        private void MinimizeWindow(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }
    }
}
