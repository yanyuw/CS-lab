#include <iostream>

using namespace std;
#define M 5
#define N 4 
 

int maze[M][N] = {
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 1}
};
int sol[M][N] = {0};

bool inMaze(int x, int y){
    if(x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1){
        return true;
    }
    return false;
}
bool solveMaze(int x, int y){
    if(x == M-1 && y == N-1){
        sol[x][y] = 1;
        return true;
    }
    
    if(inMaze(x,y)){
        sol[x][y] = 1;
        if(solveMaze(x+1, y)){
            return true;
        }
        if(solveMaze(x, y+1)){
            return true;
        }
    }

    sol[x][y] = 0;
    return false;
}


int main(){
    
    if(!solveMaze(0, 0)){
        cout << "no solution" << endl;
    } else {
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                cout << sol[i][j] << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}