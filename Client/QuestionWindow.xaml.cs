using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

using static Client.Requests;
using System.Text.Json;

namespace Client
{
    /// <summary>
    /// Interaction logic for QuestionWindow.xaml
    /// </summary>
    public partial class QuestionWindow : Window
    {
        private uint selectedAnswerNumber;
        private Border? selectedAnswerBorder = null;

        private readonly SolidColorBrush selectedAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#8549a7"));
        private readonly SolidColorBrush nonSelectedAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#deb7ff"));
        private readonly SolidColorBrush correctAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#58bb43"));
        private readonly SolidColorBrush wrongAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#ee4e4e"));
        
        private DispatcherTimer timer = new DispatcherTimer();

        private int timeLeft;
        private int questionsLeft;
        private int correctAnswers;
        private int timeBetweenQuestions;
        public QuestionWindow(string question, string ans1, string ans2, string ans3, string ans4, int questionTime,
            int questionsLeft, int correctAnswers, int timeBetweenQuestions)
        {
            InitializeComponent();

            questionTextBlock.Text = question;
            answerTextBlock1.Text = ans1;
            answerTextBlock2.Text = ans2;
            answerTextBlock3.Text = ans3;
            answerTextBlock4.Text = ans4;

            timeLeft = questionTime;
            this.questionsLeft = questionsLeft;
            this.correctAnswers = correctAnswers;
            this.timeBetweenQuestions = timeBetweenQuestions;

            timerTextBlock.Text = questionTime.ToString();
            questionsLeftTextBlock.Text = questionsLeft.ToString();
            correctAnswerTextBlock.Text = correctAnswers.ToString();

            timer.Tick += new EventHandler(timerTick);
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.Start();
        }

        private void timerTick(object? sender, EventArgs e)
        {
            timerTextBlock.Text = (--timeLeft).ToString();
            if (timeLeft == 0)
            {
                timer.Stop();
                submitAnswer();
            }
        }

        private void selectAnswer(object sender, RoutedEventArgs e)
        {
            Button btn = (Button)sender;
            char newAnswerNumber = ((string)btn.Tag)[0];

            if (selectedAnswerNumber != newAnswerNumber)
            {
                if (selectedAnswerBorder != null) 
                    selectedAnswerBorder.Background = nonSelectedAnswerBgBrush;
                // update the seleceted border
                selectedAnswerBorder = (Border)VisualTreeHelper.GetParent(btn);
                selectedAnswerBorder.Background = selectedAnswerBgBrush;
                selectedAnswerNumber = (uint)(((string)btn.Tag)[0] - '0'); // char to int conversion
            }
        }

        private void submitAnswer()
        {

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
