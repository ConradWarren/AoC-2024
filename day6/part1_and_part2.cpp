#include "../core.h"

bool Will_Loop(std::vector<std::string>& grid, int y, int x, int delta, std::vector<std::vector<std::vector<bool>>>& delta_cache){
    
    if(delta_cache[y][x][delta]) return true;
    
    static std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int ty = y + directions[delta].first;
    int tx = x + directions[delta].second;
    int test = 0;
    
    while(ty >= 0 && tx >= 0 && ty < grid.size() && tx < grid[0].size() && grid[ty][tx] == '#'){
        delta = (delta+1)%4;
        ty = y + directions[delta].first;
        tx = x + directions[delta].second;
        test++;
    }
    
    if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()){
        return false;
    }
    
    delta_cache[y][x][delta] = true;
    bool result = Will_Loop(grid, ty, tx, delta, delta_cache);
    delta_cache[y][x][delta] = false;
    return result;
}

int Count(std::vector<std::string>& grid, int y, int x, int delta_y, int delta_x, std::vector<std::vector<bool>>& seen){
    
    int result = (seen[y][x]) ? 0 : 1;
    seen[y][x] = true;
    int ty = y + delta_y;
    int tx = x + delta_x;
    
    while(ty >= 0 && tx >= 0 && ty < grid.size() && tx < grid[0].size() && grid[ty][tx] == '#'){
        std::swap(delta_y, delta_x);
        delta_x *= -1;
        ty = y + delta_y;
        tx = x + delta_x;
    }
    
    if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()) return result;
    
    return result + Count(grid, ty, tx, delta_y, delta_x, seen);
}
int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    int y = -1;
    int x = -1;
    for(int i = 0; i < input_data.size() && y == -1; i++){
        std::string::iterator itr = std::find(input_data[i].begin(), input_data[i].end(), '^');
        if(itr != input_data[i].end()){
            y = i;
            x = static_cast<int>(itr - input_data[i].begin());
        }
    }
    std::vector<std::vector<std::vector<bool>>> delta_cache(input_data.size(), std::vector<std::vector<bool>>(input_data[0].size(), std::vector<bool>(4,false)));
    std::vector<std::vector<bool>> seen(input_data.size(), std::vector<bool>(input_data[0].size(), false));
    int result1 = Count(input_data, y, x, -1,0, seen);
    int result2 = 0;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[0].size(); j++){
            if(!seen[i][j]) continue;
            input_data[i][j] = '#';
            if(Will_Loop(input_data, y, x, 0, delta_cache)) result2++;
            input_data[i][j] = '.';
        }
    }
    std::cout<<result1<<'\n';
    std::cout<<result2<<'\n';
    return 0;
}
