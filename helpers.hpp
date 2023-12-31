#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

vector<string> fileSplitLines(string filename){
    vector<string> lines;
    string line;
    ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

vector<string> splitAtEvery(string line,char c){
    vector<string> lines;
    string sub_string;
    size_t i = 0;
          
    while(line.find(c,i)!=string::npos){
        auto cut = line.find(c,i);
        sub_string = line.substr(i,cut-i);
        lines.push_back(sub_string);
        i = cut+1;
    }
    if (i!=line.size()){
        sub_string = line.substr(i);
        lines.push_back(sub_string);
    }
    
    return lines;
}

template <typename T>
void print2dArray(vector<vector<T>> arr, string seperator = "\0"){
    for (size_t i = 0; i < arr.size(); i++){
        for (size_t j = 0; j < arr[i].size(); j++){
            cout << arr[i][j] ;
            if (j != arr[i].size() - 1){
                cout << seperator;
            }
        }
        cout <<endl;
    }
}

#endif