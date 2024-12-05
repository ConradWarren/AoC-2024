#include "core.h"

int Correct_Order(std::vector<int>& nums, std::vector<std::pair<int, int>>& edges){

    std::vector<bool> in_nums(100, false);
    std::vector<int> n_degree(100, 0);
    std::vector<std::vector<int>> graph(100);

    for(int i = 0; i < nums.size(); i++){
        in_nums[nums[i]] = true;
    }

    for(int i = 0; i < edges.size(); i++){
        if(in_nums[edges[i].first] && in_nums[edges[i].second]){
            graph[edges[i].first].push_back(edges[i].second);
            n_degree[edges[i].second]++;
        }
    }

    std::queue<int> node_queue;
    for(int i = 0; i < nums.size(); i++){
        if(n_degree[nums[i]] == 0) node_queue.push(nums[i]);
    }

    std::vector<int> ordered_nums;
    while(!node_queue.empty()){

        int node = node_queue.front();
        node_queue.pop();
        ordered_nums.push_back(node);

        for(int i = 0; i < graph[node].size(); i++){
            if(--n_degree[graph[node][i]] == 0) node_queue.push(graph[node][i]);
        }
    }

    return (ordered_nums == nums) ? 0 : ordered_nums[nums.size()/2];
}

int main() {

    std::vector<std::vector<int>> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::pair<int, int>> edges;

    int idx = 0;
    while(idx < input_data.size() && !input_data[idx].empty()){
        edges.push_back({input_data[idx][0], input_data[idx][1]});
        idx++;
    }

    long long result = 0;
    for(int i = idx+1; i < input_data.size(); i++){
        result += Correct_Order(input_data[i], edges);
    }

    std::cout<<result<<'\n';
    return 0;
}
