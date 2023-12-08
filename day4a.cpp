#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include "helpers.hpp"
#include <regex>

using namespace std;

vector<int> make_int_vec(vector<string> v){
    vector<int> nv;
    for (string s:v){
        if (!s.empty()){
            nv.push_back(stoi(s));
        }
    }
    return nv;
}

int calculateWs(vector<int> winning, vector<int> played){
    int ws = 0;
    int returns = 0;
    for (int p: played){
        for (int w: winning){
            if (p == w){
                ws += 1;
            }
        }
    }

    if (ws-- > 0){
        returns = 1;
        while(ws-->0){
            returns *= 2;
        }
        return returns;
    }
    else {
        return returns;
    }
}

int main(){
    vector<string> lines = fileSplitLines("day4.txt");
    int game = 0;
    int sum = 0;
    for (string line:lines){
        
        game++;
        string cards = splitAtEvery(line,':')[1].substr(1);
        vector<string> cards_vec = splitAtEvery(cards,'|');
        string winning_cards = cards_vec[0];
        string played_cards = cards_vec[1].substr(1);
        
        vector<string> winning_cards_vec = splitAtEvery(winning_cards,' ');
        vector<string> playing_cards_vec = splitAtEvery(played_cards,' ');
        
        vector<int> winning_c = make_int_vec(winning_cards_vec);
        vector<int> playing_c = make_int_vec(playing_cards_vec);

        sum += calculateWs(winning_c,playing_c);
        /*
        cout << "Game: " << game <<endl;
        cout << "Won: " << endl;
        for (int c: winning_c){
            cout << c <<endl;
        }
        cout << "Played: " << endl;
        for (int c: playing_c){
            cout << c << endl;
        }
        */
        
        
    }
    cout << "Sum: " << sum << endl;
    return 0;
}