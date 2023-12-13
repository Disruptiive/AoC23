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

struct coords {
    int x;
    int y;
};

enum symbols{
    vertical,
    horizon,
    northeast,
    northwest,
    southwest,
    southeast,
    ground,
    starting,
};

enum dir_x{
    Right,
    Left,
};

enum dir_y{
    Up,
    Down,
};

class Pipe{
    public:
        char symbol;
        coords coordinates;
        int distance;
        Pipe* prev;
        Pipe* next;

        Pipe(char symbs, int i, int j, Pipe *starting){
            distance = 0;
            symbol = symbs;
            coordinates = coords{i,j};
            prev = nullptr;
            next = nullptr;
        }
};

void findNext(Pipe *curr, vector<vector<char>> arr, Pipe* root, int &way, int &distance){
    //cout << "Im currently in: " << curr->coordinates.x << " , " << curr->coordinates.y << " Char: " << arr[curr->coordinates.x][curr->coordinates.y] << endl;

    if (arr[curr->coordinates.x][curr->coordinates.y] == '|'){
        if(curr->prev->coordinates.x == curr->coordinates.x+1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x-1][curr->coordinates.y],curr->coordinates.x-1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }

        else if (curr->prev->coordinates.x == curr->coordinates.x-1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x+1][curr->coordinates.y],curr->coordinates.x+1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else{
            cout << "It cant be |" <<endl;
        }
    }

    else if (arr[curr->coordinates.x][curr->coordinates.y] == '-'){
        if(curr->prev->coordinates.y == curr->coordinates.y+1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y-1],curr->coordinates.x,curr->coordinates.y-1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }

        else if (curr->prev->coordinates.y == curr->coordinates.y-1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y+1],curr->coordinates.x,curr->coordinates.y+1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else{
            cout << "It cant be -" <<endl;
        }
    }

    else if(arr[curr->coordinates.x][curr->coordinates.y] == 'L'){
        if((curr->coordinates.x - 1 >= 0) && curr->prev->coordinates.x == curr->coordinates.x-1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y+1],curr->coordinates.x,curr->coordinates.y+1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else if((curr->coordinates.y + 1 < arr[0].size()) && curr->prev->coordinates.y == curr->coordinates.y+1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x-1][curr->coordinates.y],curr->coordinates.x-1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else{
            cout << "It cant be L" <<endl;
        }
        
    }

    else if(arr[curr->coordinates.x][curr->coordinates.y] == 'J'){
        if((curr->coordinates.x - 1 >= 0) && curr->prev->coordinates.x == curr->coordinates.x-1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y-1],curr->coordinates.x,curr->coordinates.y-1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else if((curr->coordinates.y - 1 >= 0) && curr->prev->coordinates.y == curr->coordinates.y-1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x-1][curr->coordinates.y],curr->coordinates.x-1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else{
            cout << "It cant be J" <<endl;
        }
    }

    else if(arr[curr->coordinates.x][curr->coordinates.y] == '7'){
        if((curr->coordinates.x + 1 < arr.size()) && curr->prev->coordinates.x == curr->coordinates.x+1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y-1],curr->coordinates.x,curr->coordinates.y-1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else if((curr->coordinates.y - 1 >= 0) && curr->prev->coordinates.y == curr->coordinates.y-1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x+1][curr->coordinates.y],curr->coordinates.x+1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else{
            cout << "It cant be 7" <<endl;
        }
    }

    else if(arr[curr->coordinates.x][curr->coordinates.y] == 'F'){
        if((curr->coordinates.x + 1 < arr.size()) && curr->prev->coordinates.x == curr->coordinates.x+1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y+1],curr->coordinates.x,curr->coordinates.y+1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else if((curr->coordinates.y + 1 < arr[0].size()) && curr->prev->coordinates.y == curr->coordinates.y+1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x+1][curr->coordinates.y],curr->coordinates.x+1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
        else{
            cout << "It cant be F" <<endl;
        }
    }

    else if(arr[curr->coordinates.x][curr->coordinates.y] == 'S' && curr == root){

        
        if(((curr->coordinates.x+1)>arr.size()) && arr[curr->coordinates.x+1][curr->coordinates.y] == '|' || arr[curr->coordinates.x+1][curr->coordinates.y] == 'L' || arr[curr->coordinates.x+1][curr->coordinates.y] == 'J' && way == 1){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x+1][curr->coordinates.y],curr->coordinates.x+1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }



        else if(((curr->coordinates.x-1)>=0) && arr[curr->coordinates.x-1][curr->coordinates.y] == '|' || arr[curr->coordinates.x-1][curr->coordinates.y] == '7' || arr[curr->coordinates.x-1][curr->coordinates.y] == 'F'  && way == 2){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x-1][curr->coordinates.y],curr->coordinates.x-1,curr->coordinates.y, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }
 


        else if(((curr->coordinates.y+1)>arr[0].size()) && arr[curr->coordinates.x][curr->coordinates.y+1] == '-' || arr[curr->coordinates.x][curr->coordinates.y+1] == '7' || arr[curr->coordinates.x][curr->coordinates.y+1] == 'J'  && way == 3){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y+1],curr->coordinates.x,curr->coordinates.y+1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }



        else if(((curr->coordinates.y-1)>=0) && arr[curr->coordinates.x][curr->coordinates.y-1] == '-' || arr[curr->coordinates.x][curr->coordinates.y-1] == 'L' || arr[curr->coordinates.x][curr->coordinates.y-1] == 'F'  && way == 4){
            Pipe *main_pipe = new Pipe(arr[curr->coordinates.x][curr->coordinates.y-1],curr->coordinates.x,curr->coordinates.y-1, root);
            curr->next = main_pipe;
            main_pipe->prev = curr;
        }       
    }

    else if(arr[curr->coordinates.x][curr->coordinates.y] == 'S' && curr != root){
        cout << "already done a circle" << endl;
    }

    else {
        cout << "how tf am i in here" << endl;
    }
}

