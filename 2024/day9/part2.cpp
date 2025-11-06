#include "../core.h"

int main() {

    std::string input_data;
    Read_Data("../input.txt", input_data);

    std::vector<int> ids(2000000, -1);
    std::vector<std::vector<int>> segments;

    int idx = 0;
    int current_id = 0;
    for(int i = 0; i < input_data.size(); i++){

        if(i%2 == 0){
            std::fill(ids.begin()+idx, ids.begin() + idx + input_data[i]-'0', current_id);
            segments.push_back({idx, input_data[i]-'0', current_id});
            idx += input_data[i] - '0';
            current_id++;
        }else{
            idx += input_data[i] - '0';
        }
    }

    for(int i = segments.size()-1; i >= 0; i--){

        int free_count = 0;
        int target = -1;
        for(int j = 0; j < segments[i][0] && target == -1; j++){

            if(ids[j] == -1) free_count++;
            else free_count = 0;

            if(free_count == segments[i][1]) target = j - segments[i][1] + 1;
        }

        if(target != -1){
            std::fill(ids.begin()+target, ids.begin()+target+segments[i][1], segments[i][2]);
            std::fill(ids.begin()+segments[i][0], ids.begin()+segments[i][0]+segments[i][1], -1);
        }
    }

    long long result = 0;
    for(int i = 0; i < ids.size(); i++){
        if(ids[i] != -1) result += (long long)i * ids[i];
    }

    std::cout<<result<<'\n';
    return 0;
}
