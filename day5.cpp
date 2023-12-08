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
    vector<string> lines = fileSplitLines("day5.txt");
    vector<unsigned long int> availlable_seeds;

    stringstream ss(lines[0]);
    string text;
    unsigned long int n;
    ss >> text;
    ss.ignore(1,':');

    while (ss>>n){
        availlable_seeds.push_back(n);
    }

    vector<vector<vector<unsigned long int>>> map;
    int i=1;
    while (i<lines.size()){
        if (lines[i].empty()){
            i++;
            continue;
        }
        else if(lines[i].back() == ':'){
            vector<vector<unsigned long int>> part_of_map;
            i++;
            while (i<lines.size() && !lines[i].empty()){
                stringstream ss(lines[i++]);
                vector<unsigned long int> row;
                unsigned long int n;
                while(ss>>n){
                    row.push_back(n);
                }
                part_of_map.push_back(row);
            }
            map.push_back(part_of_map);
        }
    }

    vector<unsigned long int> solutions;

    for(auto seed:availlable_seeds){
        auto curr_num = seed;
        for (const auto &part_map : map) {
            for (const auto &row : part_map) {
                if (curr_num >= row[1] && curr_num < row[1] + row[2]){
                    curr_num = row[0] + curr_num - row[1];
                    break;
                }
            }
        }
        solutions.push_back(curr_num);
    }

    auto solution = *min_element(solutions.begin(),solutions.end());

    cout << solution <<endl;
    for (unsigned long int i = 0; i<=solution;i++){
        if (i%1000000 == 0){
            cout << "Done: " << i <<endl;
        }
        auto curr_num = i;
        for (auto part_map = rbegin(map); part_map!=rend(map);++part_map){
            for (const auto &row : *part_map) {
                if (curr_num >= row[0] && curr_num < row[0] + row[2]){ 
                    curr_num = row[1] + curr_num - row[0];
                    break;
                }
            }
        }
        for (int j = 0; j<availlable_seeds.size();j+=2){
            if (curr_num>=availlable_seeds[j] && curr_num < availlable_seeds[j] + availlable_seeds[j+1]){
                cout << "Solution " << i <<endl;
                return 0;
            } 
        }
    }

    /*
    
    unsigned long int solution = ULONG_MAX;

    for(size_t i = 0; i < availlable_seeds.size();i += 2){
        auto seed = availlable_seeds[i];
        auto rg = availlable_seeds[i+1];
        for (unsigned long int r=0;r<rg;r++){
            auto curr_num = seed + r;
            for (const auto &part_map : map) {
                for (const auto &row : part_map) {
                    if (curr_num >= row[1] && curr_num < row[1] + row[2]){
                        curr_num = row[0] + curr_num - row[1];
                        break;
                    }
                }
            }
            if (solution > curr_num){
                solution = curr_num;
            }
        }
        cout << "Done one" <<endl;
    }
    cout << solution <<endl;
    
    */
    return 0;
}
