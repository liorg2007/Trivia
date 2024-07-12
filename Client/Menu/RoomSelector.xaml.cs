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
using System.Security;
using System.Diagnostics;
using Client.Rooms;

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

            if (rooms.Count > 0)
            {
                // display each room in the listBox
                foreach (Room room in rooms)
                {
                    ListBoxItem listBoxItem = new ListBoxItem();

                    StackPanel stackPanel = new StackPanel();
                    stackPanel.Orientation = Orientation.Horizontal;

                    TextBlock roomNameText = new TextBlock();
                    roomNameText.Text = room.roomData.name;

                    TextBlock playerCountText = new TextBlock();
                    playerCountText.Text = room.players.Count.ToString() + "/" + room.roomData.maxPlayers;
                    playerCountText.TextAlignment = TextAlignment.Right;

                    Button joinButton = new Button();
                    joinButton.Content = "Join";
                    joinButton.Click += (sender, e) => JoinRoom(room.roomData.id);

                    stackPanel.Children.Add(roomNameText);
                    stackPanel.Children.Add(playerCountText);
                    stackPanel.Children.Add(joinButton);

                    listBoxItem.Content = stackPanel;

                    roomList.Items.Add(listBoxItem);
                }
            }
            else
            {
                // Prompt a message saying there are no rooms open in the ListBox
                ListBoxItem listBoxItem = new ListBoxItem();
                listBoxItem.HorizontalContentAlignment = HorizontalAlignment.Stretch;

                TextBlock textBlock = new TextBlock();
                textBlock.Text = "There are no rooms open!";
                textBlock.TextAlignment = TextAlignment.Center;
                textBlock.Width = double.NaN; // same as "Auto" in the XAML

                listBoxItem.Content = textBlock;
                roomList.Items.Add(listBoxItem);
            }
        }

        private List<Room> GetRooms()
        {
            //Get first the rooms 
            List<RoomData> rooms = getExistingRooms();
            List<Room> roomsWithPeople = new List<Room>();

            //Get each rooms users
            foreach(var roomData in rooms)
            {
                Room room = new Room();
                room.roomData = roomData;
                room.players = GetUsersInRoom(roomData.id);
                roomsWithPeople.Add(room);
            }

            return roomsWithPeople;
        }

        private List<RoomData> getExistingRooms()
        {
            ServerResponse response;
            GetRoomsResponse roomsResponse;
            var message = RoomManagement.CreateGetRoomsRequests();
            try
            {
               response = SendMessageWithByteArr(message, ((App)Application.Current));
            }
            catch
            {
                raiseErrorBox("Server problem");
                System.Environment.Exit(0);
                return new List<RoomData>();
            }

            try
            {
                if (response.code == Code.GetRooms)
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

        private List<string> GetUsersInRoom(uint roomId)
        {
            ServerResponse response;
            GetUsersInRoomRequest getUsersInRoomRequest = new GetUsersInRoomRequest() { roomId = roomId };
            GetUsersInRoomResponse playersResponse;

            var message = RoomManagement.CreateGetUsersInRoomsRequests(getUsersInRoomRequest);

            try
            {
                response = SendMessageWithByteArr(message, ((App)Application.Current));
            }
            catch
            {
                raiseErrorBox("Server problem");
                System.Environment.Exit(0);
                return new List<string>();
            }

            try
            {
                if (response.code == Code.GetPlayersInRoom)
                {
                    playersResponse = DeserializeGetUsersInRoomsRequests(response.message);
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
                return new List<string>();
            }

            return playersResponse.PlayersInRoom;
        }


        /* CLICK EVENTS */
        private void RefreshClick(object sender, RoutedEventArgs e)
        {
            roomList.Items.Clear();
            UpdateRoomList();
        }

        public void JoinRoom(uint roomId)
        {
            ServerResponse response;
            JoinRoomRequest joinRoomRequest = new JoinRoomRequest() { roomId = roomId };

            var message = RoomManagement.CreateJoinRoomRequests(joinRoomRequest);

            try
            {
                response = SendMessageWithByteArr(message, ((App)Application.Current));
            }
            catch
            {
                raiseErrorBox("Server problem");
                System.Environment.Exit(0);
                return;
            }

            try
            {
                if (response.code == Code.JoinRoom && DeserializeJoinRoomResponse(response.message).status == 1)
                {
                    RoomMember window = new RoomMember(_username);
                    window.Show();
                    this.Close();
                }
                else
                {
                    raiseSuccessBox("Can't enter room!");

                }
            }
            catch (Exception ex)
            {
                raiseErrorBox(ex.Message);
                System.Environment.Exit(0);
            }
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
