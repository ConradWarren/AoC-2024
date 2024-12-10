#include "../core.h"

int main() {
    std::string input_data;
    Read_Data("../input.txt", input_data);
    std::vector<int> ids(2000000, -1);
    std::queue<int> free_spaces;
    int idx = 0;
    int current_id = 0;
    for(int i = 0; i < input_data.size(); i++){
        if(i%2 == 0){
            std::fill(ids.begin()+idx, ids.begin()+idx+input_data[i]-'0', current_id);
            idx += input_data[i] - '0';
            current_id++;
        }else{
            for(int j = idx; j < idx + input_data[i] - '0'; j++){
                free_spaces.push(j);
            }
            idx += input_data[i] - '0';
        }
    }
    for(int i = ids.size()-1; i >= 0 && !free_spaces.empty() && free_spaces.front() < i; i--){
        if(ids[i] != -1){
            ids[free_spaces.front()] = ids[i];
            ids[i] = -1;
            free_spaces.pop();
        }
    }
    long long result = 0;
    for(int i = 0; i < ids.size() && ids[i] != -1; i++){
        result += (long long)i * ids[i];
    }
    std::cout<<result<<'\n';
    return 0;
}
