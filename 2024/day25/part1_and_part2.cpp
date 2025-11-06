#include "../core.h"

std::vector<int> Build_Key(const std::vector<std::string>& key){

    std::vector<int> result(key[0].size(), -1);
    for(int i = 0; i < key[0].size(); i++){
        for(int j = (int)key.size()-1; j >= 0 && key[j][i] == '#'; j--){
            result[i]++;
        }
    }

    return result;
}

std::vector<int> Build_Lock(const std::vector<std::string>& lock){

    std::vector<int> result(lock[0].size(), -1);

    for(int i = 0; i < lock[0].size(); i++){
        for(int j = 0; j < lock.size() && lock[j][i] == '#'; j++){
            result[i]++;
        }
    }

    return result;
}

int Count(std::vector<std::vector<int>>& locks, std::vector<int>& key, int idx){

    if(idx >= locks.size()){
        return 0;
    }

    int result = 0;
    bool is_valid = true;
    for(int i = 0; i < key.size() && is_valid; i++){
        is_valid = (locks[idx][i] + key[i] <= 5);
    }
    if(is_valid) result++;

    result += Count(locks, key, idx+1);
    return result;
}


int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);


    std::vector<std::vector<int>> locks;
    std::vector<std::vector<int>> keys;

    int idx = 0;
    while(idx < input_data.size()){

        std::vector<std::string> current;
        while(idx < input_data.size() && !input_data[idx].empty()){
            current.push_back(input_data[idx]);
            idx++;
        }
        idx++;

        if(current[0][0] == '.') keys.push_back(Build_Key(current));
        else locks.push_back(Build_Lock(current));
    }

    int result = 0;
    for(int i = 0; i < keys.size(); i++){
        result += Count(locks, keys[i], 0);
    }
    std::cout<<result<<'\n';

    return 0;
}
