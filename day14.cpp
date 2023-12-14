#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>
#include <unordered_set>
#include "helpers.hpp"


using namespace std;

enum symbols{
    Rock,
    Empty,
    Immovable,
};

struct coordinates{
    int x;
    int y;
};

void moveNorth(vector<vector<symbols>> &arr, int i, int j){
    int row = i;
    row--;
    if ((row>=0) && arr[row][j]!=Empty){
        return;
    }
    
    while((row>=0) && arr[row][j]==Empty){ 
        row--;
    }


    row++;
    if(row != i){
        arr[row][j] = Rock;
        arr[i][j] = Empty;
    }   
    
}

void moveWest(vector<vector<symbols>> &arr, int i, int j){
    int col = j;
    col--;
    if ((col>=0) && arr[i][col]!=Empty){
        return;
    }
    
    while((col>=0) && arr[i][col]==Empty){ 
        col--;
    }


    col++;
    if(col != j){
        arr[i][col] = Rock;
        arr[i][j] = Empty;
    }   
}

void moveSouth(vector<vector<symbols>> &arr, int i, int j){
    int row = i;
    row++;
    if ((row<arr.size()) && arr[row][j]!=Empty){
        return;
    }
    
    while((row<arr.size()) && arr[row][j]==Empty){ 
        row++;
    }


    row--;
    if(row != i){
        arr[row][j] = Rock;
        arr[i][j] = Empty;
    }   
    
}

void moveEast(vector<vector<symbols>> &arr, int i, int j){
    int col = j;
    col++;
    if ((col<arr[i].size()) && arr[i][col]!=Empty){
        return;
    }
    
    while((col<arr[i].size())  && arr[i][col]==Empty){ 
        col++;
    }


    col--;
    if(col != j){
        arr[i][col] = Rock;
        arr[i][j] = Empty;
    }   
}

void processGrid2(vector<vector<symbols>> &arr){
    for(int i=0;i<arr.size();i++){
        for(int j=0;j<arr[i].size();j++){
            if(arr[i][j] == Rock){
                moveNorth(arr,i,j);
            }
        }
    }

    for(int i=0;i<arr.size();i++){
        for(int j=0;j<arr[i].size();j++){
            if(arr[i][j] == Rock){
                moveWest(arr,i,j);
            }
        }
    }

    for(int i=(int)arr.size()-1;i>=0;i--){
        for(int j=0;j<arr[i].size();j++){
            if(arr[i][j] == Rock){
                moveSouth(arr,i,j);
            }
        }
    }
    
    for(int i=0;i<arr.size();i++){
        for(int j=(int)arr[i].size()-1;j>=0;j--){
            if(arr[i][j] == Rock){
                moveEast(arr,i,j);
            }
        }
    }
    
}

void processGrid(vector<vector<symbols>> &arr){
    for(int i=1;i<arr.size();i++){
        for(int j=0;j<arr[i].size();j++){
            if(arr[i][j] == Rock){
                moveNorth(arr,i,j);
            }
        }
    }
}



bool didTheyStopReapeating(int idx1,int idx2, vector<int>arr){
    while(idx1<arr.size() && idx2<arr.size()){
        if(arr[idx1]!=arr[idx2]){
            return false;
        }
        idx1++;
        idx2++;
    }
    return true;
}

int main(){
    vector<string> lines = fileSplitLines("day14.txt");
    vector<vector<symbols>> grid;
    for(int i=0;i<lines.size();i++){
        vector<symbols> row;
        for(char c:lines[i]){
            if(c == '.'){
                row.push_back(Empty);
            }
            else if(c == '#'){
                row.push_back(Immovable);
            }
            else if(c == 'O'){
                row.push_back(Rock);
            }
        }
        grid.push_back(row);
    }
    int sum = 0;
    processGrid(grid);
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            if (grid[i][j] == Rock){
                sum += (int)grid.size() - i;
            }
        }
    }

    cout << "Part 1) " << sum << endl ;

    grid.clear();
    for(int i=0;i<lines.size();i++){
        vector<symbols> row;
        for(char c:lines[i]){
            if(c == '.'){
                row.push_back(Empty);
            }
            else if(c == '#'){
                row.push_back(Immovable);
            }
            else if(c == 'O'){
                row.push_back(Rock);
            }
        }
        grid.push_back(row);
    }
    vector<int> sums;
    
    for (int i = 0;i<700;i++){
        processGrid2(grid);
        sum = 0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[i].size();j++){
                if (grid[i][j] == Rock){
                    sum += (int)grid.size() - i;
                }
            }
        }
        sums.push_back(sum);
    }
    int start_repeating= -1;
    int stop_repeating= -1;
    bool found = false;
    for(int i = 0;i<sums.size();i++){
        for(int j = i+1;j<sums.size();j++){
            if(didTheyStopReapeating(i,j,sums)){
                if (start_repeating-stop_repeating<100){
                    start_repeating = i;
                    stop_repeating = j;
                    found = true;
                }
                
            }
            if (found){
                break;
            }
                
        }
        if (found){
            break;
        }
    }

    int n = 1000000000;

    int idx = (n-start_repeating)%(stop_repeating-start_repeating)+start_repeating-1;

    cout << "Part 2:) " << sums[idx]  << endl;
    
    
    return 0;
}