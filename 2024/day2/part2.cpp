#include "../core.h"

bool Is_Valid_Increasing(std::vector<int>& nums, int idx, bool used_skip, std::vector<int>& cache){

    if(idx + 1 >= nums.size() || (!used_skip && idx + 2 >= nums.size())){
        return true;
    }

    if(cache[idx * 2 + used_skip] != -1) return static_cast<bool>(cache[idx*2 + used_skip]);

    bool use_skip = (!used_skip && nums[idx + 2] > nums[idx] && nums[idx + 2] - nums[idx] <= 3) && Is_Valid_Increasing(nums, idx + 2,true, cache);
    bool take = (nums[idx + 1] > nums[idx] && nums[idx + 1] - nums[idx] <= 3) && Is_Valid_Increasing(nums, idx + 1, used_skip, cache);

    return cache[idx*2 + used_skip] = static_cast<int>(use_skip || take);
}

bool Is_Valid_Decreasing(std::vector<int>& nums, int idx, bool used_skip, std::vector<int>& cache){

    if(idx + 1 >= nums.size() || (!used_skip && idx + 2 >= nums.size())){
        return true;
    }

    if(cache[idx * 2 + used_skip] != -1) return static_cast<bool>(cache[idx*2 + used_skip]);

    bool use_skip = (!used_skip && nums[idx + 2] < nums[idx] && nums[idx] - nums[idx+2] <= 3) && Is_Valid_Decreasing(nums, idx + 2,true, cache);
    bool take = (nums[idx + 1] < nums[idx] && nums[idx] - nums[idx+1] <= 3) && Is_Valid_Decreasing(nums, idx + 1, used_skip, cache);

    return cache[idx*2 + used_skip] = static_cast<int>(use_skip || take);

}

int main() {

    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    int result = 0;
    for(int i = 0; i < input_data.size(); i++){

        std::vector<int> increasing_cache(input_data[i].size() * 2, -1);
        std::vector<int> decreasing_cache(input_data[i].size() * 2, -1);

        if(Is_Valid_Increasing(input_data[i], 0, false, increasing_cache) || Is_Valid_Decreasing(input_data[i], 0, false, decreasing_cache)){
            result++;
        }else if(Is_Valid_Increasing(input_data[i], 1, true, increasing_cache) || Is_Valid_Decreasing(input_data[i], 1, true, decreasing_cache)){
            result++;
        }
    }

    std::cout<<result<<'\n';

    return 0;
}
