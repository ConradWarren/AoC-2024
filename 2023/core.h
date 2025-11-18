#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <type_traits>
#include <fstream>
#include <climits>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <utility>
#include <array>
#include <cassert>
#include <iterator> 
#include <tuple> 

namespace core{
	
	template <typename T>
	T LCM(T a, T b){
		return (a*b)/std::gcd(a,b);
	}
	
	template <typename T>
	std::vector<T> Prime_Factorization(T num){
		
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		
		std::vector<T> result;
		while(num%2 == 0){
			result.emplace_back(2);
			num /= 2;
		}
			

		T idx = 3;

		while(idx * idx <= num){
			
			while(num%idx == 0){
				result.emplace_back(idx);
				num /= idx;
			}
			idx += 2;
		}
		
		if(num != 1) result.emplace_back(num);

		return result;
	}
	
	template <typename T>
	constexpr T Pow_Const(T base, T exp, T mod){
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		if(exp == 0) return 1;
		if(exp%2 == 1){
			return (base * Pow_Const(base, exp-1, mod))%mod;
		}
		return Pow_Const((base * base)%mod, exp/2, mod)%mod;
	}
	
	template <typename T>
	constexpr T Pow_Const(T base, T exp){
		static_assert(std::is_integral<T>::value, "T must be an integral type");
		if(exp == 0) return 1;
		
		if(exp%2 == 1){
			return (base * Pow_Const(base, exp-1));
		}	
		
		return Pow_Const(base * base, exp/2);
	}

	template <typename T>
	constexpr T Sqrt_Const(T num){
		
		if constexpr (std::is_same_v<T, bool>) return num;
			
		static_assert(std::is_integral<T>::value && std::is_unsigned_v<T>,  "T must be a unsigned integral type");
		
		if(num == 0) return 0;
		
		constexpr T max_sqrt = (static_cast<T>(1) << (std::numeric_limits<T>::digits/2))-1; 

		T low = 0;
		T high = std::min(num, max_sqrt);

		while(low < high){
			
			T mid = (low + high)/2;

			if(mid * mid > num){
				high = mid;
			}else{
				low = mid+1;
			}
		}

		return low-1;
	}
	
	std::vector<bool> Prime_Sieve(size_t upper_bound){
		
		std::vector<bool> is_prime(upper_bound+1, true);
		
		is_prime[0] = false;
		is_prime[1] = false;
	
		for(size_t i = 1; i * i <= upper_bound; i++){
			if(!is_prime[i]) continue;
			for(size_t j = i * i; j <= upper_bound; j += i){
				is_prime[j] = false;
			}
		} 
		
		return is_prime;
	}
	
	template <std::size_t T>
	constexpr std::array<bool, T> Prime_Sieve_Const(){
		
		std::array<bool, T> is_prime;
		std::fill(is_prime.begin(), is_prime.end(), true);

		is_prime[0] = false;
		is_prime[1] = false;

		for(std::size_t i = 2; i * i < T; i++){
			if(!is_prime[i]) continue;
			for(std::size_t j = i * i; j < T; j += i){
				is_prime[j] = false;
			}
		}
		
		return is_prime;
	}
	
	template <std::size_t T>
	void Prime_Sieve_Global(std::array<bool, T>& is_prime_global){
		
		std::fill(is_prime_global.begin(), is_prime_global.end(), true);

		is_prime_global[0] = false;
		is_prime_global[1] = false;

		for(std::size_t i = 2; i * i < T; i++){
			if(!is_prime_global[i]) continue;
			for(std::size_t j = i * i; j < T; j += i){
				is_prime_global[j] = false;
			}
		}		
	}

	template <typename T>
	T Split_Nums(const std::string& str){
		
		T result;
		std::string current;
		for(int i = 0; i < str.size(); i++){
			
			if(current.empty() && str[i] == '-'){
				current += '-';
			}else if(!current.empty() && (str[i] < '0' || str[i] > '9')){
				result.emplace_back(std::stoll(current));
				current.clear();
			}else if(str[i] >= '0' && str[i] <= '9'){
				current += str[i];
			}
		}

		if(!current.empty()){
			result.emplace_back(std::stoll(current));
		}

		return result;
	}

	std::vector<std::string> Split_String(const std::string& str, const std::vector<char>& to_remove){
		
		bool to_remove_arr[256];
		std::fill(to_remove_arr, to_remove_arr + 256, false);

		for(int i = 0; i < to_remove.size(); i++){
			to_remove_arr[to_remove[i]] = true;
		}

		std::string current;
		std::vector<std::string> result;

		for(int i = 0; i < str.size(); i++){

			if(to_remove_arr[str[i]] && !current.empty()){
				result.push_back(current);
				current.clear();
			}else if(!to_remove_arr[str[i]]){
				current += str[i];
			}
		}
		
		if(!current.empty()) result.push_back(current);

		return result;
	}
	
	template <typename T>
	T Read_Data(const std::string& file_path){

		std::ifstream file(file_path);

		if(!file.is_open()){
			std::cerr<<"Error: Could not open file"<<std::endl;
			return {};
		}
		
		
		if constexpr (std::is_same_v<T, std::vector<std::string>>){

			T result;
			std::string current;
			while(std::getline(file, current)){
				result.emplace_back(current);
			}

			return result;
		}

		if constexpr (std::is_same_v<T, std::string>){
			T result;
			std::string current;
			while(std::getline(file, current)){
				result += current;
				result += "\n";
			}
			result.pop_back();
			return result;
		}

		if constexpr (std::is_same_v<T, std::vector<std::vector<int>>>){

			T result;
			std::string current;
			while(std::getline(file, current)){
				result.emplace_back(Split_Nums<std::vector<int>>(current));
			}
			return result;
		}
		if constexpr (std::is_same_v<T, std::vector<std::vector<long long>>>){

			T result;
			std::string current;
			while(std::getline(file, current)){
				result.emplace_back(Split_Nums<std::vector<long long>>(current));
			}
			return result;
		} 
		
		if constexpr (std::is_same_v<T, std::vector<int>> || std::is_same_v<T, std::vector<long long>>){
			
			std::string str;
			std::string current;
			while(std::getline(file, current)){
				str += current;
			}
			return Split_Nums<T>(str);
		}
	}	
}

