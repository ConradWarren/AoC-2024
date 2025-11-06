#include "../core.h"

long long Next(long long num){

    long long first = num * 64;
    num ^= first;
    num %= 16777216;

    long long second = num/32;
    num ^= second;
    num %= 16777216;

    long long third = num * 2048;
    num ^= third;
    num %= 16777216;

    return num;
}

void Build_Pattern_Map(std::vector<int>& delta, std::vector<int>& price, int idx, std::unordered_map<int, int>& cache){

    if(idx >= delta.size()){
        return;
    }

    long long hash = (delta[idx-3] << 15) + (delta[idx-2] << 10) | (delta[idx-1] << 5) | delta[idx];

    if(cache.find(hash) == cache.end()){
        cache[hash] = price[idx];
    }

    Build_Pattern_Map(delta, price, idx+1, cache);
}


int main() {

    std::vector<std::vector<long long>> input_data;
    Read_Data("../input.txt", input_data);
    std::vector<std::vector<int>> delta(input_data.size(), std::vector<int>(2000));
    std::vector<std::vector<int>> price(input_data.size(), std::vector<int>(2000));

    int result = 0;
    for(int i = 0; i < input_data.size(); i++){
        long long num = input_data[i][0];
        int last_price = num%10;
        for(int j = 0; j < 2000; j++){
            num = Next(num);
            delta[i][j] = num % 10 - last_price + 10;
            last_price = num%10;
            price[i][j] = num%10;
        }
    }

    std::unordered_map<int, int> global_count;
    std::unordered_map<int, int> local_map;
    for(int i = 0; i < delta.size(); i++){
        Build_Pattern_Map(delta[i], price[i], 3, local_map);

        for(auto& x: local_map){
            global_count[x.first] += x.second;
        }
        local_map.clear();
    }

    for(auto& x: global_count){
        result = std::max(x.second, result);
    }
    std::cout<<result<<'\n';

    return 0;
}
