#include "../core.h"

int main() {
    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<int> nums(input_data.size());
    std::unordered_map<int, int> num_frequency;
    for(int i = 0; i < input_data.size(); i++){
        num_frequency[input_data[i][1]]++;
        nums[i] = input_data[i][0];
    }

    long long result = 0;
    for(int i = 0; i < nums.size(); i++){
        result += static_cast<long long>(num_frequency[nums[i]]) * nums[i];
    }

    std::cout<<result<<'\n';
    return 0;
}
