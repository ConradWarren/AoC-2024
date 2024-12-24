#include "../core.h"

inline bool Can_Add(const std::vector<std::string>& arr, const std::unordered_set<std::string>& is_connected_set){

    for(int i = 0; i < arr.size(); i++){
        if(is_connected_set.find(arr[i]) == is_connected_set.end()) return false;
    }
    return true;
}

void Search_Node(std::vector<std::string>& edges, int idx, std::vector<std::string>& current, std::unordered_map<std::string, std::unordered_set<std::string>>& is_connected_map, std::vector<std::string>& result){

    if(idx >= edges.size()){
        if(current.size() > result.size()) result = current;
        return;
    }

    Search_Node(edges, idx+1, current, is_connected_map, result);

    if(Can_Add(current, is_connected_map[edges[idx]])){
        current.push_back(edges[idx]);
        Search_Node(edges, idx+1, current, is_connected_map, result);
        current.pop_back();
    }

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

    std::vector<std::string> result;
    std::vector<std::string> current;
    for(auto& x : graph){
        current.push_back(x.first);
        Search_Node(x.second, 0, current, is_connected_map, result);
        current.pop_back();
    }

    std::sort(result.begin(), result.end());
    for(int i = 0; i < result.size(); i++){
        std::cout<<result[i]<<',';
    }
    
    return 0;
}
