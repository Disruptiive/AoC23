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

void cleanupParts(vector<vector<Character>> &board, int i, int j,int n, int m){
    if (i>0){
        board[i-1][j].parted = false;
        
    }
    if (i>0 && j > 0){
        board[i-1][j-1].parted = false;
    }
    if (j > 0){
        board[i][j-1].parted =false;
    }
    if ((i+1)<n && j > 0){
        board[i+1][j-1].parted = false;
    }

    if ((i+1)<n){
        board[i+1][j].parted = false;
    }

    if ((i+1)<n && (j+1) < m){
        board[i+1][j+1].parted = false;
    }

    if ((j+1) < m){
        board[i][j+1].parted = false;
    }

    if (i>0 && (j+1) < m){
        board[i-1][j+1].parted = false;
    }
}

int isGear(vector<vector<Character>> board, int i, int j, int n, int m){
    int cnt = 0;
    int d1 = -1;
    int d2 = -1;
    if (i>0){
        if (board[i-1][j].type == Number && board[i-1][j].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i-1, j);
            }
            else{
                d2 = checkAndForm(board, i-1, j);
            }
            cnt++;
        }
    }
    if (i>0 && j > 0){
        if (board[i-1][j-1].type == Number && board[i-1][j-1].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i-1, j-1);
            }
            else{
                d2 = checkAndForm(board, i-1, j-1);
            }
            cnt++;
        }
    }
    if (j > 0){
        if (board[i][j-1].type == Number && board[i][j-1].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i, j-1);
            }
            else{
                d2 = checkAndForm(board, i, j-1);
            }
            cnt++;
        }
    }
    if ((i+1)<n && j > 0){
        if (board[i+1][j-1].type == Number && board[i+1][j-1].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i+1, j-1);
            }
            else{
                d2 = checkAndForm(board, i+1, j-1);
            }
            cnt++;
        }
    }

    if ((i+1)<n){
        if (board[i+1][j].type == Number && board[i+1][j].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i+1, j);
            }
            else{
                d2 = checkAndForm(board, i+1, j);
            }
            cnt++;
        }
    }

    if ((i+1)<n && (j+1) < m){
        if (board[i+1][j+1].type == Number && board[i+1][j+1].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i+1, j+1);
            }
            else{
                d2 = checkAndForm(board, i+1, j+1);
            }
            cnt++;
        }
    }
    if ((j+1) < m){
        if (board[i][j+1].type == Number && board[i][j+1].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i, j+1);
            }
            else{
                d2 = checkAndForm(board, i, j+1);
            }
            cnt++;
        }
    }

    if (i>0 && (j+1) < m){
        if (board[i-1][j+1].type == Number && board[i-1][j+1].parted == false){
            if (cnt == 0){
                d1 = checkAndForm(board, i-1, j+1);
            }
            else{
                d2 = checkAndForm(board, i-1, j+1);
            }
            cnt++;
        }
    }
    cleanupParts(board, i, j, n, m);
    if (cnt == 2){
        return d1 * d2;
    }
    else{
        return 0;
    }
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
                if (line[j] == '*'){
                    curr_line.push_back(Character{Symbol,-1});
                }
                else if(line[j] >= '0' && line[j] <= '9'){
                    curr_line.push_back(Character{Number,(int)(line[j]-'0')});
                }
                else{
                    curr_line.push_back(Character{Dot,-1});
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
                    break;
                case Symbol:
                    sum += isGear(chars,i,j,chars.size(),chars[0].size());
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