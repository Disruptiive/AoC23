#include <iostream>
#include <set>
#include <map>

#include "helpers.hpp"

enum direction{
    Up,
    Down,
    Right,
    Left
};

int DIRECTION_N = 4;

enum tiles_type{
    Empty,
    Mirror_L,
    Mirror_R,
    Split_H,
    Split_V,
};

struct coordinates{
    int i;
    int j;
};

class Ball{
    public:
        direction dir;
        coordinates init_cord;
        coordinates curr_cord;
        bool dead;
        int max_row;
        int max_col;

    Ball(direction _dir, coordinates _coords,int _max_row, int _max_col) : dir(_dir), init_cord(_coords), curr_cord(_coords), max_row(_max_row), max_col(_max_col), dead(false) {}

    bool operator<(const Ball& other_ball)const{
        return init_cord.i * max_col + init_cord.j*DIRECTION_N + dir < other_ball.init_cord.i * max_col + other_ball.init_cord.j*DIRECTION_N + dir;
    }
};

class Tile{
    public:
        coordinates coords;
        tiles_type type;
        bool visited;
        map<direction,int> was_here;

    Tile(coordinates _coords, tiles_type _type){
        map<direction,int> mp;
        coords = _coords;
        type = _type;
        visited = false;
        was_here = mp;
        was_here[Right] = 0;
        was_here[Left] = 0;
        was_here[Up] = 0;
        was_here[Down] = 0;

    } 
};

void moveBallRight(Ball &ball,vector<vector<Tile>> &tiles){
    tiles[ball.curr_cord.i][ball.curr_cord.j].was_here[Right]++;
    if(ball.curr_cord.j+1<ball.max_col){
        ball.curr_cord.j++;
        tiles[ball.curr_cord.i][ball.curr_cord.j].visited=true;
    }
    else{
        ball.dead = true;
    }
}

void moveBallLeft(Ball &ball,vector<vector<Tile>> &tiles){
    tiles[ball.curr_cord.i][ball.curr_cord.j].was_here[Left]++;
    if(ball.curr_cord.j>0){
        ball.curr_cord.j--;
        tiles[ball.curr_cord.i][ball.curr_cord.j].visited=true;
    }
    else{
        ball.dead = true;
    }
}

void moveBallUp(Ball &ball,vector<vector<Tile>> &tiles){
    tiles[ball.curr_cord.i][ball.curr_cord.j].was_here[Up]++;
    if(ball.curr_cord.i>0){
        ball.curr_cord.i--;
        tiles[ball.curr_cord.i][ball.curr_cord.j].visited=true;
    }
    else{
        ball.dead = true;
    }
}

void moveBallDown(Ball &ball,vector<vector<Tile>> &tiles){
    tiles[ball.curr_cord.i][ball.curr_cord.j].was_here[Down]++;
    if(ball.curr_cord.i+1<ball.max_row){
        ball.curr_cord.i++;
        tiles[ball.curr_cord.i][ball.curr_cord.j].visited=true;
    }
    else{
        ball.dead = true;
    }
}

void moveEmpty(Ball &ball,vector<vector<Tile>> &tiles){
    if(ball.dir == Right){
        
        moveBallRight(ball,tiles);
    }
    else if(ball.dir == Left){
        moveBallLeft(ball,tiles);
    }
    else if(ball.dir == Up){
        moveBallUp(ball,tiles);
    }
    else if(ball.dir == Down){
        moveBallDown(ball,tiles);
    }
}

void moveMirror(Ball &ball,tiles_type mirror_type, vector<vector<Tile>> &tiles){
    if(mirror_type == Mirror_L){
        if(ball.dir == Right){
            moveBallUp(ball,tiles);
            ball.dir = Up;
        }
        else if(ball.dir == Left){
            moveBallDown(ball,tiles);
            ball.dir = Down;
        }
        else if(ball.dir == Up){
            moveBallRight(ball,tiles);
            ball.dir = Right;
        }
        else if(ball.dir == Down){
            moveBallLeft(ball,tiles);
            ball.dir = Left;
        }
    }

    else if(mirror_type == Mirror_R){
        if(ball.dir == Right){
            moveBallDown(ball,tiles);
            ball.dir = Down;
        }
        else if(ball.dir == Left){
            moveBallUp(ball,tiles);
            ball.dir = Up;
        }
        else if(ball.dir == Up){
            moveBallLeft(ball,tiles);
            ball.dir = Left;
            
        }
        else if(ball.dir == Down){
            moveBallRight(ball,tiles);
            ball.dir = Right;
        }
    }
}

