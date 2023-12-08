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
        bool valid;

        Game(int r, int g, int b, int index){
            red = r;
            green = g;
            blue = b;
            valid = true;
            idx = index;
        }
        void remove(color_t color, int& amount){
            switch (color)
            {
            case r:
                red -= amount;
                break;
            case g:
                green -= amount;
            case b:
                blue -= amount;
            default:
                break;
            }
        }
        /*
        bool isValid(){
            cout << "Game " << idx << " red: " <<red <<" green: " << green << " blue: " << blue << endl; 
            if (red >= 0 && green >= 0 && blue >= 0){
                return true;
            }
            else{
                return false;
            }
        }
        */
        bool isValid(){
            if (valid){
                return true;
            }
            else{
                return false;
            }
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
        /*
        else if(line[i] == 'b'){
            gm.remove(b,amount);
        }
        else if(line[i] == 'g'){
            gm.remove(g,amount);
        }
        else if(line[i] == 'r' && line[i-1] != 'g'){
            gm.remove(r,amount);
        }
        */
        else if(line[i] == 'b'){
            if (amount > gm.blue){
                gm.valid = false;
            }
        }
        else if(line[i] == 'g'){
            if (amount > gm.green){
                gm.valid = false;
            }
        }
        else if(line[i] == 'r' && line[i-1] != 'g'){
            if (amount > gm.red){
                gm.valid = false;
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
            Game gm(12,13,14,cnt);
            while(line.find(';',i)!=string::npos){
                auto cut = line.find(';',i);
                game = line.substr(i,cut-i);
                handleGame(game,gm);
                i = cut+1;
            }
            game = line.substr(i);
            handleGame(game,gm);
            
            if (gm.isValid()){
                n_sum += cnt;
            }
        }
        file.close();
    }
    cout << "Sum " << n_sum << endl;
}