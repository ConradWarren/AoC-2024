#include "../core.h"

long long Get_Expanded_Count(char last, char current, int depth,std::vector<std::vector<std::string>>& key, std::vector<std::vector<std::vector<long long>>>& cache){

    if(depth == 0){
        return 1;
    }

    if(cache[depth][last][current] != -1){
        return cache[depth][last][current];
    }

    long long result = 0;
    for(int i = 0; i < key[last][current].size(); i++){
        result += Get_Expanded_Count((i == 0) ? 'A' : key[last][current][i-1], key[last][current][i], depth-1, key, cache);
    }

    return cache[depth][last][current] = result;
}


void Get_Min_Length(std::vector<int>& target, int idx, std::vector<std::vector<int>>& key_pad, std::vector<std::vector<std::pair<int, int>>>& dir_pad, int num_y, int num_x, int y, int x, std::map<std::vector<int>, long long>& cache, int cost, std::string& current, std::vector<std::string>& res){

    if(idx >= target.size()){
        if(res.empty() || res.front().size() == current.size()){
            res.push_back(current);
        }else if(res.front().size() > current.size()){
            res.clear();
            res.push_back(current);
        }
        return;
    }

    if(y < 0 || x < 0 || y >= dir_pad.size() || x >= dir_pad[0].size()){
        return;
    }

    if(num_y < 0 ||  num_x < 0 || num_y >= key_pad.size() || num_x >= key_pad[0].size()){
        return;
    }

    if(dir_pad[y][x].first == -1 && dir_pad[y][x].second == -1) return;
    if(key_pad[num_y][num_x] == -1) return;

    if(cache.find({idx, y, x, num_y, num_x}) != cache.end() && cache[{idx, y, x, num_y, num_x}] < cost){
        return;
    }
    cache[{idx, y, x, num_y, num_x}] = cost;

    static std::vector<std::pair<int, int>> directions = {{0,1},{1,0},{0, -1}, {-1,0}};

    current += 'A';
    if(dir_pad[y][x].first == 10 && key_pad[num_y][num_x] == target[idx]){
        Get_Min_Length(target, idx+1, key_pad, dir_pad, num_y, num_x, y, x, cache, cost+1, current, res);

    }else if(dir_pad[y][x].first != 10){
        Get_Min_Length(target, idx, key_pad, dir_pad, num_y + dir_pad[y][x].first, num_x + dir_pad[y][x].second, y, x, cache, cost+1, current, res);
    }
    current.pop_back();
    for(int i = 0; i < directions.size(); i++){

        if(i == 0){
            current += '>';
        }else if(i == 1){
            current += 'v';
        }else if(i == 2){
            current += '<';
        }else if(i == 3){
            current += '^';
        }

        Get_Min_Length(target, idx, key_pad, dir_pad, num_y, num_x, y+directions[i].first, x + directions[i].second, cache, cost+1, current, res);
        current.pop_back();
    }

    return;
}

long long Get_Length(const std::string& str, int depth, std::vector<std::vector<std::string>>& key){

    static std::vector<std::vector<std::vector<long long>>> length_cache(25, std::vector<std::vector<long long>>(256, std::vector<long long>(256, -1)));

    long long length = 0;
    char last = 'A';
    for(int i = 0; i < str.size(); i++){
        length += Get_Expanded_Count(last, str[i], depth, key, length_cache);
        last = str[i];
    }

    return length;
}

int main() {

    std::vector<std::string> input_data;
    Read_Data("../input.txt", input_data);

    std::vector<std::vector<int>> key_pad = {{7,8,9},
                                             {4,5,6},
                                             {1,2,3},
                                             {-1, 0, 10}};
    std::vector<std::vector<std::pair<int, int>>> direction_pad = {{{-1,-1}, {-1, 0}, {10, 10}},
                                                                   {{0, -1},{1,0},{0, 1}} };

    std::vector<std::vector<std::string>> key(256, std::vector<std::string>(256));

    key['^']['A'] = ">A";
    key['^']['<'] = "<vA";
    key['^']['v'] = "vA";
    key['^']['>'] = "v>A";
    key['^']['^'] = "A";

    key['A']['^'] = "<A";
    key['A']['<'] = "v<<A";
    key['A']['v'] = "<vA";
    key['A']['>'] = "vA";
    key['A']['A'] = "A";

    key['<']['^'] = ">^A";
    key['<']['A'] = ">>^A";
    key['<']['v'] = ">A";
    key['<']['>'] = ">>A";
    key['<']['<'] = "A";

    key['v']['^'] = "^A";
    key['v']['A'] = "^>A";
    key['v']['<'] = "<A";
    key['v']['>'] = ">A";
    key['v']['v'] = "A";

    key['>']['^'] = "<^A";
    key['>']['A'] = "^A";
    key['>']['<'] = "<<A";
    key['>']['v'] = "<A";
    key['>']['>'] = "A";

    long long result = 0;

    for(int i = 0; i < input_data.size(); i++){

        std::map<std::vector<int>, long long> cache;
        std::vector<int> target = {input_data[i][0]-'0', input_data[i][1]-'0', input_data[i][2]-'0', 10};

        std::vector<std::string> res;
        std::string current;
        Get_Min_Length(target, 0, key_pad, direction_pad, 3, 2, 0, 2, cache, 0, current, res);

        long long length = (1LL << 60);
        for(int j = 0; j < res.size(); j++){
            long long current_length = Get_Length(res[j], 1, key);
            length = std::min(current_length, length);
        }

        result += (long long)length * std::stoll(input_data[i].substr(0, 3));
    }

    std::cout<<result<<std::endl;


    return 0;
}
