#include <iostream>
#include <string>
#include <cmath>
using namespace std;
enum enLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizz {
    stQuestion Questions[100];
    short NumberOfQuestions;
    enLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};
string GetOpTypeSymbol(enOperationType OperationType)
{
    string OperationsType[5] = { "+", "-", "*", "/", "Mix" };
    return OperationsType[OperationType - 1];
}
string GetQuestionLevelText(enLevel Level)
{
    string Lvl[4] = { "Easy", "Mid", "Hard", "Mix" };
    return Lvl[Level - 1];
}
string GetFinalResultsText(bool IsPass)
{
    if (IsPass)
    {
        return "Pass :-)";
    }

    return "Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz) {
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType             : " << GetOpTypeSymbol(Quizz.OperationType) << endl;
    cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}
void SetScreenColor(bool Right)
{
    if (Right)
    {
        system("color 2F"); //turn screen to Gre
    }
    else {
        system("color 4F"); //turn screen to Red
        cout << "\a";
    }
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.Questions[QuestionNumber].PlayerAnswer != Quizz.Questions[QuestionNumber].CorrectAnswer)
    {
        Quizz.Questions[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "Worng Answer :-( \n";
        cout << "The right answer is: ";
        cout << Quizz.Questions[QuestionNumber].CorrectAnswer;
        cout << "\n";

    }
    else
    {
        Quizz.Questions[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "Right Answer :-) \n";
    }
    SetScreenColor(Quizz.Questions[QuestionNumber].AnswerResult);

}
int ReadAnswer()
{
    int answer = 0;
    cin >> answer;
    return answer;
}
void PrintQuestion(stQuestion Question, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber << "]:\n\n";
    cout << Question.Number1;
    cout << " " << GetOpTypeSymbol(Question.OperationType) << " ";
    cout << Question.Number2;
    cout << " = ??? \n";
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quizz.Questions[QuestionNumber], QuestionNumber);

        Quizz.Questions[QuestionNumber].PlayerAnswer = ReadAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Add: return Number1 + Number2;
    case enOperationType::Sub: return Number1 - Number2;
    case enOperationType::Mul: return Number1 * Number2;
    case enOperationType::Div: return Number1 / Number2;
    }
}
int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From; // Not Include The End. So We Add 1 => To
    return RandNum;
}
stQuestion GenrateQuestion(enLevel QuestionLevel, enOperationType OperationType)
{
    stQuestion Question;

    if (QuestionLevel == enLevel::Mix)
        Question.QuestionLevel = (enLevel)RandomNumber(1, 3);

    if (OperationType == enOperationType::MixOp)
        Question.OperationType = (enOperationType)RandomNumber(1, 4);

    switch (Question.QuestionLevel)
    {
    case enLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enLevel::Mid:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

    return Question;
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.Questions[Question] = GenrateQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
    }
}
enOperationType ReadOperationType()
{
    short OperationType = 0;
    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? \n";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);
    return (enOperationType)OperationType;
}
enLevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;
    do {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?\n";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enLevel)QuestionLevel;
}
short ReadHowManyQuestions()
{
    short Number = 0;
    do {
        cout << "How Many Questions do you want to answer ? ";
        cin >> Number;
    } while (Number < 0 || Number > 10);

    return Number;
}
void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OperationType = ReadOperationType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}
void ResetScreen()
{
    system("cls");
    system("color 0f");
}
void StartGame()
{
    char PlayAgain = 'Y';

    do {
        ResetScreen();
        PlayMathGame();
        cout << "\nDo You Play Again ? Y/N ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}


