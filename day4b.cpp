#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include <map>
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

int calculateWs(vector<int> winning, vector<int> played, map<int,int>& lottery,int card,int max_game){
    int ws = 0;
    for (int p: played){
        for (int w: winning){
            if (p == w){
                ws += 1;
            }
        }
    }
    int amount = lottery[card];
    
    int i = card + 1;
    while(ws-->0 && i < max_game){
        lottery[i++] += amount;
    }

    return amount;
}

int main(){
    vector<string> lines = fileSplitLines("day4.txt");
    int game = 0;
    int sum = 0;
    map<int, int> scratches;
    for (auto i = 1; i<=lines.size(); i++){
        scratches[i] = 1;
    }

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

        sum += calculateWs(winning_c,playing_c,scratches,game,lines.size()+1);
                
    }
    cout << "Sum: " << sum << endl;
    return 0;
}