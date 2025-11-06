#include "../core.h"

long long Count(std::string& target, std::vector<std::string>& towels, int idx, std::vector<long long>& cache){

    if(idx == target.size()){
        return 1;
    }

    if(cache[idx] != -1){
        return cache[idx];
    }

    long long result = 0;
    for(int i = 0; i < towels.size(); i++){

        if(towels[i] == target.substr(idx, towels[i].size())){
            result += Count(target, towels, idx + towels[i].size(), cache);
        }

    }
    return cache[idx] = result;
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::string> towels;
    Split_String(input_data.front(), towels);

    long long result = 0;
    for(int i = 2; i < input_data.size(); i++){

        std::vector<long long> cache(input_data[i].size(), -1);
        result += Count(input_data[i], towels, 0, cache);

    }

    std::cout<<result<<'\n';

    return 0;
}
