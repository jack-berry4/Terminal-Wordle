#ifndef STATS
#define STATS

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

// stats.txt will be in the format:
// [# of tries] [guessing word]


void showStats() {

    // getting stats
    ifstream file;
    file.open("stats.txt", ios::in);

    if (file.is_open()) {
        int totalGames = 0, totalAttempts = 0, wins = 0, curStreak = 0, longestStreak = 0;
        vector<int> allAttempts;
        vector<string> allWords;
        string word;
        while(file >> word) {
            int attempts = stoi(word);
            file >> word;

            if (attempts < 7) {
                wins++;
                curStreak++;
                if (curStreak > longestStreak) longestStreak = curStreak;
            } else curStreak = 0;

            allAttempts.push_back(attempts);
            allWords.push_back(word);

            totalGames++;
            totalAttempts += (attempts < 7 ? attempts : 6);
        }

        
    // outputting stats

        cout << "==========================\n    STATISTICS SUMMARY\n==========================\n";
        cout << setprecision(3);
        cout << "Times Played:" << setw(13) << totalGames << endl;
        cout << "Average Attempts:" << setw(9) << (totalGames==0 ? 0:(totalAttempts / totalGames)) << endl;
        cout << "Win Percentage:" << setw(10) << (totalGames==0 ? 0:(100.0*(((double) wins) / totalGames))) << "%" << endl;
        cout << "Current Streak:" << setw(11) << curStreak << endl;
        cout << "Longest Streak:" << setw(11) << longestStreak << endl;

        cout << "\n\n--------------------------\nWORD     ATTEMPTS      WIN\n--------------------------\n";

        for(int i=0; i<allWords.size();i++) {
            cout << allWords[i] << setw(12) << (allAttempts[i] < 7 ? allAttempts[i] : 6) << setw(9) << (allAttempts[i] < 7 ? "Yes" : "No") << endl;
        }

    } else {
        cout << "Error Reading stats.txt" << endl;
    }

    cout << "\nPress [enter] to continue\n";
    cin.ignore();
}

void resetStats(){
    ofstream file;
    file.open("stats.txt");
    if (file.is_open()) file.close();
}

#endif