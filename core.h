#ifndef ADVENT_OF_CODE_2024_CORE_H
#define ADVENT_OF_CODE_2024_CORE_H

#include <iostream> 
#include <vector>
#include <string> 
#include <fstream>
#include <cmath>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <numeric>

template <typename T>
void Print_Vec(const std::vector<T>& vec){

    std::cout<<"{";
    for(int i = 0; i < vec.size(); i++){
        std::cout<<vec[i];
        if(i+1 < vec.size()) std::cout<<", ";
    }
    std::cout<<"}\n";
}

template <typename T>
void Print_Vec(const std::vector<std::vector<T>>& vec){

    for(int i = 0; i < vec.size(); i++){
        Print_Vec(vec[i]);
    }
    std::cout<<"\n";
}

template <typename T>
T String_To_Num(const std::string& str){
	
	T result = 0;

	for(int i = 0; i < str.size(); i++){
		result *= 10;
		result += str[i] - '0';
	}
	
	return result;
}

void Split_String(const std::string& input_str, std::vector<std::string>& result){

    std::string current;

    for(int i = 0; i < input_str.size(); i++){

        bool is_valid = (input_str[i] >= 'a' && input_str[i] <= 'z') || (input_str[i] >= 'A' && input_str[i] <= 'Z');
        if(!is_valid && !current.empty()){
            result.push_back(current);
            current.clear();
        }else if(is_valid){
            current += input_str[i];
        }
    }

    if(!current.empty()){
        result.push_back(current);
    }
}

void Split_String(const std::string& input_str, std::vector<std::string>& result, const std::vector<char>& to_remove){

    bool arr[256];
    std::fill(arr, arr + 256, false);

    for(int i = 0; i < to_remove.size(); i++){
        arr[to_remove[i]] = true;
    }

    std::string current;

    for(int i = 0; i < input_str.size(); i++){

        if(arr[input_str[i]] && !current.empty()){
            result.push_back(current);
            current.clear();
        }else if(!arr[input_str[i]]){
            current += input_str[i];
        }
    }

    if(!current.empty()){
        result.push_back(current);
    }
}
template <typename T>
void Split_Nums(const std::string& input_str, std::vector<T>& result){

	T current = 0;
	bool negative_flag = false;
	bool empty_flag = true;

	for(int i = 0; i < input_str.size(); i++){
		
		if(!empty_flag && (input_str[i] < '0' || input_str[i] > '9')){
			result.push_back((negative_flag) ? -current : current);
			current = 0;
			empty_flag = true;
			negative_flag = false;
		}else if(empty_flag && input_str[i] == '-'){
			negative_flag = true;
			empty_flag = false;
		}else if(input_str[i] >= '0' && input_str[i] <= '9'){
			current *= 10;
			current += input_str[i] - '0';
			empty_flag = false;
		}
	}

	if(!empty_flag){
		result.push_back((negative_flag) ? -current : current);
	}
}

void Read_Data(const std::string& file_path, std::string& result){
	
	std::ifstream file(file_path);
	std::string current;
	
	if(!file.is_open()){
		std::cerr<<"Error: Could not open file"<<std::endl;
	}

	while(std::getline(file, current)){
		result += current;
	}
}

void Read_Data(const std::string& file_path, std::vector<std::string>& result){
	
	std::ifstream file(file_path);
	std::string current;
	
	if(!file.is_open()){
		std::cerr<<"Error: Could not open file"<<std::endl;
	}

	while(std::getline(file, current)){
		result.push_back(current);
	}
}

template <typename T>
void Read_Data(const std::string& file_path, std::vector<T>& result){
	
	std::ifstream file(file_path);

	std::string data;
	std::string current;

	while(std::getline(file, current)){
		data += current + '\n';
	}
	
	Split_Nums(data, result);

	file.close();
}


template <typename T>
void Read_Data(const std::string& file_path, std::vector<std::vector<T>>& result){
	
	std::ifstream file(file_path);

	std::string current;
	
	while(std::getline(file, current)){
		result.push_back({});
		Split_Nums(current, result.back());
	}

	file.close();
}


template <typename T>
void Stream_Nums(std::vector<T>& result){
	
	std::string current;
	std::string data;

	while(std::getline(std::cin, current)){
		data += current + '\n';	
	}
	
	Split_Nums(data, result);
}

template <typename T>
void Stream_Nums(std::vector<std::vector<T>>& result){
	
	std::string current;
	
	while(std::getline(std::cin, current)){
		result.push_back({});
		Split_Nums(current, result.back());
	}
}

#endif
