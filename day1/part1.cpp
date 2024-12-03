#include "core.h"

int main() {
    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<int> nums1(input_data.size());
    std::vector<int> nums2(input_data.size());
    for(int i = 0; i < input_data.size(); i++){
        nums1[i] = input_data[i][0];
        nums2[i] = input_data[i][1];
    }

    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());

    long long result = 0;
    for(int i = 0; i < nums1.size(); i++){
        result += std::abs(nums1[i] - nums2[i]);
    }
    std::cout<<result<<'\n';
    return 0;
}
