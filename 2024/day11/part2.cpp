#include "core.h"

long long Eval(long long num, int depth, std::vector<std::unordered_map<long long, long long>>& cache){

    if(depth == 75){
        return 1;
    }

    if(cache[depth].find(num) != cache[depth].end()){
        return cache[depth][num];
    }

    if(num == 0){
        return cache[depth][num] = Eval(1, depth+1, cache);
    }

    int digits = static_cast<int>(std::log10(num))+1;
    if(digits%2 == 0){
        return cache[depth][num] = Eval(num%(static_cast<int>(std::pow(10, digits/2))), depth+1, cache) + Eval(num/(static_cast<int>(std::pow(10, digits/2))), depth+1, cache);
    }


    return cache[depth][num] = Eval(num * 2024, depth+1, cache);
}

int main() {

    std::vector<long long> nums;
    Read_Data("../input.txt", nums);
    std::vector<std::unordered_map<long long, long long>> cache(75);
    long long result = 0;

    for(int i = 0; i < nums.size(); i++){
        result += Eval(nums[i], 0, cache);
    }

    std::cout<<result<<'\n';
    return 0;
}
