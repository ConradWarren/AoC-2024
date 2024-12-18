#include "../core.h"

int Breadth_First_Search(std::vector<std::vector<int>>& counts, int y, int x, std::vector<std::vector<bool>>& seen){

    std::queue<std::pair<int, int>> node_queue;
    std::vector<std::pair<int, int>> directions = {{1,1},{-1,1}, {-1,-1}, {1,-1}, {0,1}, {1, 0}, {-1, 0}, {0, -1}};

    seen[y][x] = true;
    node_queue.push({y,x});
    int res = 1;

    while (!node_queue.empty()){

        y = node_queue.front().first;
        x = node_queue.front().second;
        node_queue.pop();
        for(int i = 0; i < directions.size(); i++){

            int ty = y + directions[i].first;
            int tx = x + directions[i].second;

            if(ty < 0 || tx < 0 || ty >= counts.size() || tx >= counts[0].size()) continue;

            if(!seen[ty][tx] && counts[ty][tx] != 0){
                seen[ty][tx] = true;
                node_queue.push({ty,tx});
                res++;
            }

        }

    }


    return res;
}

int Get_Score(std::vector<std::vector<int>>& counts, int height, int width){

    int res = 0;
    std::vector<std::vector<bool>> seen(height, std::vector<bool>(width, false));

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(!seen[i][j] && counts[i][j]){
                int current = Breadth_First_Search(counts, i, j, seen);
                res = std::max(current, res);
            }
        }
    }


    return res;
}

int main() {

    std::vector<std::vector<long long>> nums;
    Read_Data("../input.txt", nums);

    int width = 101;
    int height = 103;
    int best_score = 0;
    int idx = -1;


    for(int time = 1; time < 10000; time++){
        std::vector<std::vector<int>> counts(height, std::vector<int>(width, 0));
        for(int i = 0; i < nums.size(); i++){

            long long x = nums[i][0];
            long long y = nums[i][1];
            long long delta_x = nums[i][2];
            long long delta_y = nums[i][3];

            x += delta_x * time;
            y += delta_y * time;

            x = ((x%width)+width)%width;
            y = ((y%height) + height)%height;

            counts[y][x]++;
        }
        int current = Get_Score(counts, height, width);
        if(current > best_score){
            best_score = current;
            idx = time;
        }
    }

    std::cout<<idx<<'\n';

    return 0;
}
