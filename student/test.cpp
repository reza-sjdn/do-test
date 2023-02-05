// This file is driver program for taking tests

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;


// Question type definition
struct Question {
    string question;
    vector<string> alters;
    vector<int> trueAlt;
};


// Vector of questions
vector<Question> vect;


void drawLine (ostream&, int, char);




int main () {
    // Get the name of test file
    cout << "Please enter the name of the test: ";
    string testName;
    getline(cin, testName);

    cout << "\n=====>> "<< testName << " <<=====\n";
    
    // Opening questions file for reading questions into program
    ifstream input{testName + ".txt"};
    if (!input) {
        cout << "File couldn't be opened!\n";
        exit(EXIT_FAILURE);
    }


    // The date and time of taking the test
    time_t rawTime;
    time(&rawTime);
    struct tm* timeInfo;
    timeInfo = localtime(&rawTime);
    char dateOfTest[30];
    strftime(dateOfTest, 30, "%a %b %d %Y %I:%M %p", timeInfo);


    Question q;
    string question;
    int num;
    string alter;
    int trueAlt;



    // Populating vector with questions from the file
    input >> quoted(question);
    q.question = question;
    while (input) {
        input >> num;
        q.alters.clear();
        for (int j{0}; j < num; ++j) {
            input >> quoted(alter);
            q.alters.push_back(alter);
        }

        input >> num;
        q.trueAlt.clear();
        for (int j{0}; j < num; ++j) {
            input >> trueAlt;
            q.trueAlt.push_back(trueAlt);
        }

        vect.push_back(q);

        input >> quoted(question);
        q.question = question;
    }




    // The answer that user gives in each question
    int userAnswer;
    // Collector of user answers
    int userAnswersArr[vect.size()];


    // Test Show
    // Loops questions
    char ans;
    for (int q{0}; q < vect.size(); ++q) {
        drawLine(cout, 84, '-');
        cout << q + 1 << ") " << vect[q].question << endl << endl;

        // Loops alters
        for (int a{0}; a < vect[q].alters.size(); ++a) {
            cout << a + 1 << ". " << left << setw(18) << vect[q].alters[a];
        }

        // Get user answer and add it to user answer collector
        cout << endl;
        do {
            cout << "Enter your answer: ";
            cin >> userAnswer;
        } while (userAnswer <= 0 || userAnswer > vect[q].alters.size());

        userAnswersArr[q] = userAnswer;
        drawLine(cout, 84, '-');


        // Maybe user wants to get back to a specific question
        cout << endl;
        do {
            cout << "(+ : continue, - : return) ==> ";
            cin >> ans;
        } while (ans != '+' && ans != '-');
        cout << endl;


        if (ans == '-') {
            int num;
            do {
                cout << "Enter the number of question you want to get back to: ";
            cin >> num;
            } while (num <= 0 || num > q + 1);


            int newAlt;
            do {
                cout << "Enter new alternative: ";
                cin >> newAlt;
            } while (newAlt <= 0 || newAlt > vect[num - 1].alters.size());

            userAnswersArr[num - 1] = newAlt;
            cout << "Change applied.\n\n";
        }
    }




    // Here, I'm creating a numerical separator of date and time
    // for distinguishing files from each other
    char separator[15];
    strftime(separator, 15, "%Y%m%d%H%M%S", timeInfo);
    

    // Calculating the score and mark and Displaying the result
    // and Outputing the wrong questions into file
    ofstream output1{testName + separator + "_WAQ.txt", ios::out};
    if (!output1) {
        cerr << "File couldn't be opened!\n";
        exit(EXIT_FAILURE);
    }

    // The number of correct answered questions
    int trueOnes{0};
    // If user makes the correct choice flag goes up
    int flag;

    cout << "\n\nQuestions That You Answered Wrong: \n";
    output1 << dateOfTest << endl << endl;
    for (int i{0}; i < vect.size(); ++i) {
        flag = 0;
        for (int j{0}; j < vect[i].trueAlt.size(); ++j) {
            if (userAnswersArr[i] == vect[i].trueAlt[j]) flag = 1;
        }

        if (flag) ++trueOnes;
        else {
            // Display the wrong answered questions
            drawLine(cout, 84, '.');
            cout << i + 1 << ") " << vect[i].question << endl;
            cout << "Your choice was " << userAnswersArr[i];
            cout << " (" << vect[i].alters[userAnswersArr[i] - 1] << "), ";
            cout << "but the correct alternative is ";
            for (int k{0}; k < vect[i].trueAlt.size(); ++k) {
                if (k == vect[i].trueAlt.size() - 1) {
                    cout << vect[i].trueAlt[k] << " (" << 
                        vect[i].alters[vect[i].trueAlt[k] - 1] << ")" << endl;
                }
                else {
                    cout << vect[i].trueAlt[k] << " (" <<
                        vect[i].alters[vect[i].trueAlt[k] - 1] << ")" << " or ";
                }
            }

            drawLine(cout, 84, '.');


            // Output the wrong answered questions into file
            output1 << i + 1 << ") " << vect[i].question << endl;
            output1 << "Your choice was " << userAnswersArr[i];
            output1 << " (" << vect[i].alters[userAnswersArr[i] - 1] << "), ";
            output1 << "but the correct alternative is ";
            for (int k{0}; k < vect[i].trueAlt.size(); ++k) {
                if (k == vect[i].trueAlt.size() - 1) {
                    output1 << vect[i].trueAlt[k] << " (" << 
                        vect[i].alters[vect[i].trueAlt[k] - 1] << ")" << endl;
                }
                else {
                    output1 << vect[i].trueAlt[k] << " (" <<
                        vect[i].alters[vect[i].trueAlt[k] - 1] << ")" << " or ";
                }
            }

            drawLine(output1, 80, '~');
        }
    }

    if (trueOnes == vect.size()) {
        cout << "You answered all the questions correctly :)\n";
        output1 << "no wrong answered question :)\n";
    }



    double score{(static_cast<double>(trueOnes) / vect.size()) * 100};

    char mark;
    if (score >= 90) mark = 'A';
    else if (score >= 80) mark = 'B';
    else if (score >= 70) mark = 'C';
    else if (score >= 60) mark = 'D';
    else mark = 'F';

    cout << endl << endl;
    drawLine(cout, 84, '=');
    cout << "You Got " << mark << ".\n";
    cout << fixed << setprecision(2);
    cout << "You Answered Correctly " << trueOnes << " Questions From " <<
        vect.size() << " Questions. That Is " << score << "%\n";
    drawLine(cout, 84, '=');




    // Put the previous results into a file
    // The latest results go to the bottom of the file
    ofstream output2{testName + "_results.txt", ios::app};
    if (!output2) {
        cerr << "File couldn't be opened!\n";
        exit(EXIT_FAILURE);
    }

    output2 << dateOfTest << endl;
    output2 << "You Got " << mark << ".\n";
    output2 << fixed << setprecision(2);
    output2 << "You Answered Correctly " << trueOnes << " Questions From " <<
        vect.size() << " Questions. That Is " << score << "%\n";
    drawLine(output2, 80, '~');
    output2 << endl;

    return 0;
}


void drawLine (ostream& output, int num, char ch) {
    for (int i{0}; i < num; ++i) output << ch;
    output << endl;
}
