#include "../core.h"

bool Make_Move(std::vector<std::string>& grid, int delta_x, int delta_y, int y, int x){
    while(grid[y][x] != '#' && grid[y][x] != '.'){
        x += delta_x;
        y += delta_y;
    }
    if(grid[y][x] == '#'){
        return false;
    }
    while(grid[y][x] != '@'){
        grid[y][x] = grid[y-delta_y][x-delta_x];
        x -= delta_x;
        y -= delta_y;
    }
    grid[y][x] = '.';
    return true;
}

int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    std::vector<std::string> grid;
    std::string moves;

    int idx = 0;
    while(!input_data[idx].empty()){
        grid.push_back(input_data[idx]);
        idx++;
    }
    idx++;

    while(idx < input_data.size()){
        moves += input_data[idx];
        idx++;
    }

    int y = -1;
    int x = -1;
    for(int i = 0; i < grid.size() && y == -1; i++){
        auto itr = std::find(grid[i].begin(), grid[i].end(), '@');
        if(itr != grid[i].end()){
            y = i;
            x = static_cast<int>(itr - grid[i].begin());
        }
    }

    for(int i = 0; i < moves.size(); i++){
        int delta_y = 0;
        int delta_x = 0;
        if(moves[i] == '^') delta_y = -1;
        else if(moves[i] == '>') delta_x = 1;
        else if(moves[i] == '<') delta_x = -1;
        else if(moves[i] == 'v') delta_y = 1;

        if(Make_Move(grid, delta_x, delta_y, y, x)){
            y += delta_y;
            x += delta_x;
        }
    }

    long long result = 0;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++){
            if(grid[i][j] == 'O'){
                result += (i * 100) + j;
            }
        }
    }

    std::cout<<result<<'\n';
    return 0;
}
