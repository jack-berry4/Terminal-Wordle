#ifndef KEYBOARD
#define KEYBOARD

#define CLEAR_TERMINAL "\033[2J\033[1;1H"
#define RESET "\033[0m"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void outputKeyboard(vector<string> colors){
    cout << CLEAR_TERMINAL;
    if (colors.size() == 0) {cout << "Waiting for Wordle Game round to start" << endl; return;}
    vector<char> keyTop{'q','w','e','r','t','y','u','i','o','p'};
    vector<char> keyMid{'a','s','d','f','g','h','j','k','l'};
    vector<char> keyBot{'z','x','c','v','b','n','m'};
    char letter;
    string color;
    for(int round=0;round<3;round++){
        for (int i=0; i<keyTop.size();i++){
            letter = keyTop[i];
            color = colors[letter-'a'];
            if(round==0||round==2) cout << color << " --- ";
            if(round==1) cout << color << "| "<<letter<<" |";
        }
        cout << endl;
    }
    for(int round=0;round<3;round++){
        cout << "  ";
        for (int i=0; i<keyMid.size();i++){
            letter = keyMid[i];
            color = colors[letter-'a'];
            if(round==0||round==2) cout << color << " --- ";
            if(round==1) cout << color << "| "<<letter<<" |";
        }
        cout << endl;
    }
    for(int round=0;round<3;round++){
        cout << "       ";
        for (int i=0; i<keyBot.size();i++){
            letter = keyBot[i];
            color = colors[letter-'a'];
            if(round==0||round==2) cout << color << " --- ";
            if(round==1) cout << color << "| "<<letter<<" |";
        }
        cout << RESET << endl;
    }
}

void keyboard() {
    vector<string> colors;
    string color;
    ifstream status;

    status.open("status.txt", ios::in);
    if (status.is_open()) {
        while(status >> color){
            colors.push_back(color);
        }
        status.close();
    } else {cout << "Error opening status.txt" << endl; return;}

    outputKeyboard(colors);

    while (true){
        vector<string> tempColors;
        status.open("status.txt", ios::in);
        if (status.is_open()) {
            while(status >> color){
                tempColors.push_back(color);
            }
            status.close();
        } else {cout << "Error opening status.txt" << endl; return;}

        if (!(tempColors == colors)){ 
            colors = tempColors;
            outputKeyboard(colors);
        }
    }

}

#endif