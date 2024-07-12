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
using static Client.DataStructs;
using static Client.Requests;

namespace Client
{
    /// <summary>
    /// Interaction logic for GameResultsWindow.xaml
    /// </summary>
    public partial class GameResultsWindow : Window
    {
        private const int TIME_BETWEEN_REFRESHES = 3000;
        private string username;

        public GameResultsWindow(string username)
        {
            this.username = username;
            InitializeComponent();
            StartWaitingForResults();
        }

        private async void StartWaitingForResults()
        {
            bool stillRunning = true;
            await Task.Run(async () =>
            {
                while (stillRunning)
                {
                    ServerResponse response = Helper.SendMessageWithCode(Code.GetGameResults, (App)Application.Current);
                    GetGameResultsResponse serializedRes = JsonPacketDeserializer.DeserializeGetGameResultsResponse(response.message);
                    if (serializedRes.status == 1)
                    {
                        stillRunning = false;
                        await Application.Current.Dispatcher.InvokeAsync(() => SetResults(serializedRes.results));
                    }
                    await Task.Delay(TIME_BETWEEN_REFRESHES);
                }
            });
        }

        private void SetResults(List<PlayerResults> results)
        {
            var orderedResults = results.OrderByDescending(res => res.correctAnswerCount).ThenBy(res => res.averageAnswerTime);
            resultsListBox.Items.Clear();
            foreach (var (result, index) in orderedResults.Select((result, index) => (result, index)))
            {
                Grid grid = new();
                ColumnDefinition placeColumn = new();
                placeColumn.Width = new GridLength(0.5, GridUnitType.Star);
                grid.ColumnDefinitions.Add(placeColumn);
                for (int i = 0; i < 4; i++)
                {
                    grid.ColumnDefinitions.Add(new ColumnDefinition());
                }
                TextBlock placeTB = new();
                TextBlock usernameTB = new();
                TextBlock correctAnswersTB = new();
                TextBlock wrongAnswersTB = new();
                TextBlock avgTimeTB = new();

                placeTB.Text = (index + 1).ToString();
                placeTB.FontSize = 30;
                usernameTB.Text = result.username;
                correctAnswersTB.Text = result.correctAnswerCount.ToString();
                wrongAnswersTB.Text = result.wrongAnswerCount.ToString();
                avgTimeTB.Text = result.averageAnswerTime.ToString();

                grid.Children.Add(placeTB);
                Grid.SetColumn(placeTB, 0);
                grid.Children.Add(usernameTB);
                Grid.SetColumn(usernameTB, 1);
                grid.Children.Add(correctAnswersTB);
                Grid.SetColumn(correctAnswersTB, 2);
                grid.Children.Add(wrongAnswersTB);
                Grid.SetColumn(wrongAnswersTB, 3);
                grid.Children.Add(avgTimeTB);
                Grid.SetColumn(avgTimeTB, 4);

                ListBoxItem listBoxItem = new();
                listBoxItem.Content = grid;
                resultsListBox.Items.Add(listBoxItem);
            }
        }

        /* Window Functions */
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

        private void BackToMenu_Click(object sender, RoutedEventArgs e)
        {
            new MainMenu(username).Show();
            this.Close();
        }
    }
}
