#include "../core.h"

int hash(const std::string& str){
	
	int current = 0; 
	for(int i = 0; i < str.size() && str[i] != '-' && str[i] != '='; i++){
		current += str[i]; 
		current *= 17; 
		current %= 256;
	}

	return current; 
}


int main(void){

	std::string input = core::Read_Data<std::string>("input.txt");

	std::vector<std::string> sequences = core::Split_String(input, {',', '\n'}); 
	std::unordered_map<std::string, std::pair<int, int>> lable_value_map;
	
	for(int i = 0; i < sequences.size(); i++){
		
		int box_id = hash(sequences[i]);
		std::string lable = (sequences[i].back() == '-') ? std::string(sequences[i].begin(), sequences[i].end()-1) :std::string(sequences[i].begin(), sequences[i].end()-2); 
		auto itr = lable_value_map.find(lable); 	
		
		if(sequences[i].back() == '-' && itr != lable_value_map.end()){
			lable_value_map.erase(lable);
		}else if(sequences[i].back() != '-' && itr == lable_value_map.end()){
			lable_value_map[lable] = {sequences[i].back() - '0', i};
		}else if(sequences[i].back() != '-'){
			itr->second.first = sequences[i].back() - '0'; 
		}
	}

	std::vector<std::vector<std::pair<int, int>>> boxes(256); 
	for(auto& lense : lable_value_map){
		int box_id = hash(lense.first); 
		boxes[box_id].push_back({lense.second.second, lense.second.first}); 
	}

	long long result = 0;
	for(int j = 0; j < boxes.size(); j++){
		
		if(boxes[j].empty()) continue; 

		std::sort(boxes[j].begin(), boxes[j].end()); 
		for(int i = 0; i < boxes[j].size(); i++){
			result += boxes[j][i].second * (i + 1) * (j+1); 		
		}
	}
	std::cout<<result<<'\n';
	return 0;
}
