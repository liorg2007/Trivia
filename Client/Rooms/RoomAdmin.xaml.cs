﻿using System;
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
using static Client.Requests;

namespace Client.Rooms
{
    /// <summary>
    /// Interaction logic for RoomAdmin.xaml
    /// </summary>
    public partial class RoomAdmin : Window
    {
        private string username;
        private bool ContinueBackgroundThread;
        private static Mutex mut = new Mutex();
        private DataStructs.RoomState roomState;
        public RoomAdmin(string username)
        {
            ContinueBackgroundThread = true;
            InitializeComponent();
            this.username = username;

            Thread thread1 = new Thread(Background_Update_Thread);
            thread1.Start();
        }

        /* Button events */
        void exitPress(object sender, RoutedEventArgs e)
        {
            mut.WaitOne();
            if (WaitingRoomCommands.CloseRoom((App)Application.Current))
            {
                ContinueBackgroundThread = false;
                MainMenu window = new MainMenu(username);
                window.Show();
                this.Close();
            }
            mut.ReleaseMutex();
        }

        void startPress(object sender, RoutedEventArgs e)
        {
            mut.WaitOne();
            DateTime start_time;
            try
            {
                start_time = WaitingRoomCommands.StartGame((App)Application.Current);
                //handle the start game
                ContinueBackgroundThread = false;
                WaitingRoomCommands.startGameInTime(start_time, this, gameStartText, buttonsPanel, roomState, username);
            }
            catch (Exception ex)
            {
                Helper.raiseErrorBox(ex.Message);
            }
            finally
            {
                mut.ReleaseMutex();
            }
        }

        /* Get Update Thread */
        private void Background_Update_Thread()
        {
            while (ContinueBackgroundThread)
            {
                mut.WaitOne();

                if (!ContinueBackgroundThread)//check if while waiting state was changed
                {
                    mut.ReleaseMutex();
                    break;
                }

                ServerResponse response = Helper.SendMessageWithCode(Code.GetRoomState, (App)Application.Current);
                roomState = WaitingRoomCommands.HandleRoomData((App)Application.Current, this, response.message)
                    ?? roomState;

                mut.ReleaseMutex();
                Thread.Sleep(300);
            }
        }

        /* Default screen events*/

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
