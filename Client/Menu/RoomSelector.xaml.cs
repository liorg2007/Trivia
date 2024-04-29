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
using static Client.Helper;
using static Client.Requests;
using static Client.JsonPacketDeserializer;

namespace Client.Menu
{
    /// <summary>
    /// Interaction logic for RoomSelector.xaml
    /// </summary>
    public partial class RoomSelector : Window
    {
        private string _username;
        public RoomSelector(string username)
        {
            _username = username;
            InitializeComponent();
            UpdateRoomList();
        }

        /* Get the rooms and insert the rooms into the list */
        private void UpdateRoomList()
        {
            List<Room> rooms = GetRooms();
        }

        private List<Room> GetRooms()
        {
            //Get first the rooms 
            List<RoomData> rooms = getExistingRooms();

            return new List<Room>();
        }

        private List<RoomData> getExistingRooms()
        {
            ServerResponse response;
            GetRoomsResponse roomsResponse;
            var message = RoomManagement.CreateGetRoomsRequests();
            try
            {
                ((App)Application.Current)._server.sendMessage(message);
                response = decodeProtocol(((App)Application.Current)._server.receiveMessage());
            }
            catch
            {
                raiseErrorBox("Server problem");
                System.Environment.Exit(0);
                return new List<RoomData>();
            }

            try
            {
                if (response.code == 6)
                {
                    roomsResponse = DeserializeGetRoomsResponse(response.message);
                }
                else
                {
                    throw new Exception("Bad conn");
                }
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
                return new List<RoomData>(); 
            }

            return roomsResponse.rooms;
        }

        private void exitPress(object sender, RoutedEventArgs e)
        {
            MainMenu window = new MainMenu(_username);
            window.Show();
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
