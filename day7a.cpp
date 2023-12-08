#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include "helpers.hpp"


using namespace std;

enum hand_t{
    HighCard,
    OP,
    TP,
    ThreeOfKind,
    FH,
    FourOfKind,
    FiveOfKind,
};


int charValue(char c){
    int v;
    if (c>='2' && c<='9'){
        v = c-'0';
    }
    else if (c =='T'){
        v=10;
    }
    else if (c =='J'){
        v=11;
    }
    else if (c =='Q'){
        v=12;
    }
    else if (c =='K'){
        v=13;
    }
    else if (c =='A'){
        v=14;
    }
    else{
        cout <<"the fuck"<< endl;
    }
    return v;
}

hand_t findHandType(string hand){
    hand_t tp;
    map<char, int> mp;
    for (char c:hand){
        if (mp.count(c)>0){
            mp[c]+=1;
        }
        else{
            mp[c]=1;
        }
    }
    auto pr = max_element(mp.begin(), mp.end(), [](const auto &x, const auto &y) {
                    return x.second < y.second;
                });
    switch (mp.size())
    {
    case 1:
        tp = FiveOfKind;
        break;
    case 2:
        if(pr->second == 4){
            tp = FourOfKind;
          //  cout << hand << " is four of kind"<<endl; 
        }
        else{
            tp = FH;
            //cout << hand << " is full house"<<endl; 
        }
        break;
    case 3:
        if(pr->second == 3){
            tp = ThreeOfKind;
            //cout << hand << " is three of kind"<<endl; 
        }
        else{
            tp = TP;
        //    cout << hand << " is two pair"<<endl; 
        }
        break;
    case 4:
        tp = OP;
        //cout << hand << " is one pair"<<endl; 
        break;
    case 5:
        tp = HighCard;
        //cout << hand << " is high card"<<endl; 
    default:
        break;
    }
    return tp;
}


class Hand{
    public:
        hand_t hand_type;
        int first;
        int second;
        int third;
        int fourth;
        int fifth;
        int value;
        string hd;
    Hand(string hand, int v){
        first = charValue(hand.at(0));
        second = charValue(hand.at(1));
        third = charValue(hand.at(2));
        fourth = charValue(hand.at(3));
        fifth = charValue(hand.at(4));
        hand_type = findHandType(hand);
        value = v;
        hd = hand;
    }

    int compareWith(Hand h2){
        if (hand_type > h2.hand_type){
            return 0;
        }
        else if (hand_type < h2.hand_type){
            return 1;
        }
        else{
            if (first > h2.first){
                return 0;
            }
            else if (first < h2.first){
                return 1;
            }
            else{
                if (second > h2.second){
                return 0;
                }
                else if (second < h2.second){
                    return 1;
                }
                else{
                    if (third > h2.third){
                        return 0;
                    }
                    else if (third < h2.third){
                        return 1;
                    }
                    else{
                        if (fourth > h2.fourth){
                            return 0;
                        }
                        else if (fourth < h2.fourth){
                            return 1;
                        }
                        else{
                            if (fifth > h2.fifth){
                                return 0;
                            }
                            else if (fifth < h2.fifth){
                                return 1;
                            }
                            else{
                                return 2;
                            }
                        }
                    }
                }
            }
        }
    }
};



int main(){
    vector<string> lines = fileSplitLines("day7.txt");
    vector<Hand> hands;
    for (size_t i = 0;i<lines.size();i++){
        string text;
        int v;
        stringstream ss(lines[i]);
        ss>>text;
        ss>>v;
        hands.push_back(Hand(text,v));
    } 

    for (size_t i = 0;i<hands.size();i++){
        for (size_t j = i+1;j<hands.size();j++){
            if (hands[i].compareWith(hands[j]) ==  0){
                //cout << hands[i].hd << " stronger than " << hands[j].hd <<endl;
                swap(hands[i],hands[j]);
            }
        }
    }
    unsigned long long solution = 0;
    for (size_t i = 0;i<hands.size();i++){
        solution += (i+1) * hands[i].value;
    }    
    cout << "Part 1: " << solution << endl;

    return 0;
}