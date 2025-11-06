#include "../core.h"

inline bool Is_Edge(std::vector<std::string>& grid, int y, int x, char target){
    return (y < 0 || x < 0 || y >= grid.size() || x >= grid[0].size() || grid[y][x] != target);
}

long long Breadth_First_Search(std::vector<std::string>& grid, int y, int x, std::vector<std::vector<bool>>& seen){

    std::vector<std::vector<bool>> counted(grid.size(), std::vector<bool>(grid[0].size(), false));
    char target = grid[y][x];

    long long area = 0;
    long long sides = 0;

    seen[y][x] = true;

    std::queue<std::pair<int, int>> node_queue;
    node_queue.push({y,x});
    std::vector<std::pair<int, int>> directions = {{0,1},{1,0},{0,-1},{-1, 0}};
    while (!node_queue.empty()){

        y = node_queue.front().first;
        x = node_queue.front().second;
        area++;

        bool up = Is_Edge(grid, y-1, x, target);
        bool down = Is_Edge(grid, y+1, x, target);
        bool right = Is_Edge(grid, y, x+1, target);
        bool left = Is_Edge(grid, y, x-1, target);

        if(up && right) sides++;
        if(up && left) sides++;
        if(down && right) sides++;
        if(down && left) sides++;
        if(!up && !right && Is_Edge(grid, y-1, x+1, target)) sides++;
        if(!up && !left && Is_Edge(grid, y-1, x-1, target)) sides++;
        if(!down && !right && Is_Edge(grid, y+1, x+1, target)) sides++;
        if(!down && !left && Is_Edge(grid, y+1, x-1, target)) sides++;

        node_queue.pop();

        for(int i = 0; i < directions.size(); i++){

            int ty = y + directions[i].first;
            int tx = x + directions[i].second;

            if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()){
                continue;
            }

            if(grid[ty][tx] == target && !seen[ty][tx]){
                seen[ty][tx] = true;
                node_queue.push({ty,tx});
            }
        }
    }
    
    return area * sides;
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::vector<bool>> seen(input_data.size(), std::vector<bool>(input_data[0].size(), false));

    long long result = 0;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[0].size(); j++){

            if(!seen[i][j]){
                result += Breadth_First_Search(input_data, i, j, seen);
            }

        }
    }

    std::cout<<result<<'\n';
    return 0;
}
