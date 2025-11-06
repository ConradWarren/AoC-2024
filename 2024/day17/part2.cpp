#include "../core.h"

bool Search(std::vector<int>& nums, int idx, long long bitmask, long long current, long long& result, std::vector<std::unordered_set<long long>>& cache){

    if(idx < 0){
        result = current;
        return true;
    }

    if(cache[idx].find(bitmask) != cache[idx].end()){
        return false;
    }
    cache[idx].insert(bitmask);

    for(int i = 0; i <= 7; i++){
        long long t_bitmask = (bitmask << 3) | i;
        long long t_current = (current << 3 | i);
        long long out_put_num = i ^ (t_bitmask >> (i^2))%8LL ^ 1;

        if(out_put_num%8 == nums[idx] && Search(nums, idx-1, t_bitmask & ((1 << 10)-1), t_current, result, cache)){
            return true;
        }
    }

    return false;
}

int main() {

    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<long long> registers = {0,1,2,3,input_data[0][0], input_data[0][1], input_data[0][2]};
    std::vector<int> nums = input_data[4];

    std::vector<std::unordered_set<long long>> cache(nums.size());
    long long result = 0;
    Search(nums, nums.size()-1, 0, 0, result, cache);

    std::cout<<result<<'\n';
    return 0;
}
