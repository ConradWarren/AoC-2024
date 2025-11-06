#include "../core.h"

bool Can_Pass(std::vector<std::vector<int>>& grid, int time){

    std::vector<std::vector<int>> cache(grid.size(), std::vector<int>(grid[0].size(), INT_MAX));
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> min_heap;
    std::vector<std::pair<int, int>> directions = {{0,1}, {1, 0}, {-1, 0},{0,-1}};
    cache[0][0] = 0;
    min_heap.push({0,0});

    while(!min_heap.empty()){

        int y = min_heap.top().second/grid[0].size();
        int x = min_heap.top().second%grid[0].size();
        int cost = min_heap.top().first;
        min_heap.pop();


        if(cache[y][x] < cost) continue;

        for(int i = 0; i < directions.size(); i++){

            int ty = y + directions[i].first;
            int tx = x + directions[i].second;

            if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()) continue;

            if(grid[ty][tx] != 0 && time >= grid[ty][tx]) continue;

            if(cache[ty][tx] > cost + 1){
                cache[ty][tx] = cost + 1;
                min_heap.push({cost + 1, ty * grid[0].size() + tx});
            }
        }

    }

    return cache.back().back() != INT_MAX;
}


int main() {

    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::vector<int>> grid(71, std::vector<int>(71, false));

    for(int i = 0; i < input_data.size(); i++){
        grid[input_data[i][1]][input_data[i][0]] = i+1;
    }

    int low = 0;
    int high = input_data.size();
    while(low < high){

        int mid = (low + high)/2;

        if(Can_Pass(grid, mid)){
            low = mid+1;
        }else{
            high = mid;
        }
    }

    std::cout<<input_data[low-1][0]<<" "<<input_data[low-1][1]<<std::endl;

    return 0;
}
