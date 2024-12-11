#include "../core.h"

int Breadth_First_Search(std::vector<std::string>& grid, int y, int x){
    std::vector<std::vector<bool>> seen(grid.size(),std::vector<bool>(grid[0].size(), false));
    seen[y][x] = true;

    std::vector<std::pair<int, int>> directions = {{0,1}, {1, 0}, {0,-1}, {-1, 0}};
    std::queue<std::pair<int, int>> node_queue;
    node_queue.push({y,x});

    int result = 0;
    while(!node_queue.empty()){
        y = node_queue.front().first;
        x = node_queue.front().second;
        node_queue.pop();
        if(grid[y][x] == '9'){
            result++;
            continue;
        }
        for (int i = 0; i < directions.size(); ++i) {
            int ty = y + directions[i].first;
            int tx = x + directions[i].second;
            if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()) continue;
            if(grid[y][x]+1 == grid[ty][tx] && !seen[ty][tx]){
                seen[ty][tx] = true;
                node_queue.push({ty,tx});
            }
        }
    }
    return result;
}

int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    long long result = 0;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[0].size(); j++){
            if(input_data[i][j] == '0'){
                result += Breadth_First_Search(input_data, i, j);
            }
        }
    }

    std::cout<<result<<'\n';
    return 0;
}
