#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include "helpers.hpp"


using namespace std;

int main(){
    vector<string> lines = fileSplitLines("day6.txt");
    vector<int> times;
    vector<int> distances;
    string text;
    int n;

    stringstream ss(lines[0]);
    ss >> text;
    ss.ignore(1,':');
    while (ss >> n){
        times.push_back(n);
    }

    stringstream ss2(lines[1]);
    ss2 >> text;
    ss2.ignore(1,':');
    while (ss2 >> n){
        distances.push_back(n);
    }

    int solution = 1;

    for(int i=0;i<times.size();i++){
        int Tconst = times[i];
        int cnt = 0;
        for (int v = 0 ; v <= Tconst; v++){
            int t = Tconst - v;
            if (v*t>distances[i]){
                cnt += 1;
            }
        }
        solution *= cnt;
    }

    cout << "Part 1: " << solution << endl;

    unsigned long long int T_max =  (unsigned long long int)47847467;
    unsigned long long int d_max = (unsigned long long int)207139412091014;
    
    int cnt = 0;
    for(unsigned long long int v=0;v<=T_max;v++){
        unsigned long long int t = T_max - v;
        if (v*t>d_max){
            cnt += 1;
        }

    }
    cout << "Part 2: " << cnt << endl;
    return 0;
    
}
