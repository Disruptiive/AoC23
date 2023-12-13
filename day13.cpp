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

int main(){
    vector<string> lines = fileSplitLines("day13.txt");
    vector<vector<string>> grids;
    vector<string> g;
    grids.push_back(g);
    int curr_grid = 0;
    for (int i=0;i<lines.size();i++){
        if (lines[i].empty()){
            curr_grid++;
            vector<string> g;
            grids.push_back(g);
        }
        else{
            grids[curr_grid].push_back(lines[i]);
        }
    }

    for (int i=0;i<grids[5].size();i++){
        cout << grids[5][i] <<endl;
    }
    return 0;
}