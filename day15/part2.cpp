#include "../core.h"

bool Make_Move_X(std::vector<std::string>& grid, int delta_x, int y, int x){
    while(grid[y][x] != '#' && grid[y][x] != '.'){
        x += delta_x;
    }
    if(grid[y][x] == '#'){
        return false;
    }
    while(grid[y][x] != '@'){
        grid[y][x] = grid[y][x-delta_x];
        x -= delta_x;
    }
    grid[y][x] = '.';
    return true;
}

bool Can_Move(std::vector<std::string>& grid, int delta_y, int y, int x){
    if(grid[y][x] == '.') return true;
    if(grid[y][x] == '#') return false;
    if(grid[y][x] == '['){
        return Can_Move(grid, delta_y, y + delta_y, x) && Can_Move(grid, delta_y, y + delta_y, x+1);
    }
    if(grid[y][x] == ']'){
        return Can_Move(grid, delta_y, y + delta_y, x) && Can_Move(grid, delta_y, y + delta_y, x-1);
    }
    return false;
}

void Make_Move(std::vector<std::string>& grid, int delta_y, int y, int x,std::vector<std::vector<bool>>& moved){
    if(moved[y][x]) return;
    moved[y][x] = true;
    char last = grid[y][x];
    grid[y][x] = '.';
    if(grid[y+delta_y][x] == '.'){
        grid[y+delta_y][x] = last;
        return;
    }
    if(grid[y+delta_y][x] == '['){
        Make_Move(grid, delta_y, y+delta_y, x, moved);
        Make_Move(grid, delta_y, y+delta_y, x+1, moved);
        grid[y+delta_y][x] = last;
        return;
    }
    if(grid[y+delta_y][x] == ']'){
        Make_Move(grid, delta_y, y+delta_y, x, moved);
        Make_Move(grid, delta_y, y+delta_y, x-1, moved);
        grid[y+delta_y][x] = last;
    }
}

bool Make_Move_Y(std::vector<std::string>& grid, int delta_y, int y, int x){
    if(!Can_Move(grid, delta_y, y+delta_y, x)){
        return false;
    }
    std::vector<std::vector<bool>> moved(grid.size(), std::vector<bool>(grid[0].size(), false));
    Make_Move(grid, delta_y, y, x, moved);
    return true;
}

int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    std::vector<std::string> grid;
    std::string moves;
    
    int idx = 0;
    while(!input_data[idx].empty()){
        grid.push_back("");
        for(int i = 0; i < input_data[idx].size(); i++){
            if(input_data[idx][i] == '#'){
                grid.back() += "##";
            }else if(input_data[idx][i] == 'O'){
                grid.back() += "[]";
            }else if(input_data[idx][i] == '@'){
                grid.back() += "@.";
            }else if(input_data[idx][i] == '.'){
                grid.back() += "..";
            }
        }
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
        if(delta_x != 0 && Make_Move_X(grid, delta_x, y, x)){
            x += delta_x;
        }else if(delta_y != 0 && Make_Move_Y(grid, delta_y, y, x)){
            y += delta_y;
        }
    }
    
    long long result = 0;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++){
            if(grid[i][j] == '['){
                result += (i * 100) + j;
            }
        }
    }
    
    std::cout<<result<<'\n';
    return 0;
}