void moveSplitter(Ball &ball,tiles_type splitter_type,set<Ball> &balls,vector<vector<Tile>> &tiles){
    if(splitter_type == Split_H){
        if(ball.dir==Right){
            moveBallRight(ball,tiles);
        } 
        else if (ball.dir==Left){
            moveBallLeft(ball,tiles);
        }
        else{
            if(ball.curr_cord.j+1<ball.max_col && ball.curr_cord.j>0){
                balls.insert(Ball(Left,coordinates{ball.curr_cord.i,ball.curr_cord.j-1},ball.max_row,ball.max_col));
                tiles[ball.curr_cord.i][ball.curr_cord.j-1].visited = true;
                moveBallRight(ball,tiles);
                ball.dir = Right;
            }
            else if(ball.curr_cord.j+1<ball.max_col && ball.curr_cord.j<=0){
                moveBallRight(ball,tiles);
                ball.dir = Right;
            }

            else if(ball.curr_cord.j+1>=ball.max_col && ball.curr_cord.j>0){
                balls.insert(Ball(Left,coordinates{ball.curr_cord.i,ball.curr_cord.j-1},ball.max_row,ball.max_col));
                tiles[ball.curr_cord.i][ball.curr_cord.j-1].visited = true;
                ball.dead = true;
            }
        }
    }

    else if(splitter_type == Split_V){
        if(ball.dir==Up){
            moveBallUp(ball,tiles);
        } 
        else if (ball.dir==Down){
            moveBallDown(ball,tiles);
        }
        else{
            if(ball.curr_cord.i+1<ball.max_row && ball.curr_cord.i>0){
                balls.insert(Ball(Up,coordinates{ball.curr_cord.i-1,ball.curr_cord.j},ball.max_row,ball.max_col));
                tiles[ball.curr_cord.i-1][ball.curr_cord.j].visited = true;
                moveBallDown(ball,tiles);
                ball.dir = Down;
            }
            else if(ball.curr_cord.i+1<ball.max_row && ball.curr_cord.i<=0){
                moveBallDown(ball,tiles);
                ball.dir = Down;
            }

            else if(ball.curr_cord.i+1>=ball.max_row && ball.curr_cord.i>0){
                balls.insert(Ball(Up,coordinates{ball.curr_cord.i-1,ball.curr_cord.j},ball.max_row,ball.max_col));
                tiles[ball.curr_cord.i-1][ball.curr_cord.j].visited = true;
                ball.dead = true;
            }
        }
    }
}

void calculateBallMovement(Ball &ball, vector<vector<Tile>> &tiles,set<Ball> &balls){
    if (tiles[ball.curr_cord.i][ball.curr_cord.j].was_here[ball.dir]>0){
        ball.dead = true;
        return;
    }
    if (tiles[ball.curr_cord.i][ball.curr_cord.j].type == Empty){
        moveEmpty(ball,tiles);
    }

    else if (tiles[ball.curr_cord.i][ball.curr_cord.j].type == Mirror_L){
        moveMirror(ball,Mirror_L,tiles);
    }

    else if (tiles[ball.curr_cord.i][ball.curr_cord.j].type == Mirror_R){
        moveMirror(ball,Mirror_R,tiles);
    }

    else if (tiles[ball.curr_cord.i][ball.curr_cord.j].type == Split_H){
        moveSplitter(ball,Split_H,balls,tiles);
    }

    else if (tiles[ball.curr_cord.i][ball.curr_cord.j].type == Split_V){
        moveSplitter(ball,Split_V,balls,tiles);
    }
}

void runBallLoop(set<Ball> &ball_set,std::vector<std::vector<Tile>> &tiles){
    int cnt = 0;

    bool elementsInserted = false;
    do {
        elementsInserted = false;
        for (auto it = ball_set.begin(); it != ball_set.end(); ++it) {
            auto initial_size = ball_set.size();
            Ball& ball = const_cast<Ball&>(*it);
            cout << cnt++ << endl;
            while(!ball.dead){
                calculateBallMovement(ball,tiles,ball_set);
                cout << ball.curr_cord.i << " " << ball.curr_cord.j << endl;
            }
            auto size_after = ball_set.size();
            
            // Insert new elements directly into the set
            if (initial_size!=size_after) {
                // Set the flag if new elements are inserted
                elementsInserted = true;
            }
        }

    } while (elementsInserted);

    /*
    Ball& ball = const_cast<Ball&>(*(ball_set.begin()));
    while(!ball_set.empty()){
        cout << "COORDS: " << ball.curr_cord.i <<  " " << ball.curr_cord.j <<  endl;

        calculateBallMovement(ball,tiles,ball_set);

        //cout << "After move: " << ball.curr_cord.i <<  " " << ball.curr_cord.j <<  endl;
        if (ball.dead){
            auto curr_ball = ball_set.find(ball);
            if (curr_ball!=ball_set.end()){
                cout << "Starting: " << (*curr_ball).init_cord.i << " " << (*curr_ball).init_cord.j << " eliminated" << endl;
                ball_set.erase(curr_ball);
            }
            else{
                cout << " :( ";
            }
            if(!ball_set.empty())
                ball = const_cast<Ball&>(*(ball_set.begin()));
            else
                cout << "Herherhe";
        }
    }
    */
}

int main(){
    std::vector<std::string> lines = fileSplitLines("day16.txt");
    std::vector<std::vector<Tile>> tiles;

    int max_row = (int)lines.size();
    int max_col = (int)lines[0].size();
    for(int i=0;i<lines.size();i++){
        std::vector<Tile> row;
        for(int j=0;j<lines[i].size();j++){
            if (lines[i][j] == '.'){
                row.push_back(Tile{coordinates{i,j},Empty});
            }
            else if (lines[i][j] == '/'){
                row.push_back(Tile{coordinates{i,j},Mirror_L});
            }
            else if (lines[i][j] == '\\'){
                row.push_back(Tile{coordinates{i,j},Mirror_R});
            }
            else if (lines[i][j] == '-'){
                row.push_back(Tile{coordinates{i,j},Split_H});
            }
            else if (lines[i][j] == '|'){
                row.push_back(Tile{coordinates{i,j},Split_V});
            }
            else{
                std::cout << "Wtf" << std::endl;
            }
        }
        tiles.push_back(row);
    }

    Ball init_ball = Ball(Right,coordinates{0,0},max_row,max_col);
    tiles[0][0].visited = true;
    set<Ball> ball_set;
    ball_set.insert(init_ball);

    runBallLoop(ball_set,tiles);

    int cnt = 0;
    for(int i=0;i<tiles.size();i++){
        for(int j=0;j<tiles[i].size();j++){
            if (tiles[i][j].visited){
                cnt++;
            }
        }
    }

    cout << "Part 1) " << cnt << endl;
    
}