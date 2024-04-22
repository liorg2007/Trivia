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
using static Client.Helper;
using static Client.LoginSignup;
using static Client.Requests;

namespace Client
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public SignupWindow()
        {
            InitializeComponent();
        }

        private void CancelBtn(object sender, RoutedEventArgs e)
        {
            MainWindow window = new MainWindow();
            window.Show();
            this.Close();
        }

        private void RegisterPress(object sender, RoutedEventArgs e)
        {
            SignupRequest request = new SignupRequest()
            {
                username = Username.Text,
                password = passwordBox.Password,
                address = Address.Text,
                phoneNumber = PhoneNumber.Text,
                email = Email.Text,
                birthDate = BirthDate.Text
            };


            var message = LoginSignup.CreateSignupRequest(request);

            ((App)Application.Current)._server.sendMessage(message);

            ServerResponse response = decodeProtocol(((App)Application.Current)._server.receiveMessage());

            try
            {
                if (CheckSignup(response))
                {
                    MainMenu window = new MainMenu(request.username);
                    window.Show();
                    this.Close();
                }
                else
                {
                    raiseErrorBox("Signup bad");
                }
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
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
            ((App)Application.Current)._musicWorker.CancelAsync();
            Thread.Sleep(50);
            Close();
        }

        private void MinimizeWindow(object sender, RoutedEventArgs e)
        {
            this.WindowState = WindowState.Minimized;
        }

        private void BoxGotFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == ((TextBox)sender).Name)
                ((TextBox)sender).Text = "";
        }

        private void BoxLostFocus(object sender, RoutedEventArgs e)
        {
            if (((TextBox)sender).Text == "")
                ((TextBox)sender).Text = ((TextBox)sender).Name;
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

