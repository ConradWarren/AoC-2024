#include "../core.h"

int Gen_Nodes(std::vector<std::pair<int, int>>& nodes, std::vector<std::vector<bool>>& marked){
    int result = 0;
    for(int i = 0; i < nodes.size(); i++){
        for(int j = 0; j < nodes.size(); j++){
            if(i == j) continue;
            int y_delta = nodes[j].first - nodes[i].first;
            int x_delta = nodes[j].second - nodes[i].second;
            int ty = nodes[i].first - y_delta;
            int tx = nodes[i].second - x_delta;
            if(tx >= 0 && ty >= 0 && tx < marked[0].size() && ty < marked.size() && !marked[ty][tx]){
                result++;
                marked[ty][tx] = true;
            }
        }
    }
    return result;
}

int main() {
    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);
    std::unordered_map<char, std::vector<std::pair<int, int>>> node_map;
    std::vector<std::vector<bool>> marked(input_data.size(), std::vector<bool>(input_data[0].size(), false));
    for(int i = 0; i < input_data.size(); i++){
        for(int j = 0; j < input_data[i].size(); j++){
            if(input_data[i][j] != '.') node_map[input_data[i][j]].push_back({i, j});
        }
    }
    int result = 0;
    for(auto x : node_map){
        result += Gen_Nodes(x.second, marked);
    }
    std::cout<<result<<'\n';
    return 0;

}
