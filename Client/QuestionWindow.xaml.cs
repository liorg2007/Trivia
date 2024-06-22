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
using System.Runtime.CompilerServices;

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

        private readonly uint timeForQuestion;
        private uint timeLeft;
        private uint questionsLeft;
        private uint correctAnswers;

        private bool isShowingResult = false;

        public QuestionWindow(uint questionTime, uint questionsLeft)
        {
            InitializeComponent();
            timer.Tick += new EventHandler(timerTick);
            timer.Interval = new TimeSpan(0, 0, 1);

            nextQuestion();

            timeForQuestion = timeLeft = questionTime;
            this.questionsLeft = questionsLeft;
            correctAnswers = 0;

            timerTextBlock.Text = questionTime.ToString() + 's';
            questionsLeftTextBlock.Text = questionsLeft.ToString();
            numCorrectAnswersTextBlock.Text = correctAnswers.ToString();

        }

        private void timerTick(object? sender, EventArgs e)
        {
            timerTextBlock.Text = (--timeLeft).ToString() + 's';
            if (timeLeft == 0)
            {
                submitAnswerAndShowResults();
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
        private void submitOrNextQuestionClick(object? sender, RoutedEventArgs? e)
        {
            if (isShowingResult)
            {
                if (questionsLeft == 0)
                {
                    new GameResultsWindow().Show();
                    this.Close();
                    return;
                }
                if (nextQuestion()) // if succeeded
                {
                    selectedAnswerNumber = 0;
                    if (correctAnswerBorder != null)
                        correctAnswerBorder.Background = nonSelectedAnswerBgBrush;
                    if (selectedAnswerBorder != null)
                        selectedAnswerBorder.Background = nonSelectedAnswerBgBrush;
                    submitAnswerTextBlock.Text = "Submit Answer";
                    isShowingResult = !isShowingResult;
                }
            }
            else
            {
                submitAnswerAndShowResults();
            }
        }
        private void submitAnswerAndShowResults()
        {
            uint correctAnswerId = submitAnswer();
            if (correctAnswerId != 0) // an error hasnt occured
            {
                showCorrectAnswer(correctAnswerId);
                submitAnswerTextBlock.Text = "Next Question";
                isShowingResult = !isShowingResult;
            }
        }
        private uint submitAnswer()
        {
            SubmitAnswerRequest request = new SubmitAnswerRequest();
            request.answerId = selectedAnswerNumber;
            ServerResponse fullResponse = Helper.SendMessageWithByteArr(
                Helper.createProtocol(Code.SubmitAnswer, JsonSerializer.SerializeToUtf8Bytes(request)),
                (App)Application.Current);
            if (fullResponse.code != Code.SubmitAnswer)
            {
                Helper.raiseErrorBox("Server error while submitting answer");
                return 0;
            }
            SubmitAnswerResponse response = JsonPacketDeserializer.DeserializeSubmitAnswerResponse(fullResponse.message);
            if (response.status == 1)
            {
                return response.correctAnswerId;
            }
            else
            {
                Helper.raiseErrorBox("Server error while submitting answer");
                return 0;
            }
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

        private bool nextQuestion()
        {
            ServerResponse fullResponse = Helper.SendMessageWithCode(Code.GetQuestion, (App)Application.Current);
            GetQuestionResponse response = JsonPacketDeserializer.DeserializeGetQuestionResponse(fullResponse.message);
            if (response.status != 1)
            {
                Helper.raiseErrorBox("Server error while getting next question");
                return false; // failed
            }
            else
            {
                showNewQuestion(response.question, response.answers);

                timeLeft = timeForQuestion;
                timerTextBlock.Text = timeLeft.ToString() + 's';
                timer.Start();
                return true; // succeeded
            }
        }

        private void showNewQuestion(string question, string[] answers)
        {
            questionTextBlock.Text = question;
            answerTextBlock1.Text = answers[0];
            answerTextBlock2.Text = answers[1];
            answerTextBlock3.Text = answers[2];
            answerTextBlock4.Text = answers[3];
        }

        /* Window Functions */
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
