#include "../core.h"

int Eval(std::unordered_map<std::string, std::vector<std::string>>& operation_map, std::unordered_map<std::string, int>& value_map,const std::string& str){

    if(value_map.find(str) != value_map.end()){
        return value_map[str];
    }

    std::string reg_1 = operation_map[str][0];
    std::string reg_2 = operation_map[str][2];
    std::string op = operation_map[str][1];

    int val_1 = Eval(operation_map, value_map, reg_1);
    int val_2 = Eval(operation_map, value_map, reg_2);

    if(op == "AND"){
        return (val_1 & val_2);
    }
    if(op == "OR"){
        return (val_1 | val_2);
    }
    if(op == "XOR"){
        return (val_1 ^ val_2);
    }

    return -1;
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    int idx = 0;
    std::unordered_map<std::string, int> values;

    long long x = 0;
    long long y = 0;
    while (idx < input_data.size() && !input_data[idx].empty()){

        if(input_data[idx].front() == 'x' && input_data[idx].back() == '1'){
            x |= (1LL << std::stoi(input_data[idx].substr(1,2)));
        }else if(input_data[idx].front() == 'y' && input_data[idx].back() == '1'){
            y |= (1LL << std::stoi(input_data[idx].substr(1,2)));
        }

        values[input_data[idx].substr(0, 3)] = (std::stoi(input_data[idx].substr(5)));
        idx++;
    }

    long long target = x + y;

    idx++;
    std::unordered_map<std::string, std::vector<std::string>> reverse_op_map;

    while(idx < input_data.size()){
        std::vector<std::string> operation;
        Split_String(input_data[idx], operation, {' ','-','>'});
        reverse_op_map[operation[3]] = {operation[0], operation[1], operation[2]};
        idx++;
    }

    long long result = 0;
    for(int i = 0; i <= 45; i++){

        if(i < 10){
            if(Eval(reverse_op_map, values, "z0" + std::to_string(i)) == 1) result |= (1LL << i);
        }else{
            if(Eval(reverse_op_map, values, "z" + std::to_string(i)) == 1) result |= (1LL << i);
        }
        if((target & (1LL << i)) != (result & (1LL << i))){
            std::cout<<"fails at i = "<<i<<'\n';
        }
    }


    return 0;
}
