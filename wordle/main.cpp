#include <iostream>
#include "wordle.h"
#include "stats.h"

// Escape Code Definitions
#define CLEAR_TERMINAL "\033[2J\033[1;1H"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GRAY  "\033[90m"


using namespace std;

int main(int argc, char* argv[]) {
    

    while (true){
        cout << CLEAR_TERMINAL;
        cout << "=========================\n    WELCOME TO WORDLE\n=========================\n\n\n1. Play Wordle\n2. How to Play\n3. Statistics Summary\n4. Reset Statistics\n5. Exit\n\n\nSelect an option:\n";
        string selStr;
        getline(cin, selStr);
        int selection = stoi(selStr);

        cout << CLEAR_TERMINAL;

        switch (selection) {
        case 1:
            wordle();
            break;
        case 2:
            // How to play menu
            cout << "=============================================\n                 HOW TO PLAY\n=============================================\nGuess the Wordle in 6 tries.\n\n\nHOW TO PLAY:\n- Each guess must be a valid 5 letter word.\n- The color of the tiles will change to show\n  you how close your guess was to the word.\n\n " << GREEN << "---" << RESET << "  ---  ---  ---  ---\n" << GREEN << "| W |" << RESET << "| E || A || R || Y |\n " << GREEN << "---" << RESET << "  ---  ---  ---  ---\nW is in the word and in the correct spot.\n\n ---" << YELLOW << "  ---" << RESET << "  ---  ---  ---\n| P |" << YELLOW << "| I |" << RESET << "| L || L || S |\n ---" << YELLOW << "  ---" << RESET << "  ---  ---  ---\nI is in the word but in the wrong spot.\n\n ---  ---  ---" << GRAY << "  ---" << RESET << "  ---\n| V || A || G |" << GRAY << "| U |" << RESET << "| E |\n ---  ---  ---" << GRAY << "  ---" << RESET << "  ---\nU is not in the word in any spot.\n\n\nPress [enter] to continue";
            cin.ignore();   // wait for enter
            break;
        case 3:
            showStats();
            break;
        case 4:
            resetStats();
            showStats();
            break;
        case 5:
            return 0;
        default:
            cout << "Not a number from 1 to 5\n\nPress [enter] to continue";
            cin.ignore();   // wait for enter
            break;
        }
        
    }

    return 0;
}