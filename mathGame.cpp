#include<iostream>
#include <time.h>


using namespace std;

enum enType {Add = 1, Sub = 2, Mul = 3, Dev = 4, Mix = 5};
enum enLevel {easy = 1, mid = 2, hard = 3, mix = 4};

struct stQuestion {
    int Number1;
    int Number2;
    string Operation;
    enType Type;
    int PlayerAnswer;
    int answer;
};

struct stQuize{
    stQuestion Questions[100];
    enLevel QuestionsLevel;
    enType QuestionsType;
    int NumberOfQuestions;
    int NumberOfRightAnswers = 0;
};


int Random(int from , int to) {
    int num = rand() % (to - from + 1) + from;

    return num;
}

int readNumberOfQuestions() {
    int Num = 0;
    cout << "\nHow many questions do you want to answer? : ";
    cin >> Num;
    return Num;
}

enLevel readQuestionsLevel() {
    int QuestionsLevel;

    cout << "\nEnter questions level [1] Easy , [2] Mid, [3] Hard, [4] Mix ";
    cin >> QuestionsLevel;

    return (enLevel)QuestionsLevel;
}

enType readQuestionsType() {
    int QuestionsType;
    cout << "\nEnter questions type [1] Add , [2] Sub, [3] Mul, [4] Div , [5] Mix ";
    cin >> QuestionsType;
    return (enType)QuestionsType;
}

void resetScreen() {
    system("clear");
    cout << "\033[0m";
}

string QuestionTypeToString(enType QuestionType) {
    switch (QuestionType)
    {
    case enType::Add:
        return "Add";
    case enType::Dev:
        return "Dev";
    case enType::Mul:
        return "Mul";
    case enType::Sub:
        return "Sub";
    default:
        return "Mix";
    }
}

string QuestionLevelToString(enLevel QuestionLevel) {
    switch (QuestionLevel)
    {
    case enLevel::easy:
        return "Easy";
    case enLevel::hard:
        return "Hard";
    case enLevel::mid:
        return "Mid";
    default:
        return "Mix";
    }
}

stQuestion GenerateQuestion(enType QuestionsType, enLevel QuestionsLevel) {
    stQuestion Question;

    if(QuestionsLevel == enLevel::mix) {
        QuestionsLevel = (enLevel)Random(1,4);
    }

    if(QuestionsType == enType::Mix) {
        QuestionsType = (enType)Random(1,5);
    }

    switch (QuestionsLevel) {
        case enLevel::easy:
            Question.Number1 = Random(1,10);
            Question.Number2 = Random(1,10);
            break;
        case enLevel::mid:
            Question.Number1 = Random(15, 30);
            Question.Number2 = Random(15,30);
            break;
        case enLevel::hard:
            Question.Number1 = Random(50,100);
            Question.Number2 = Random(50,100);
            break;
        default:
            Question.Number1 = Random(15, 30);
            Question.Number2 = Random(15,30);
            break;
    }

    switch (QuestionsType) {
        case enType::Add:
            Question.Operation = "+";
            Question.answer = Question.Number1 + Question.Number2;
            break;
        case enType::Dev:
            Question.Operation = "/";
            Question.answer = Question.Number1 / Question.Number2;
            break;
        case enType::Mul:
            Question.Operation = "*";
            Question.answer = Question.Number1 * Question.Number2;
            break;
        case enType::Sub:
            Question.Operation = "-";
            Question.answer = Question.Number1 - Question.Number2;
            break;
        default:
            Question.Operation = "+";
            Question.answer = Question.Number1 + Question.Number2;
            break;
    }

    

    return Question;
}

void printQuestions(stQuize &Quize) {
    for(int i = 0 ; i < Quize.NumberOfQuestions ; i++) {
        cout << "\nQuestion [" << i << "/" << Quize.NumberOfQuestions << "]: " << endl;
        cout << "\n" << Quize.Questions[i].Number1;
        cout << "\n" << Quize.Questions[i].Operation;
        cout << "\n" << Quize.Questions[i].Number2;
        cout << "\n____________________";
        cout << "\nYour answer: ";
        cin >> Quize.Questions[i].PlayerAnswer;

        if(Quize.Questions[i].PlayerAnswer == Quize.Questions[i].answer) {
            Quize.NumberOfRightAnswers++;
            cout << "\n\033[32mCorrect answer :)\033[0m";
            cout << endl;
        } else {
            cout << "\n\033[31mIncorrect answer :(\033[0m";
            cout << "\nThe correct answer is: " << Quize.Questions[i].answer;
            cout << endl;
        }
    }
}

void printFinalResult(stQuize Quize) {
    string Result = "";
    Result = (Quize.NumberOfRightAnswers >= Quize.NumberOfQuestions - Quize.NumberOfRightAnswers) ? "\033[32mPASS" : "\033[31mFAIL";

    resetScreen();

    cout << "\n\t\tYou " << Result << "\033[0m";
    cout << "\nNUmber of questions: " << Quize.NumberOfQuestions;
    cout << "\nNumber of correct answers: " << Quize.NumberOfRightAnswers;
    cout << "\nNumber of wrong answers: " << Quize.NumberOfQuestions - Quize.NumberOfRightAnswers;
    cout << "\nOperation type: " << QuestionTypeToString(Quize.QuestionsType);
    cout << "\nQuestions level: " << QuestionLevelToString(Quize.QuestionsLevel); 

}

void playGame() {
    stQuize Quize;
    
    Quize.NumberOfQuestions = readNumberOfQuestions();
    Quize.QuestionsLevel = readQuestionsLevel();
    Quize.QuestionsType = readQuestionsType();

    for(int i = 0; i < Quize.NumberOfQuestions ; i++) {
        Quize.Questions[i] = GenerateQuestion(Quize.QuestionsType, Quize.QuestionsLevel);
    }

    printQuestions(Quize);
    printFinalResult(Quize);
}


void startGame() {
    string play = "y";

    do {
        resetScreen();
        playGame();

        cout << "\n\nDo you want to play again? Y/N ";
        cin >> play;
    } while (play == "y" || play == "Y");
}


int main() {
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}