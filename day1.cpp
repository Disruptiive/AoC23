#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> numbers = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

int main() {
    auto sum = 0;
    string line;
    ifstream file("day1.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            bool first = true;
            auto n_last = -1;
            for (char c : line) {
                if (c>='0' && c <= '9'){
                    if (first){
                        first = false;
                        int n = atoi(&c);
                        n_last = n;
                        sum+= 10*n;
                    }
                    else{
                        n_last = atoi(&c);
                    }
                }
            }
            sum+=n_last;       
        }
        file.close();
    }
    cout << "Part1 " << sum << endl;
    sum = 0;
    ifstream file2("day1.txt");
    if (file2.is_open()) {
        while (getline(file2, line)) {
            bool first = true;
            auto n_last = -1;
            for (int j = 0; j < line.size(); j++)  {
                if (line[j]>='0' && line[j] <= '9'){
                    if (first){
                        first = false;
                        int n = line[j]-'0';
                        n_last = n;
                        sum+= 10*n;
                    }
                    else{
                        n_last = line[j]-'0';
                    }
                }
                else{
                    for (int i=0;i<numbers.size();i++){

                        if (j+numbers[i].size()<=line.size()){
                            if(line.substr(j,numbers[i].size())==numbers[i]){
                                if (first){
                                    first = false;
                                    n_last = i;
                                    sum+= 10*i;
                                }
                                else{
                                    n_last = i;
                                }
                            }
                        }
                    }
                }
            }
            sum+=n_last;
        }
        file2.close();
    }
    cout << "Part2 " << sum << endl;
    return 0;
}