#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef enum Color { r, g, b } color_t;
class Game{
    public:
        int red;
        int green;
        int blue;
        int idx;

        Game(int index){
            red = 0;
            green = 0;
            blue = 0;
            idx = index;
        }

        int calc(){
            return red*green*blue;
        }
};

void handleGame(string line,Game& gm){
    int amount = -1;
    for (int i=0;i<line.size();i++){
        if (line[i]>='0' && line[i]<='9'){
            if (line[i+1]>='0' && line[i+1]<='9'){
                amount = (line[i]-'0') * 10 + (line[i+1]-'0');
            }
            else if(line[i-1]>='0' && line[i-1]<='9'){
                continue;
            }
            else{
                amount = line[i] - '0';
            }
        }

        else if(line[i] == 'b'){
            if (amount > gm.blue){
                gm.blue = amount;
            }
        }
        else if(line[i] == 'g'){
            if (amount > gm.green){
                gm.green = amount;
            }
        }
        else if(line[i] == 'r' && line[i-1] != 'g'){
            if (amount > gm.red){
                gm.red = amount;
            }
        }
    }
}

int main() {
    auto n_sum = 0;
    auto cnt = 0;
    string line;
    string game;
    ifstream file("day2.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            cnt++;
            auto i = line.find(':') + 1;
            Game gm(cnt);
            while(line.find(';',i)!=string::npos){
                auto cut = line.find(';',i);
                game = line.substr(i,cut-i);
                handleGame(game,gm);
                i = cut+1;
            }
            game = line.substr(i);
            handleGame(game,gm);
            

            n_sum += gm.calc();
           
        }
        file.close();
    }
    cout << "Sum " << n_sum << endl;
}