int Dijkstra(std::vector<std::vector<bool>>& grid){

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

            if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size() || grid[ty][tx]) continue;

            if(cache[ty][tx] > cost + 1){
                cache[ty][tx] = cost + 1;
                min_heap.push({cost + 1, ty * grid[0].size() + tx});
            }
        }

    }

    return cache.back().back();
}


int main() {

    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::vector<bool>> grid(71, std::vector<bool>(71, false));

    for(int i = 0; i < input_data.size && i < 2024(); i++){
        grid[input_data[i][1]][input_data[i][0]] = true;
    }

    std::cout<Dijkstra(grid)<<'\n';


    return 0;
}
