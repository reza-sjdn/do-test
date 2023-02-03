// This file makes test sheets
 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main () {
    cout << "Please name your test: ";
    string testName;
    getline(cin, testName);

    ofstream output{testName + ".txt", ios::app};
    if (!output) {
        cerr << "File couldn't be opened!\n";
        exit(EXIT_FAILURE);
    }

    string question;
    string alternative;
    int trueAlt;

    char ch{'y'};
    while (ch == 'y') {
        cout << "\nEnter question: ";
        getline(cin, question);
        output << quoted(question) << "\n";

        cout << "How many alternatives will you provide? ";
        int num;
        cin >> num;
        output << num << " ";

        cout << "Enter alternatives: \n";
        cin.get();
        for (int j{0}; j < num; ++j) {
            getline(cin, alternative);
            output << quoted(alternative) << " ";
        }
        output.seekp(-1, ios::cur);
        output << "\n";

        cout << "How many true alternatives will you provide? ";
        cin >> num;
        output << num << " ";

        cout << "Enter true alternatives: ";
        for (int j{0}; j < num; ++j) {
            cin >> trueAlt;
            output << trueAlt << " ";
        }
        output.seekp(-1, ios::cur);
        output << "\n";


        cout << "Keep Going? ";
        cin >> ch;
        cin.get();
    }

    return 0;
}
