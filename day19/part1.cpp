#include "../core.h"

bool Is_Possible(std::string& target, std::vector<std::string>& towels, int idx, std::vector<int>& cache){

    if(idx == target.size()){
        return true;
    }

    if(cache[idx] != -1){
        return cache[idx];
    }


    for(int i = 0; i < towels.size(); i++){

        if(towels[i] == target.substr(idx, towels[i].size()) && Is_Possible(target, towels, idx+towels[i].size(), cache)){
            return cache[idx] = true;
        }

    }
    return cache[idx] = false;
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::string> towels;
    Split_String(input_data.front(), towels);

    int result = 0;
    for(int i = 2; i < input_data.size(); i++){

        std::vector<int> cache(input_data[i].size(), -1);
        if(Is_Possible(input_data[i], towels, 0, cache)) result++;
    }

    std::cout<<result<<'\n';

    return 0;
}