int main(){
    vector<string> lines = fileSplitLines("day10.txt");
    vector<vector<char>> chars;
    char c;
    for(size_t i = 0; i < lines.size();i++){
        stringstream ss(lines[i]);
        vector<char> row;
        while (ss >> c){
            row.push_back(c);
        }
        chars.push_back(row);
    }

    coords starting_pos;

    for(size_t i = 0; i < chars.size();i++){
        for(size_t j = 0; j < chars[i].size();j++){
            if (chars[i][j] == 'S'){
                starting_pos.x = (int)i;
                starting_pos.y = (int)j;
            }
        }
    }

    int way = 1;
    bool finished = false;
    map<vector<int>,int> mp;
    while (!finished && way<5){
        Pipe *root = new Pipe(chars[starting_pos.x][starting_pos.y],starting_pos.x,starting_pos.y, nullptr);
        auto curr_pipe = root;
        int distance = -1;
        mp.clear();

        while(curr_pipe->coordinates.x != root->coordinates.x || curr_pipe->coordinates.y != root->coordinates.y || curr_pipe == root){
            findNext(curr_pipe, chars, root, way, distance);
            curr_pipe = curr_pipe->next;

            vector<int> key;
            key.push_back(curr_pipe->coordinates.x);
            key.push_back(curr_pipe->coordinates.y);
            if (mp.count(key) > 0 ){
                cout << "Loop detected";
                root = new Pipe(chars[starting_pos.x][starting_pos.y],starting_pos.x,starting_pos.y, nullptr);
                curr_pipe = root;
                mp.clear();
                //way++;
            }
            else{
                mp[key] = 1;
            }
        }

        if(curr_pipe->coordinates.x == root->coordinates.x && curr_pipe->coordinates.y == root->coordinates.y ){
            finished=true;
        }
        way++;
    }

    vector<vector<int>> rows(chars.size());
    vector<vector<int>> cols(chars[0].size());
    int sum = 0;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        sum++;

        rows[it->first[0]].push_back(it->first[1]);
        cols[it->first[1]].push_back(it->first[0]);
    }

    cout << "Max distance: " << sum/2 << endl;

    //print2dArray(rows,",");
    cout << rows[0][0] << endl;
    /*
    int curr_row = 0;
    bool can_be_pipe = false;
    for (int i = 0; i < pipes.size();i++){
        if (pipes[i][0]!= curr_row){
            curr_row = pipes[i][0];
            can_be_pipe = false;
            i--;
        }
        else{

        }
    }
    */
    
    //cout << starting_pos.x << ' ' << starting_pos.y << ' ' << chars[starting_pos.x][starting_pos.y];

    
    
    return 0;
}