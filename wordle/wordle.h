#ifndef WORDLE
#define WORDLE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#define CLEAR_TERMINAL "\033[2J\033[1;1H"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GRAY  "\033[90m"

using namespace std;

bool validWord(string filename, string word) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if(file.is_open()) {
        while(getline(file, line)){
            if (word == line) return true;
        }
        file.close();
    } else {
        cout << "Error opening file: "+filename;
        return false;
    }
    return false;
}

string getCol(string correct, string word, int pos){
    if(word[pos] == correct[pos]) {
        return GREEN;
    } else if(correct.find(word[pos]) != string::npos) {
        return YELLOW;
    } else {
        return GRAY;
    }
}

void outputWords(vector<string> guesses, string correct) {
    //cout << correct << endl;      // TODO output list of your guesses with correct coloring
                                    // TODO plus update keyboard status.txt

    // update keyboard status

    vector<string> col;
    
    ifstream statusIn;
    statusIn.open("../keyboard/status.txt", ios::in);
    string line;
    if(statusIn.is_open()) {
        while(getline(statusIn, line)){
            col.push_back(line);
        }
        statusIn.close();
    } else {
        cout << "Error opening status.txt";
        return;
    }

    if (guesses.size() != 0) {
        string guess = guesses[guesses.size()-1];
        for(int j=0;j<5;j++){
            if(guess[j] == correct[j]) {
                //set green
                col[guess[j]-'a'] = GREEN;
            } else if(correct.find(guess[j]) != string::npos) {
                //set yellow if not green
                if(col[guess[j]-'a'] != GREEN) col[guess[j]-'a'] = YELLOW;
            } else {
                //set grey if not yellow or green
                if(col[guess[j]-'a'] != GREEN && col[guess[j]-'a'] != YELLOW) col[guess[j]-'a'] = GRAY;
            }
        }
    }

    ofstream statusOut;
    statusOut.open("../keyboard/status.txt", ios::out);
    
    if (statusOut.is_open()) {
        for(int i=0;i<26;i++) statusOut << col[i] << endl;
        statusOut.close();
    } else {
        cout << CLEAR_TERMINAL << "Error opening keyboard status.txt";
        return;
    }

    for(int i=0;i<guesses.size();i++){
        string guess = guesses[i];
        cout << getCol(correct,guess,0) << " ---  " << getCol(correct,guess,1) << "---  " << getCol(correct,guess,2) << "---  " << getCol(correct,guess,3) << "---  " << getCol(correct,guess,4) << "---  " << endl;
        cout << getCol(correct,guess,0) << "| " << guess[0] << " |" << getCol(correct,guess,1) << "| " << guess[1] << " |" << getCol(correct,guess,2) << "| " << guess[2] << " |" << getCol(correct,guess,3) << "| " << guess[3] << " |" << getCol(correct,guess,4) << "| " << guess[4] << " |" << endl;
        cout << getCol(correct,guess,0) << " ---  " << getCol(correct,guess,1) << "---  " << getCol(correct,guess,2) << "---  " << getCol(correct,guess,3) << "---  " << getCol(correct,guess,4) << "---  " << endl << RESET;
    }
}

void addToStats(string word, int numTries) {
    ofstream file;
    file.open("stats.txt", ios::app);
    if (file.is_open()) {
        file << numTries << " " << word << endl;
        file.close();
    }
}

void clearStatus(){
    ofstream status;
    status.open("../keyboard/status.txt", ios::out);
    
    if (status.is_open()) status.close();
    else {
        cout << CLEAR_TERMINAL << "Error opening keyboard status.txt";
        return;
    }
}

void wordle(string setCorrect = "") {
    // reset the keyboard status
    ofstream status;
    status.open("../keyboard/status.txt", ios::out);
    
    if (status.is_open()) {
        for(int i=0;i<26;i++) status << RESET << endl;
        status.close();
    } else {
        cout << CLEAR_TERMINAL << "Error opening keyboard status.txt";
        return;
    }

    // status is set up:
    // [letter] [letter's ANSI color]
    

    // set up words
    vector<string> guesses;
    int attemptNum = 1;

    // add all words to vector
    ifstream words;
    words.open("words.txt", ios::in);
    string line;
    vector<string> correctWords;
    if (words.is_open()) {
        while(getline(words, line)){
            correctWords.push_back(line);
        }
        words.close();
    } else {cout << "Error opening words.txt" << endl; return;}
    // set 'correct' to a random word in vector
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, correctWords.size() - 1);
    string correct;
    if (setCorrect == "") correct = correctWords[dis(gen)];
    else correct = setCorrect;

    while (attemptNum <= 6) {
        // clear terminal and output guesses
        cout << CLEAR_TERMINAL;
        outputWords(guesses, correct);
        
        // get a valid guess
        string inputtedGuess;
        do {
            cout << "Enter Guess: ";
            getline(cin, inputtedGuess);
        } while (!validWord("allowed.txt", inputtedGuess) && !validWord("words.txt", inputtedGuess));
        
        guesses.push_back(inputtedGuess);
        if(inputtedGuess == correct) {
            cout << CLEAR_TERMINAL;
            outputWords(guesses, correct);
            cout << "\nSplendid!\n\nPress [enter] to continue";
            addToStats(correct,attemptNum);
            cin.ignore();
            clearStatus();
            return;
        }
        
        attemptNum++;
    }
    cout << CLEAR_TERMINAL;
    outputWords(guesses, correct);
    cout << "\n\nThe word was: " << correct << "\nBetter luck next time!\n\nPress [enter] to continue";
    addToStats(correct,7);
    cin.ignore();
    clearStatus();
    return;
}

#endif