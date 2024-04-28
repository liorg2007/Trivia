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

namespace Client.Menu
{
    /// <summary>
    /// Interaction logic for RoomCreator.xaml
    /// </summary>
    public partial class RoomCreator : Window
    {
        public RoomCreator()
        {
            InitializeComponent();
        }

        private void BoxGotFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "Room Name")
                ((TextBox)sender).Text = "";
        }

        private void BoxLostFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "")
                ((TextBox)sender).Text = "Room Name";
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
            ((App)Application.Current)._musicWorker.CancelAsync();
            Thread.Sleep(50);
            Close();
        }

        private void MinimizeWindow(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }
    }
}
