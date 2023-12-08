#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include "helpers.hpp"

using namespace std;


typedef enum{
    Dot,Symbol,Number
} chars_t;

class Character{
    public:
        chars_t type;
        int n;
        bool parted;
        Character(chars_t type, int n): type(type),n(n),parted(false) {};
};

int checkAndForm(vector<vector<Character>> &board, int i, int j){
    int n = 0;
    int k = 0;

    if (board[i][j].parted){
        return 0;
    }
    else{
        
        while( ((j+1) < board[0].size()) && board[i][j+1].type == Number){
            j = j + 1;
        }
        while( j >= 0 && board[i][j].type == Number){
            board[i][j].parted = true;
            n += board[i][j].n * pow(10,k++);
            j = j - 1;
        }
    }
    if (n > 0){
        cout << "Part number at i " <<i<< " ,j " << j << " : " << n <<endl;
    }
    return n;
}

bool checkAround(vector<vector<Character>> board, int i, int j, int n, int m){
    if (i>0){
        if (board[i-1][j].type == Symbol){
            return true;
        }
    }
    if (i>0 && j > 0){
        if (board[i-1][j-1].type == Symbol){
            return true;
        }
    }
    if (j > 0){
        if (board[i][j-1].type == Symbol){
            return true;
        }
    }
    if ((i+1)<n && j > 0){
        if (board[i+1][j-1].type == Symbol){
            return true;
        }
    }

    if ((i+1)<n){
        if (board[i+1][j].type == Symbol){
            return true;
        }
    }

    if ((i+1)<n && (j+1) < m){
        if (board[i+1][j+1].type == Symbol){
            return true;
        }
    }
    if ((j+1) < m){
        if (board[i][j+1].type == Symbol){
            return true;
        }
    }

    if (i>0 && (j+1) < m){
        if (board[i-1][j+1].type == Symbol){
            return true;
        }
    }
    return false;
}
bool isNumberPart(vector<vector<Character>> board, int i, int j){
    if (board[i][j].parted){
        return false;
    }

    Character curr_symbol = board[i][j];
    while(curr_symbol.type == Number){
        if (checkAround(board,i,j,board.size(),board[0].size())){
            return true;
        }
        else{
            if ((j+1)<board[0].size()){
                j = j+1;
                curr_symbol = board[i][j];
            }
            else{
                return false;
            }
        }
    }
    return false;

}

int main(){
    vector<vector<Character>> chars;
    string line;
    ifstream file("day3.txt");
    int sum = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            vector<Character> curr_line;
            for (int j = 0; j<line.size();j++){
                if (line[j] == '.'){
                    curr_line.push_back(Character{Dot,-1});
                }
                else if(line[j] >= '0' && line[j] <= '9'){
                    curr_line.push_back(Character{Number,(int)(line[j]-'0')});
                }
                else{
                    curr_line.push_back(Character{Symbol,-1});
                }
            }
            chars.push_back(curr_line);
        }
        file.close();
    }
    for (int i = 0; i<line.size();i++){
        for (int j = 0; j<line.size();j++){
            switch(chars[i][j].type){
                case Dot:
                    break;
                case Number:
                    if (isNumberPart(chars,i,j)){
                        sum += checkAndForm(chars,  i, j);
                    }
                    break;
                case Symbol:
                    break;
                default:
                    cout << 'WTFF' << endl;
                    break;
            }
        }
    }
    cout << "Sum: " << sum << endl;
    return 0;
}