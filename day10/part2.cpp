#include "../core.h"

long long Depth_First_Search(std::vector<std::string>& grid, int y, int x, std::vector<std::vector<long long>>& cache){
    if(grid[y][x] == '9') return 1;

    if(cache[y][x] != -1){
        return cache[y][x];
    }

    std::vector<std::pair<int, int>> directions = {{0,1}, {1, 0}, {0,-1}, {-1, 0}};

    long long result = 0;
    for(int i = 0; i < directions.size(); i++){
        int ty = y + directions[i].first;
        int tx = x + directions[i].second;
        if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()) continue;
        if(grid[y][x]+1 == grid[ty][tx]){
            result += Depth_First_Search(grid, ty, tx, cache);
        }
    }
    return cache[y][x] = result;
}
int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    std::vector<std::vector<long long>> cache(input_data.size(), std::vector<long long>(input_data[0].size(), -1));

    long long result = 0;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[0].size(); j++){
            if(input_data[i][j] == '0'){
                result += Depth_First_Search(input_data, i, j, cache);
            }
        }
    }
    std::cout<<result<<'\n';
    return 0;
}
