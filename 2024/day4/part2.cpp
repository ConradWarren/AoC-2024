#include "../core.h"

bool Is_X(std::vector<std::string>& grid, int y, int x){
    if(y + 1 >= grid.size() || x + 1 >= grid[0].size() || x == 0 || y == 0) return false;

    if(!((grid[y+1][x+1] == 'M' && grid[y-1][x-1] == 'S') || (grid[y+1][x+1] == 'S' && grid[y-1][x-1] == 'M'))) return false;

    if(!((grid[y+1][x-1] == 'M' && grid[y-1][x+1] == 'S') || (grid[y+1][x-1] == 'S' && grid[y-1][x+1] == 'M'))) return false;

    return true;
}

int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    long long result = 0;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[i].size(); j++){
            if(input[i][j] == 'A' && Is_X(input_data, i, j)) result++;
        }
    }

    std::cout<<result<<'\n';
    return 0;
}
