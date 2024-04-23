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
using System.Text.RegularExpressions;


namespace Client
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        private static readonly SolidColorBrush VALID_INPUT_BACKGROUND = Brushes.Transparent;
        private static readonly SolidColorBrush INVALID_INPUT_BACKGROUND = Brushes.Tomato;
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

            if (!CheckSignupInput(request))
            {
                raiseErrorBox("Signup input is not valid!\n" +
                    "- Password must have 8 chars and contain capitalized and uncapitalized characters" +
                    " + a digit + a special character.\n" +
                    "- Email must be in a valid email format.\n" +
                    "- Address is in form (Street,Apt,City)\n" +
                    "- Phone number always starts with 0 and is in length of 10 numbers.\n" +
                    "- Birth date is in form DD/MM/YYYY.");
                return;
            }
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
                    raiseErrorBox("Error signing up: username \"" + request.username + "\" already exists.");
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
            ((TextBox)sender).Background = VALID_INPUT_BACKGROUND;
            if (((TextBox)sender).Text == ((TextBox)sender).Name)
                ((TextBox)sender).Text = "";
        }

        private void BoxLostFocus(object sender, RoutedEventArgs e)
        {
            TextBox textBox = (TextBox)sender;
            if (textBox.Text == "")
                textBox.Text = textBox.Name;
            else
            {
                string? regex = GetRegexFromName(textBox.Name);
                if (regex is not null)
                {
                    if (Regex.IsMatch(textBox.Text, regex))
                        textBox.Background = VALID_INPUT_BACKGROUND;
                    else
                        textBox.Background = INVALID_INPUT_BACKGROUND;
                }
            }
        }
        private static string? GetRegexFromName(string name)
        {
            return name switch
            {
                "Email" => EMAIL_REGEX,
                "Address" => ADDRESS_REGEX,
                "PhoneNumber" => PHONE_NUMBER_REGEX,
                "BirthDate" => BIRTH_DATE_REGEX,
                _ => null
            };
        }

        private void PasswordGotFocus(object sender, RoutedEventArgs e)
        {
            ((PasswordBox)sender).Background = VALID_INPUT_BACKGROUND;
            if (((PasswordBox)sender).Password == "Password")
                ((PasswordBox)sender).Password = "";
        }

        private void PasswordLostFocus(object sender, RoutedEventArgs e)
        {
            PasswordBox passwordBox = (PasswordBox)sender;
            if (passwordBox.Password == "")
                passwordBox.Password = "Password";
            else
            {
                if (Regex.IsMatch(passwordBox.Password, PASSWORD_REGEX))
                    passwordBox.Background = VALID_INPUT_BACKGROUND;
                else
                    passwordBox.Background = INVALID_INPUT_BACKGROUND;
            }
        }
    }
}

