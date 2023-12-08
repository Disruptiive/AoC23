#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "helpers.hpp"

using namespace std;

int main(){
    auto lines = splitAtEvery("beep;bop;fg",';');
    for (int i = 0;i<lines.size();i++){
        cout << lines[i] << endl;
    }
    return 0;
}