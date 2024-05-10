using System;
using System.Collections;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static Client.Helper;
using static Client.Requests;

namespace Client
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }

        private void RegisterPress(object sender, RoutedEventArgs e)
        {
            SignupWindow window = new SignupWindow();
            window.Show();
            this.Close();
        }

        private void LoginPress(object sender, RoutedEventArgs e)
        {
            bool loginSuccess;
            string username = usernameBox.Text;
            string password = passwordBox.Password;
            try
            {
                loginSuccess = LoginSignup.SendLoginRequest(((App)Application.Current).server, username, password);
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                Environment.Exit(0);
                return;
            }

            if (loginSuccess)
            {
                MainMenu window = new MainMenu(username);
                window.Show();
                this.Close();
            }
            else
            {
                raiseErrorBox("Wrong login credentials, try again.");
            }
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

        private void UsernameGotFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "Username")
                ((TextBox)sender).Text = "";
        }

        private void UsernameLostFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "")
                ((TextBox)sender).Text = "Username";
        }

        private void PasswordGotFocus(object sender, RoutedEventArgs e)
        {
            if (((PasswordBox)sender).Password == "Password")
                ((PasswordBox)sender).Password = "";
        }

        private void PasswordLostFocus(object sender, RoutedEventArgs e)
        {
            if (((PasswordBox)sender).Password == "")
                ((PasswordBox)sender).Password = "Password";
        }
    }
}