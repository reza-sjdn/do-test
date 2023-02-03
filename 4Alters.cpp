// This file makes test sheets of 4-alternatives form
 
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

        output << 4 << " ";
        cout << "Enter four alternatives: \n";
        for (int j{0}; j < 4; ++j) {
            getline(cin, alternative);
            output << quoted(alternative) << " ";
        }
        output.seekp(-1, ios::cur);
        output << "\n";

        output << 1 << " ";
        cout << "Enter the true alternative: ";
        cin >> trueAlt;
        output << trueAlt << "\n";


        cout << "Keep Going? ";
        cin >> ch;
        cin.get();
    }

    return 0;
}
