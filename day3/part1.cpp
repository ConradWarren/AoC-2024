#include "core.h"

int Get_Num(std::string& str, int idx){
    bool found_comma = false;
    int first_num = 0;
    int second_num = 0;
    for(int i = idx+4; i < str.size() && str[i] != ')'; i++){
        if(str[i] >= '0' && str[i] <= '9'){
            if(found_comma){
                second_num *= 10;
                second_num += str[i]-'0';
            }else{
                first_num *= 10;
                first_num += str[i]-'0';
            }
        }else if(str[i] == ',' && !found_comma){
            found_comma = true;
        }else{
            return 0;
        }
    }
    if(first_num >= 1000 || second_num >= 1000 || !found_comma) return 0;
    return first_num * second_num;
}
int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    long long result = 0;
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[i].size(); j++){
            if(input_data[i].substr(j, 4) == "mul("){
                result += Get_Num(input_data[i], j);
            }
        }
    }
    std::cout<<result<<'\n';
    return 0;
}
