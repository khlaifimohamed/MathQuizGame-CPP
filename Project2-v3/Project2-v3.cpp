#include <iostream>
#include<cstdlib>
using namespace std;

enum enOperation
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5
};
enum enLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    MixLvl = 4
};
struct stQuestionInfo
{
    short op1 = 0;
    short op2 = 0;
    enOperation Operation;
    enLevel Level;
    short CorrectAnswer = 0;
    short UserAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizzInfo
{
    stQuestionInfo QuestionList[100];
    short QuestionsNumber;
    enOperation Operation;
    enLevel Level;
    short RightAnswers = 0;
    short WrongAnswers = 0;
    bool isPass = false;
};
short HowManyQuestions() {
    int number;
    do
    {
        cout << "How Many Questions do you want to answer";
        cin >> number;
    } while (number < 1 || number>10);
    return number;
}
enLevel WhatLevel() {
    int number;
    do
    {
        cout << "Enter Question Level [1] Easy [2] Med [3] Hard [4] Mix";
        cin >> number;
    } while (number < 1 || number > 4);
    return (enLevel)number;
}
enOperation ChooseOperation() {
    int number;
    do
    {
        cout << "Enter Operation Type [1] Add [2] Sub [3] Mul [4] Div [5] Mix";
        cin >> number;
    } while (number < 1 || number > 5);
    return (enOperation)number;
}
int RoundNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}
int SimpleCalculator(int op1, int op2, enOperation Operation) {
    switch (Operation) {
    case enOperation::Add:
        return op1 + op2;
    case enOperation::Sub:
        return op1 - op2;
    case enOperation::Mul:
        return op1 * op2;
    case enOperation::Div:
        return op1 / op2;
    default:
        return 0;
    }
}

stQuestionInfo GenerateQuestion(enLevel Level, enOperation Operation) {
    stQuestionInfo QuestionInfo;
    int OP1 = 0, OP2 = 0;
    if (Level == enLevel::MixLvl) {
        Level = (enLevel)RoundNumber(1, 3);
    }
    if (Operation == enOperation::MixOp) {
        Operation = (enOperation)RoundNumber(1, 4);
    }
    QuestionInfo.Level = Level;
    QuestionInfo.Operation = Operation;
    if (QuestionInfo.Level == enLevel::Easy)
    {
        OP1 = RoundNumber(1, 10);
        OP2 = RoundNumber(1, 10);
    }
    else if (QuestionInfo.Level == enLevel::Med) {

        OP1 = RoundNumber(10, 50);
        OP2 = RoundNumber(10, 50);
    }
    else
    {

        OP1 = RoundNumber(50, 100);
        OP2 = RoundNumber(50, 100);
    }
    QuestionInfo.op1 = OP1;
    QuestionInfo.op2 = OP2;
    QuestionInfo.CorrectAnswer = SimpleCalculator(QuestionInfo.op1, QuestionInfo.op2, QuestionInfo.Operation);
    return QuestionInfo;
}
void GenerateQuizzQuestion(stQuizzInfo& QuizzInfo) {
    for (short i = 0; i < QuizzInfo.QuestionsNumber; i++)
    {
        QuizzInfo.QuestionList[i] = GenerateQuestion(QuizzInfo.Level, QuizzInfo.Operation);
    }
}
char OperationSymbol(enOperation operation) {
    switch (operation) {
    case enOperation::Add:
        return '+';
    case enOperation::Sub:
        return '-';
    case enOperation::Mul:
        return '*';
    case enOperation::Div:
        return '/';
    default:
        return '?';
    }
}

void PrintQuestion(stQuestionInfo QuestionInfo) {
    cout << "\n";
    cout << QuestionInfo.op1 << endl;
    cout << QuestionInfo.op2 << " " << OperationSymbol(QuestionInfo.Operation) << endl;
    cout << "-------------------------------------";
}
void AskAndCorrectQuestionListAnswers(stQuizzInfo& QuizzInfo) {
    cout << "\n\n";
    for (short i = 0; i < QuizzInfo.QuestionsNumber; i++)
    {
        cout << "Question [" << i + 1 << "/ " << QuizzInfo.QuestionsNumber << "]\n";
        PrintQuestion(QuizzInfo.QuestionList[i]);
        cin >> QuizzInfo.QuestionList[i].UserAnswer;
        if (QuizzInfo.QuestionList[i].UserAnswer == QuizzInfo.QuestionList[i].CorrectAnswer) {
            QuizzInfo.RightAnswers++;
            QuizzInfo.QuestionList[i].AnswerResult = true;
            cout << "Right Answer :-)";
            system("color 4E");
        }
        else
        {
            QuizzInfo.WrongAnswers++;
            QuizzInfo.QuestionList[i].AnswerResult = false;
            cout << "Wrong Answer :-(";
            cout << "The right Answer is : " << QuizzInfo.QuestionList[i].CorrectAnswer << endl;
            system("color 2E");
        }
    }
    if (QuizzInfo.RightAnswers > QuizzInfo.WrongAnswers) {
        QuizzInfo.isPass = true;
    }
    else
    {
        QuizzInfo.isPass = false;
    }
}
string FinaleMessage(stQuizzInfo QuizzInfo) {
    if (QuizzInfo.isPass) {
        return "PASS";
    }
    else
    {
        return "FAIL";
    }
}
void EndGame(stQuizzInfo QuizzInfo) {
    cout << "\n---------------------------------\n";
    cout << "Final Result is" << FinaleMessage(QuizzInfo);
    cout << "\n---------------------------------\n";
    cout << "Number of Questions : " << QuizzInfo.QuestionsNumber << endl;
    cout << "Question Level " << QuizzInfo.Level << endl;
    cout << "OpType :" << QuizzInfo.Operation << endl;
    cout << "Number Of Right Answers" << QuizzInfo.RightAnswers << "\n";
    cout << "Number Of wrong Answers" << QuizzInfo.WrongAnswers << "\n";
    cout << "\n---------------------------------\n";


}
void STARTGAME() {
    stQuizzInfo QuizzInfo;
    QuizzInfo.QuestionsNumber = HowManyQuestions();
    QuizzInfo.Level = WhatLevel();
    QuizzInfo.Operation = ChooseOperation();
    GenerateQuizzQuestion(QuizzInfo);
    AskAndCorrectQuestionListAnswers(QuizzInfo);
    EndGame(QuizzInfo);
}
int main()
{
    srand((unsigned)time(NULL));
    STARTGAME();
}
