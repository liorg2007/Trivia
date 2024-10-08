﻿using System;
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
using static System.Byte;
using static Client.Helper;
using static Client.LoginSignup;
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
            LoginRequest request = new LoginRequest()
            {
                password = passwordBox.Password,
                username = usernameBox.Text
            };

            var message = LoginSignup.CreateLoginRequest(request);
            try
            {
                ServerResponse response = Helper.SendMessageWithByteArr(message, (App)Application.Current);
                if (CheckLogin(response))
                {
                    MainMenu window = new MainMenu(request.username);
                    window.Show();
                    this.Close();
                }
                else
                {
                    raiseErrorBox("Login credentials are invalid.");
                }
            }
            catch
            {
                raiseErrorBox("Server error");
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