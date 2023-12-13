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
#include "helpers.hpp"


using namespace std;

struct coordinates{
    int x;
    int y;
};

struct solution{
    int row;
    int col;
};

bool equalArrays(vector<vector<int>> arr,int idx1, int idx2){
    if(arr[idx1].size() != arr[idx2].size()){
        return false;
    }
    else{
        for(int i=0;i<arr[(size_t)idx1].size();i++){
            if (arr[idx1][i] != arr[idx2][i]){
                return false;
            }
        }
        return true;
    }
}

bool offByone(vector<vector<int>> arr,int idx1, int idx2){
    if (abs((int)arr[idx1].size()-(int)arr[idx2].size()) != 1){
        return false;
    }

    else{
        int i = 0;
        int j = 0;
        bool checked = false;
        while(i<arr[idx1].size() && j<arr[idx2].size()){
            if (arr[idx1][i]!=arr[idx2][j] && !checked){
                checked = true;
                if(arr[idx1][i] > arr[idx2][j]){
                    j++;
                }

                else if(arr[idx1][i] < arr[idx2][j]){
                    i++;
                }
            }
            
            else if (arr[idx1][i]!=arr[idx2][j] && checked){
                return false;
            }

            else{
                i++;
                j++;
            }
        }
        if (i >= (int)arr[idx1].size()-1 && j>=(int)arr[idx2].size()-1){
            return true;
        }
        else{
            return false;
        }
    }
}

bool findIfMirror2(vector<vector<int>> arr, int idx1, int idx2, bool checked){
    while(checked){
        while(idx1>=0 && idx2 < arr.size()){
            if(offByone(arr,idx1,idx2)){
                checked = false;
                break;
            }
            else if(equalArrays(arr,idx1,idx2)){
                idx1--;
                idx2++;
            }
            else{
                return false;
            }
        }
        if (checked){
            return false;
        }
    }
    idx1--;
    idx2++;
    while(!checked){
        while(idx1>=0 && idx2 < arr.size()){
            if (!equalArrays(arr,idx1,idx2)){
                return false;
            }
            else{
                idx1--;
                idx2++;
            }
        }
        return true;
    }    
    return true;
}

bool findIfMirror(vector<vector<int>> arr, int idx1, int idx2){
    while(idx1>=0 && idx2 < arr.size()){
        if (!equalArrays(arr,idx1,idx2)){
            return false;
        }
        else{
            idx1--;
            idx2++;
        }
    }
    return true;
}

int handleArr2(vector<vector<int>> arr){
    int idx_1 = 0;
    int idx_2 = 1;

    vector<int> possible_lists;
    vector<bool> offOne;

    while(idx_2 < arr.size()){
        if(offByone(arr,idx_1,idx_2)){
            possible_lists.push_back(idx_1);
            offOne.push_back(false);
        }
        else if (equalArrays(arr,idx_1,idx_2)){
            possible_lists.push_back(idx_1);
            offOne.push_back(true);
        }
        idx_1++;
        idx_2++;
    }    

    if (possible_lists.empty()){
        return 0;
    }
    else{
        for(int i = 0;i<possible_lists.size();i++){
            if (findIfMirror2(arr,possible_lists[i],possible_lists[i]+1,offOne[i])){
                return possible_lists[i]+1;
            }
        }
    }        
    return 0;
}

int handleArr(vector<vector<int>> arr){
    int idx_1 = 0;
    int idx_2 = 1;

    vector<int> possible_lists;

    while(idx_2 < arr.size()){
        if(equalArrays(arr,idx_1,idx_2)){
            possible_lists.push_back(idx_1);
        }
        idx_1++;
        idx_2++;
    }    

    if (possible_lists.empty()){
        return 0;
    }
    else{
        for(int i = 0;i<possible_lists.size();i++){
            if (findIfMirror(arr,possible_lists[i],possible_lists[i]+1)){
                return possible_lists[i]+1;
            }
        }
    }        
    return 0;
}

unsigned long long handleGrip2(vector<coordinates> cords){
    vector<vector<int>> rows(cords.back().x);
    vector<vector<int>> cols(cords.back().y);

    for (int i = 0;i < cords.size()-1; i++){
        rows[cords[i].x].push_back(cords[i].y);
        cols[cords[i].y].push_back(cords[i].x);
    }

    int r = handleArr2(rows);
    int c = handleArr2(cols);
    return 100*r + c;
    
}


unsigned long long handleGrip(vector<coordinates> cords){
    vector<vector<int>> rows(cords.back().x);
    vector<vector<int>> cols(cords.back().y);

    for (int i = 0;i < cords.size()-1; i++){
        rows[cords[i].x].push_back(cords[i].y);
        cols[cords[i].y].push_back(cords[i].x);
    }

    int r = handleArr(rows);
    int c = handleArr(cols);
    return 100*r + c;
    
}
int main(){
    vector<string> lines = fileSplitLines("day13.txt");
    vector<vector<coordinates>> total_asterisks;

    vector<coordinates> pattern;
    total_asterisks.push_back(pattern);
    
    int curr_grid = 0;
    int curr_row = 0;
    for (int i = 0;i<lines.size();i++){
        if (lines[i].empty()){
            total_asterisks[curr_grid].push_back({curr_row,(int)lines[i-1].size()});
            vector<coordinates> pattern;
            total_asterisks.push_back(pattern);
            curr_row = 0;
            curr_grid++;
        }
        else{
            for (int j = 0;j<lines[i].size();j++){
                if(lines[i][j]=='#'){
                    total_asterisks[curr_grid].push_back({curr_row,j});
                }
            }
            curr_row++;
        }
    }
    total_asterisks[curr_grid].push_back({curr_row,(int)lines.back().size()});

    unsigned long long sum = 0;
    for (int i = 0;i<total_asterisks.size();i++){
        sum += handleGrip(total_asterisks[i]);
    }

    cout << "Part 1) " << sum << endl;

    //terrible implementation needs rewrite
    sum = 0;
    for (int i = 0;i<total_asterisks.size();i++){
        sum += handleGrip2(total_asterisks[i]);
    }
    
    cout << "Part 2) " << sum << endl;
    return 0;
}