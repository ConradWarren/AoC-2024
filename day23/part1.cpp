#include "../core.h"

int Count_Sets(const std::vector<std::string>& edges,const std::string& node, std::unordered_map<std::string, std::unordered_set<std::string>>& is_connected_map, std::unordered_set<std::string>& found){

    int result = 0;
    for(int i = 0; i < edges.size(); i++){
        for(int j = i+1; j < edges.size(); j++){
            if(is_connected_map[edges[i]].find(edges[j]) != is_connected_map[edges[i]].end()){

                std::vector<std::string> current_arr = {node, edges[j], edges[i]};
                std::sort(current_arr.begin(), current_arr.end());
                std::string current_str = current_arr[0] + current_arr[1] + current_arr[2];

                if(found.find(current_str) == found.end()){
                    found.insert(current_str);
                    result++;
                }

            }
        }
    }

    return result;
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);


    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, std::unordered_set<std::string>> is_connected_map;

    for(int i = 0; i < input_data.size(); i++){

        std::string str1 = input_data[i].substr(0,2);
        std::string str2 = input_data[i].substr(3, 2);

        graph[str1].push_back(str2);
        graph[str2].push_back(str1);
        is_connected_map[str1].insert(str2);
        is_connected_map[str2].insert(str1);
    }

    int result = 0;
    std::unordered_set<std::string> found_set;
    for(auto& x : graph){
        if(x.first.front() == 't') result += Count_Sets(x.second,x.first, is_connected_map, found_set);
    }
    std::cout<<result<<'\n';

    return 0;
}
