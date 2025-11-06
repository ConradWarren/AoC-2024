#include "../core.h"

bool Can_Solve(std::vector<long long>& nums, int idx, long long last_valid, long long target){
    
    if(idx >= nums.size()){
        return (target == last_valid);
    }
    
    if(last_valid > target) return false;

    bool add = Can_Solve(nums, idx+1, last_valid + nums[idx], target);
    bool multiply = Can_Solve(nums, idx+1, last_valid * nums[idx], target);
    bool split = Can_Solve(nums, idx+1, last_valid * std::pow(10LL, ((long long)std::log10(nums[idx])+1)) + nums[idx], target);
    
    return add || multiply || split;
}
int main() {
    
    std::vector<std::vector<long long>> input_data;
    Read_Data("../input.txt", input_data);
    long long result = 0;
    
    for(int i = 0; i < input_data.size(); i++){
        if(Can_Solve(input_data[i], 2, input_data[i][1], input_data[i][0])){
            result += input_data[i][0];
        }
    }
    
    std::cout<<result<<'\n';
    
    return 0;
}
