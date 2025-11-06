#include "../core.h"

long long Get_Score(std::vector<std::vector<int>>& counts, int height, int width){
    long long one = 0;
    long long two = 0;
    long long three = 0;
    long long four = 0;
    for(int i = 0; i < height/2; i++){
        for(int j = 0; j < width/2; j++){
            one += counts[i][j];
        }
    }
    for(int i = 0; i < height/2; i++){
        for(int j = width/2+1; j < width; j++){
            two += counts[i][j];
        }
    }
    for(int i = height/2+1; i < height; i++){
        for(int j = 0; j < width/2; j++){
            three += counts[i][j];
        }
    }
    for(int i = height/2+1; i < height; i++){
        for(int j = width/2+1; j < width; j++){
            four += counts[i][j];
        }
    }
    return one == two && three == four;
}

int main() {
    std::vector<std::vector<long long>> nums;
    Read_Data("../input.txt", nums);
    int width = 101;
    int height = 103;

    std::vector<std::vector<int>> counts(height, std::vector<int>(width, 0));
    for(int i = 0; i < nums.size(); i++){
        long long x = nums[i][0];
        long long y = nums[i][1];
        long long delta_x = nums[i][2];
        long long delta_y = nums[i][3];
        x += delta_x * 100;
        y += delta_y * 100;
        x = ((x%width)+width)%width;
        y = ((y%height) + height)%height;
        counts[y][x]++;
    }

    std::cout<<Get_Score(counts, height, width)<<'\n';

    return 0;
}
