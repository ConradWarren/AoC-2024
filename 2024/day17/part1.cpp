#include "../core.h"

#define A 4
#define B 5
#define C 6

void Run_Program(std::vector<long long> registers, std::vector<int>& nums){
    int idx = 0;
    long long test = registers[A];

    for(int i = 0; i < nums.size(); i += 2){

        if(nums[i] == 0){
            registers[A] = registers[A]/(1 << registers[nums[i+1]]);
        }else if(nums[i] == 1){
            registers[B] ^= nums[i+1];
        }else if(nums[i] == 2){
            registers[B] = registers[nums[i+1]]%8;
        }else if(nums[i] == 3){
            if(registers[A] != 0){
                i = nums[i+1];
                i -= 2;
            }
        }else if(nums[i] == 4){
            registers[B] ^= registers[C];
        }else if(nums[i] == 5){
            std::cout<<registers[nums[i+1]]%8<<',';
        }else if(nums[i] == 6){
            registers[B] = registers[A]/(1 << registers[nums[i+1]]);
        }else if(nums[i] == 7){
            registers[C] = registers[A]/(1 << registers[nums[i+1]]);
        }
    }
}

int main() {

    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<long long> registers = {0,1,2,3,input_data[0][0], input_data[0][1], input_data[0][2]};
    std::vector<int> nums = input_data[4];
    Run_Program(registers, nums);

    return 0;
}
