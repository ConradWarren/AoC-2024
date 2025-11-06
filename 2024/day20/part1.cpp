#include "../core.h"

long long Dijkstra(std::vector<std::string>& grid, int y, int x, int TY, int TX, std::vector<std::vector<long long>>& cache){

    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> min_heap;
    std::vector<std::pair<int, int>> directions = {{0,1}, {1, 0}, {-1, 0},{0,-1}};
    cache[y][x] = 0;
    min_heap.push({0,y,x});

    while(!min_heap.empty()){

        y = min_heap.top()[1];
        x = min_heap.top()[2];
        int cost = min_heap.top()[0];

        min_heap.pop();

        if(cache[y][x] < cost) continue;

        for(int i = 0; i < directions.size(); i++){

            int ty = y + directions[i].first;
            int tx = x + directions[i].second;

            if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()) continue;

            if(grid[ty][tx] == '#') continue;

            if(cache[ty][tx] > cost + 1){
                cache[ty][tx] = cost+1;
                min_heap.push({cost + 1, ty,tx});
            }
        }

    }

    return cache[TY][TX];
}


int Get_Cheat_Count(std::vector<std::vector<long long>>& cache, std::vector<std::string>& grid, int y, int x){

    std::vector<std::pair<int, int>> directions = {{0,1}, {1, 0}, {-1, 0},{0,-1}};
    std::vector<std::vector<bool>> seen(grid.size(), std::vector<bool>(grid[0].size(), false));

    std::queue<std::vector<int>> node_queue;
    node_queue.push({0,y, x});
    int result = 0;
    int SY = y;
    int SX = x;

    while (!node_queue.empty()){

        y = node_queue.front()[1];
        x = node_queue.front()[2];
        int count = node_queue.front()[0];

        node_queue.pop();
        if(count > 1) continue;

        for(int i = 0; i < directions.size(); i++){

            int ty = y + directions[i].first;
            int tx = x + directions[i].second;

            if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size()) continue;

            if(seen[ty][tx]) continue;

            if(cache[SY][SX] - cache[ty][tx] - count >= 101 && grid[ty][tx] != '#'){
                result++;
            }
            seen[ty][tx] = true;
            node_queue.push({count+1, ty,tx});
        }

    }

    return result;
}



int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    int y = -1;
    int x = -1;
    int TY = -1;
    int TX = -1;
    for(int i = 0; i < input_data.size() && (y == -1 || TY == -1); i++){
        for(int j = 0; j < input_data[0].size(); j++){
            if(input_data[i][j] == 'S'){
                y = i;
                x = j;
            }else if(input_data[i][j] == 'E'){
                TY = i;
                TX = j;
            }
        }
    }
    std::vector<std::vector<long long>> cache1(input_data.size(), std::vector<long long>(input_data[0].size(), INT_MAX));
    std::vector<std::vector<long long>> cache2(input_data.size(), std::vector<long long>(input_data[0].size(), INT_MAX));
    long long time = Dijkstra(input_data, y, x, TY, TX, cache1);
    Dijkstra(input_data, TY, TX, y, x, cache2);


    long long result = 0;
    for(int i = 0; i < cache1.size(); i++){
        for(int j = 0; j < cache1[0].size(); j++){
            if(cache1[i][j] + cache2[i][j] == time){
                result += Get_Cheat_Count(cache2, input_data, i, j);
            }
        }
    }

    std::cout<<result<<'\n';

    return 0;
}
