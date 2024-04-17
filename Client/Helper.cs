using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Client
{
    internal static class Helper
    {
        public static void raiseErrorBox(string message)
        {
            MessageBoxButton button = MessageBoxButton.OK;
            MessageBoxImage icon = MessageBoxImage.Warning;
            MessageBox.Show(message, "Error", button, icon, MessageBoxResult.Yes);
        }
    }
}
