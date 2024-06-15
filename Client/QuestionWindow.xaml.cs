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
        private uint selectedAnswerNumber = 0; // a number in the range 1-4, 0 means unselected
        private Border? selectedAnswerBorder = null;
        private Border? correctAnswerBorder = null;

        private readonly SolidColorBrush selectedAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#8549a7"));
        private readonly SolidColorBrush nonSelectedAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#deb7ff"));
        private readonly SolidColorBrush correctAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#58bb43"));
        private readonly SolidColorBrush wrongAnswerBgBrush = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#ee4e4e"));

        private DispatcherTimer timer = new DispatcherTimer();

        private readonly int timeForQuestion;
        private int timeLeft;
        private int questionsLeft;
        private int correctAnswers;

        private bool isShowingResult = false;

        public QuestionWindow(string question, string ans1, string ans2, string ans3, string ans4, int questionTime,
            int questionsLeft, int correctAnswers)
        {
            InitializeComponent();

            questionTextBlock.Text = question;
            answerTextBlock1.Text = ans1;
            answerTextBlock2.Text = ans2;
            answerTextBlock3.Text = ans3;
            answerTextBlock4.Text = ans4;

            timeForQuestion = timeLeft = questionTime;
            this.questionsLeft = questionsLeft;
            this.correctAnswers = correctAnswers;

            timerTextBlock.Text = questionTime.ToString() + 's';
            questionsLeftTextBlock.Text = questionsLeft.ToString();
            numCorrectAnswersTextBlock.Text = correctAnswers.ToString();

            timer.Tick += new EventHandler(timerTick);
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.Start();
        }

        private void timerTick(object? sender, EventArgs e)
        {
            timerTextBlock.Text = (--timeLeft).ToString() + 's';
            if (timeLeft == 0)
            {
                timer.Stop();
                submitAnswer();
            }
        }

        private void selectAnswer(object sender, RoutedEventArgs e)
        {
            if (isShowingResult) return; // avoid selection of answers while showing the correct answer

            Button btn = (Button)sender;
            uint newAnswerNumber = (uint)(((string)btn.Tag)[0] - '0');

            if (selectedAnswerNumber != newAnswerNumber)
            {
                if (selectedAnswerBorder != null)
                    selectedAnswerBorder.Background = nonSelectedAnswerBgBrush;
                // update the seleceted border
                selectedAnswerBorder = (Border)VisualTreeHelper.GetParent(btn);
                selectedAnswerBorder.Background = selectedAnswerBgBrush;
                selectedAnswerNumber = newAnswerNumber; // char to int conversion
            }
        }
        private void submitOrNextQuestionClick(object? sender, RoutedEventArgs e)
        {
            if (isShowingResult)
            {
                nextQuestion();
                submitAnswerTextBlock.Text = "Submit Answer";
            }
            else
            {
                submitAnswer();
                submitAnswerTextBlock.Text = "Next Question";
            }
            isShowingResult = !isShowingResult;
        }
        private void submitAnswer()
        {/*
            SubmitAnswerRequest request = new SubmitAnswerRequest();
            request.answerId = selectedAnswerNumber;
            ServerResponse fullResponse = Helper.SendMessageWithByteArr(
                Helper.createProtocol(Code.SubmitAnswer, JsonSerializer.SerializeToUtf8Bytes(request)),
                (App)Application.Current);
            if (fullResponse.code != Code.SubmitAnswer)
            {
                Helper.raiseErrorBox("Server error while submitting answer");
                return;
            }
            SubmitAnswerResponse response = JsonPacketDeserializer.DeserializeSubmitAnswerResponse(fullResponse.message);
            if (response.status == 1)
            {*/
            showCorrectAnswer(4);//response.correctAnswerId);
            //}
        }

        private void showCorrectAnswer(uint correctAnswerId)
        {
            timer.Stop();
            switch (correctAnswerId)
            {
                case 1: correctAnswerBorder = answerBorder1; break;
                case 2: correctAnswerBorder = answerBorder2; break;
                case 3: correctAnswerBorder = answerBorder3; break;
                case 4: correctAnswerBorder = answerBorder4; break;
                default: return;
            }
            correctAnswerBorder.Background = correctAnswerBgBrush; // show the correct answer as green
            if (selectedAnswerBorder != null && correctAnswerId != selectedAnswerNumber)
            {
                // answer selected is wrong
                selectedAnswerBorder.Background = wrongAnswerBgBrush;
            }
            else
            {
                numCorrectAnswersTextBlock.Text = (++correctAnswers).ToString();
            }
            questionsLeftTextBlock.Text = (--questionsLeft).ToString();
        }

        private void nextQuestion()
        {
            /* get next question from server */

            if (correctAnswerBorder != null)
                correctAnswerBorder.Background = nonSelectedAnswerBgBrush;
            if (selectedAnswerBorder != null)
                selectedAnswerBorder.Background = nonSelectedAnswerBgBrush;
            selectedAnswerNumber = 0;
            timeLeft = timeForQuestion;
            timerTextBlock.Text = timeLeft.ToString() + 's';
            timer.Start();
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
