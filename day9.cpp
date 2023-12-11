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

bool isVectorZeros(vector<long> arr){
    for (size_t i = 0;i < arr.size(); i++){
        if (arr[i] != 0){
            return false;
        }
    }
    return true;
}

void calculateExtrapolated(vector<vector<long>> &vals){
    vector<long> new_vals;
    auto last_row = vals[vals.size()-1];
    for (size_t i = 1; i < last_row.size(); i++){
        new_vals.push_back(last_row[i]-last_row[i-1]);
    }
    vals.push_back(new_vals);
}

void calculateExtrapolatedBackwards(vector<vector<long>> &vals){
    vector<long> new_vals;
    auto last_row = vals[vals.size()-1];
    for (int i = 1; i < last_row.size(); i++){
        new_vals.insert(new_vals.begin(),last_row[i]-last_row[i-1]);
    }
    vals.push_back(new_vals);
}



int main(){
    vector<string> lines = fileSplitLines("day9.txt");
    vector<vector<long>> arrays;
    long n;
    for (size_t i = 0; i < lines.size(); i++){
        vector<long> row;
        stringstream ss(lines[i]);
        while (ss>>n){
            row.push_back(n);
        }
        arrays.push_back(row);
    }
    long long sum = 0;
    for (size_t i = 0; i < arrays.size(); i++){
        vector<vector<long>> extrapolated_vals;
        extrapolated_vals.push_back(arrays[i]);
        while(!isVectorZeros(extrapolated_vals[extrapolated_vals.size()-1])){
            calculateExtrapolated(extrapolated_vals);
        }
        
        for (int j = extrapolated_vals.size()-2;j > -1; j--){
            auto last_idx_prev = extrapolated_vals[j].size() - 1;
            auto last_idx_next = extrapolated_vals[j+1].size() - 1;
            long next_val = extrapolated_vals[j][last_idx_prev] + extrapolated_vals[j+1][last_idx_next];
            if (j == 0)
                sum += next_val;
            extrapolated_vals[j].push_back(next_val);
        }
    }
    cout << "1) Sum: " <<sum <<endl;

    sum = 0;
    for (size_t i = 0; i < arrays.size(); i++){
        vector<vector<long>> extrapolated_vals2;
        extrapolated_vals2.push_back(arrays[i]);
        while(!isVectorZeros(extrapolated_vals2[extrapolated_vals2.size()-1])){
            calculateExtrapolated(extrapolated_vals2);
        }
        
        for (int j = extrapolated_vals2.size()-2;j > -1; j--){
            long next_val = extrapolated_vals2[j][0] - extrapolated_vals2[j+1][0];
            if (j == 0)
                sum += next_val;
            extrapolated_vals2[j].insert(extrapolated_vals2[j].begin(),next_val);
        }
    }
    cout << "2) Sum: " <<sum <<endl;
    return 0;
}