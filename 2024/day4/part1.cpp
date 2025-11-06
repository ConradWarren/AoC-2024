#include "../core.h"

bool Is_Word(std::vector<std::string>& grid, std::string& str, int y, int x, int delta_x, int delta_y){
    int idx = 0;
    while(idx < str.size() && y < grid.size() && x < grid[0].size() && grid[y][x] == str[idx]){
        idx++;
        y += delta_y;
        x += delta_x;
    }
    return idx >= str.size();
}
int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    std::string target = "XMAS";
    long long result = 0;

    std::vector<std::pair<int, int>> directions = {{0,1}, {1, 0}, {0,-1}, {-1, 0}, {1,1}, {-1, -1}, {-1, 1}, {1, -1}};
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[i].size(); j++){
            for(int z = 0; z < directions.size() && input_data[i][j] == 'X'; z++){
                if(Is_Word(input_data, target, i, j, directions[z].first, directions[z].second)) result++;
            }
        }
    }
    std::cout<<result<<'\n';
    return 0;
}
