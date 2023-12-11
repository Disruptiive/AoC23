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

struct coordinates{
    int x;
    int y;
};

int calculateDistance(coordinates p1, coordinates p2, vector<int> empty_r, vector<int> empty_c,int empty_weight){
    int e_cnt = 0;
    for (int i = 0; i <empty_r.size(); i++){
        if ((p1.x < empty_r[i] && p2.x > empty_r[i]) || (p1.x > empty_r[i] && p2.x < empty_r[i])){
            e_cnt++;
        }
    }

    for (int i = 0; i <empty_c.size(); i++){
        if ((p1.y < empty_c[i] && p2.y > empty_c[i]) || (p1.y > empty_c[i] && p2.y < empty_c[i])){
            e_cnt++;
        }
    }
    return abs(p1.x-p2.x)+abs(p1.y-p2.y)+e_cnt*(empty_weight-1);
}


int main(){
    vector<string> lines = fileSplitLines("day11.txt");
    vector<vector<char>> grid;
    for (int i = 0; i < lines.size(); i++){
        stringstream ss(lines[i]);
        char c;
        vector<char> row;

        while(ss>>c){
            row.push_back(c);
        }
        grid.push_back(row);
    }

    vector<coordinates> cords;

    for(int i = 0; i <grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if (grid[i][j] == '#'){
                cords.push_back({i,j});
            }
        }
    }

    vector<int> empty_rows, empty_cols;
    bool empty;
    for (int i = 0; i <grid.size(); i++){
        empty = true;
        for(int j = 0; j < grid[i].size(); j++){
            if (grid[i][j] == '#'){
                empty = false;
            }
        }
        if (empty){
            empty_rows.push_back(i);
        }
    }

    for (int j = 0; j <grid[0].size(); j++){
        empty = true;
        for(int i = 0; i < grid.size(); i++){
            if (grid[i][j] == '#'){
                empty = false;
            }
        }
        if (empty){
            empty_cols.push_back(j);
        }
    }
    int weights[] = {1,1000000};

    for (int w = 0; w < size(weights); w++){
        unsigned long long total_d = 0;
        for(int i=0; i < cords.size(); i++){
            for(int j=i+1; j<cords.size();j++){
                if (i>j){
                    continue;
                }
                else{
                    total_d += calculateDistance(cords[i], cords[j], empty_rows, empty_cols, weights[w]);
                }
            }
        }

        cout << "Part " << w+1 << "): " << total_d << endl;
    }
        

    return 0;
}