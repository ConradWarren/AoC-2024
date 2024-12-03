#include "../core.h"

int main() {
    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    int result = 0;
    for(int i = 0; i < input_data.size(); i++){

        if(input_data.size() <= 1){
            result++;
            continue;
        }

        bool is_valid = true;
        bool increasing = (input_data[i][1] > input_data[i][0]);
        int last_valid = input_data[i][0];
        for(int j = 1; j < input_data[i].size() && is_valid; j++){
            if(std::abs(last_valid - input_data[i][j]) > 3) is_valid = false;
            if(increasing && input_data[i][j] <= last_valid) is_valid = false;
            if(!increasing && input_data[i][j] >= last_valid) is_valid = false;
            last_valid = input_data[i][j];
        }

        if(is_valid) result++;
    }

    std::cout<<result<<'\n';
    return 0;
}
