#include "../core.h"

long long Dijkstra(std::vector<std::string>& grid, int y, int x, int TY, int TX, int idx, std::vector<std::vector<std::vector<long long>>>& cache){
    
    std::priority_queue<std::vector<long long>,  std::vector<std::vector<long long>>, std::greater<std::vector<long long>>> min_heap;

    std::vector<std::pair<int, int>> directions = {{0,1}, {1,0},{0,-1},{-1,0}};
    cache[idx][y][x] = 0;
    min_heap.push({0, y, x, idx});

    while (!min_heap.empty()){

        y = min_heap.top()[1];
        x = min_heap.top()[2];
        idx = min_heap.top()[3];
        long long cost = min_heap.top()[0];
        min_heap.pop();
        if(cost > cache[idx][y][x]) continue;

        int ty = y + directions[idx].first;
        int tx = x + directions[idx].second;

        if(cache[(idx+1)%4][y][x] > 1000LL + cost){
            cache[(idx+1)%4][y][x] = 1000LL + cost;
            min_heap.push({1000+cost, y, x, (idx+1)%4});
        }

        if(cache[(idx+3)%4][y][x] > 1000LL + cost){
            cache[(idx+3)%4][y][x] = 1000 + cost;
            min_heap.push({1000+cost, y, x, (idx+3)%4});
        }

        if(ty < 0 || tx < 0 || ty >= grid.size() || tx >= grid[0].size() || grid[ty][tx] == '#') continue;

        if(cache[idx][ty][tx] > cost + 1){
            cache[idx][ty][tx] = cost + 1;
            min_heap.push({cost + 1, ty, tx, idx});
        }

    }
    return std::min(std::min(cache[0][TY][TX], cache[1][TY][TX]), std::min(cache[2][TY][TX], cache[3][TY][TX]));
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    int y = -1;
    int x = -1;
    int TY = -1;
    int TX = -1;

    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[0].size(); j++){
            if(input_data[i][j] == 'S'){
                y = i;
                x = j;
            }
            if(input_data[i][j] == 'E'){
                TY = i;
                TX = j;
            }
        }
    }

    std::vector<std::vector<std::vector<long long>>> cache1(4, std::vector<std::vector<long long>>(input_data.size(), std::vector<long long>(input_data[0].size(), (1LL << 56))));
    std::vector<std::vector<std::vector<long long>>> cache2(4, std::vector<std::vector<long long>>(input_data.size(), std::vector<long long>(input_data[0].size(), (1LL << 56))));

    long long target = Dijkstra(input_data, y, x, TY, TX, 0, cache1);
    Dijkstra(input_data, TY, TX, y, x, 0, cache2);
    Dijkstra(input_data, TY, TX, y, x, 1, cache2);
    Dijkstra(input_data, TY, TX, y, x, 2, cache2);
    Dijkstra(input_data, TY, TX, y, x, 3, cache2);

    int result = 2;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[0].size(); j++){

            if(input_data[i][j] != '.') continue;

            bool is_valid = false;
            for(int idx1 = 0; idx1 < 4 && !is_valid; idx1++){
                if(idx1 == 0 && cache1[0][i][j] + cache2[2][i][j] == target){
                    is_valid = true;
                }
                if(idx1 == 2 && cache1[2][i][j] + cache2[0][i][j] == target){
                    is_valid = true;
                }
                if(idx1 == 1 && cache1[1][i][j] + cache2[3][i][j] == target){
                    is_valid = true;
                }
                if(idx1 == 3 && cache1[3][i][j] + cache2[1][i][j] == target){
                    is_valid = true;
                }
            }
            if(is_valid){
                result++;
                input_data[i][j] = '0';
            }
        }
    }

    std::cout<<result<<'\n';
    return 0;
}
