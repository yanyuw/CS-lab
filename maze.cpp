#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <random>
#include <set>
#include <list>

using namespace std;

#define random(x) (rand()%x)
#define MAX 1000

int width, height;
char maze[MAX][MAX];


struct Block{
    int x;
    int y;
    // bool isVisited;
    char d;
};


void initmaze(int w, int h){
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            // if(i % 2 == 0 || j % 2 == 0){
                maze[j][i] = 0;
            // } else {
            //     maze[j][i] = 1;
            // }
        }
    }
}
void printmaze(int w, int h){
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            // printf("%d",maze[j][i]);
            if(maze[j][i] == 0){
                cout << '#';
            }else{
                cout << ' ';
            }
        }
        cout << endl;
    }
}

int main(){
    //迷宫长宽
    cout << "input width:";
    cin >> width;
    cout << "input height:";
    cin >> height;

    int w = width * 2 + 1;
    int h = height * 2 + 1;
    //初始化迷宫 生成一个2*w+1 2*h+1的数组
    initmaze(w, h);

    //随机选择一个起始点
    srand(time(NULL));
    int x = 2 * random(width) + 1;
    int y = 2 * random(height) + 1;

    
    // cout << x << y;
    
    //把邻墙放入列表
    vector<Block> neighbor;
    
    if(x > 1){
        Block block = {x-1, y, 'L'};
        neighbor.push_back(block);
    }
    if(x < w - 2){
        Block block = {x+1, y, 'R'};
        neighbor.push_back(block);
    }
    if(y > 1){
        Block block = {x, y-1 ,'U'};
        neighbor.push_back(block);
    }
    if(y < h - 2){
        Block block = {x, y+1, 'D'};
        neighbor.push_back(block);
    }
    
    //
    while(neighbor.size()){
        int r = random(neighbor.size());
        switch(neighbor[r].d){
            case 'U':
                y = neighbor[r].y -1;
                x = neighbor[r].x;
                break;
            case 'D':
                y = neighbor[r].y + 1;
                x = neighbor[r].x;
                break;
            case 'L':
                y = neighbor[r].y;
                x = neighbor[r].x - 1;
                break;
            case 'R':
                y = neighbor[r].y;
                x = neighbor[r].x + 1;
                break;
        }
        if(maze[y][x] == 0){
            //打通墙和通路
            maze[neighbor[r].y][neighbor[r].x] = 1;
            maze[y][x] = 1;


            if(neighbor[r].d != 'D' && y > 1 && maze[y-1][x] == 0 && maze[y-2][x] == 0){
                Block block = {x, y-1, 'U'};
                neighbor.push_back(block);
            }
            if(neighbor[r].d != 'U' && y < h-2 && maze[y+1][x] == 0 && maze[y+2][x] == 0){
                Block block = {x, y+1, 'D'};
                neighbor.push_back(block);
            }
            if(neighbor[r].d != 'R' && x > 1 && maze[y][x-1] == 0 && maze[y][x-2] == 0){
                Block block = {x-1, y, 'L'};
                neighbor.push_back(block);
            }
            if(neighbor[r].d != 'L' && x < w-2 && maze[y][x+1] == 0 && maze[y][x+2] == 0){
                Block block = {x+1, y, 'R'};
                neighbor.push_back(block);
            } 
        }
        neighbor.erase(neighbor.begin()+r);
    }
    
    printmaze(w, h);

    return 0;

}
