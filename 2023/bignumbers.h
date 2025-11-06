#pragma once
#include <limits>
#include <array>
#include <iostream>
#include <cstddef>
#include <algorithm>

namespace bnl{
	
	template <std::size_t N>
	class UINT{

		static_assert(N > 0, "bnl::UINT<N> cannot be zero bits");
		private:
			static constexpr std::size_t bit_count = sizeof(std::size_t) * 8;
			static constexpr std::size_t array_size = (N%bit_count == 0) ? N/bit_count : N/bit_count + 1;
			static constexpr std::size_t last_bit_mask = (N%bit_count == 0) ? std::numeric_limits<std::size_t>::max() : (1ULL << (N%bit_count)) - 1;  
			std::array<std::size_t, array_size> bits;
		public:
			UINT() : bits{}{
				
			}
			
			UINT(std::size_t x) : bits{}{
				bits[0] = x;
				if constexpr (N < bit_count) bits[0] &= last_bit_mask;
			}

			UINT(const std::array<std::size_t, array_size>& input_arr) : bits(input_arr){}
			
			template<std::size_t U> 
			friend class UINT;
	
			template<std::size_t U>
			UINT(const UINT<U>& input){
					
				if constexpr (U >= N){
					std::copy(input.bits.begin(), input.bits.begin() + array_size, bits.begin());	
					bits[array_size-1] &= last_bit_mask;
				}else{
					std::fill(bits.begin() + input.array_size, bits.end(), 0ULL);
					std::copy(input.bits.begin(), input.bits.end(), bits.begin());
				}
			}

			UINT<N> operator+(std::size_t x) const{
				
				std::array<std::size_t, array_size> result{};
				bool carry = std::numeric_limits<std::size_t>::max() - x < bits[0];
				
				result[0] = bits[0] + x;

				for(std::size_t i = 1; i < array_size; i++){	
					result[i] = bits[i] + (carry ? 1 : 0);
					carry = carry && bits[i] == std::numeric_limits<std::size_t>::max();
				}
				
				result[array_size-1] &= last_bit_mask;
				return result;
			}
			
			UINT<N> operator+(const UINT<N>& x) const{
				
				std::array<std::size_t, array_size> result{};
				bool carry = false;

				for(std::size_t i = 0; i < array_size; i++){
					std::size_t diff = std::numeric_limits<std::size_t>::max() - x.bits[i];
					bool next_carry = (diff < bits[i]) || (carry && (diff == bits[i]));
					result[i] = bits[i] + x.bits[i] + (carry ? std::size_t(1) : std::size_t(0));		
					carry = next_carry;
				}
				result[array_size-1] &= last_bit_mask;

				return UINT<N>(result);	
			}

			UINT<N> operator*(std::size_t x) const{
				
				constexpr std::size_t split_idx = sizeof(std::size_t)*4;
				constexpr std::size_t split_mask = std::numeric_limits<std::size_t>::max() >> split_idx;

				std::array<std::size_t, array_size> result{};
				std::array<std::size_t, 4> overflow{};
				std::array<std::size_t, 3> to_add{};
				
				for(std::size_t i = 0; i < array_size; i++){
					
					std::size_t next_carry = 0;
					for(std::size_t z = 0; z < overflow.size(); z++){
						if(std::numeric_limits<std::size_t>::max() - overflow[z] < result[i]) next_carry++;
						result[i] += overflow[z];
					}
					
					std::size_t lower_lower_mask = (x & split_mask) * (bits[i] & split_mask);
					std::size_t lower_upper_mask = (x & split_mask) * (bits[i] >> split_idx);
					std::size_t upper_lower_mask = (x >> split_idx) * (bits[i] & split_mask);
					std::size_t upper_upper_mask = (x >> split_idx) * (bits[i] >> split_idx);
				
					to_add[0] = lower_lower_mask;
					to_add[1] = (lower_upper_mask & split_mask) << split_idx;
					to_add[2] = (upper_lower_mask & split_mask) << split_idx;
					
					for(std::size_t z = 0; z < to_add.size(); z++){
						if(std::numeric_limits<std::size_t>::max() - to_add[z] < result[i]) next_carry++;
						result[i] += to_add[z];
					}

					overflow[0] = upper_upper_mask;
					overflow[1] = lower_upper_mask >> split_idx;
					overflow[2] = upper_lower_mask >> split_idx;
					overflow[3] = next_carry;
				}

				return UINT<N>(result);
			}

			UINT<N> operator*(const UINT<N>& x) const{
				
				
				constexpr std::size_t split_idx = sizeof(std::size_t)*4;
				constexpr std::size_t split_mask = std::numeric_limits<std::size_t>::max() >> split_idx;

				std::array<std::size_t, array_size> result{};
				

				for(std::size_t j = 0; j < array_size; j++){
					
					std::array<std::size_t, 4> overflow{};
					std::array<std::size_t, 3> to_add{};

					for(std::size_t i = 0; i + j < array_size; i++){
						
						std::size_t next_carry = 0;
						for(std::size_t z = 0; z < overflow.size(); z++){
							if(std::numeric_limits<std::size_t>::max() - overflow[z] < result[i+j]) next_carry++;
							result[i + j] += overflow[z];
						}

						std::size_t lower_lower_mask = (x.bits[j] & split_mask) * (bits[i] & split_mask);
						std::size_t lower_upper_mask = (x.bits[j] & split_mask) * (bits[i] >> split_idx);
						std::size_t upper_lower_mask = (x.bits[j] >> split_idx) * (bits[i] & split_mask);
						std::size_t upper_upper_mask = (x.bits[j] >> split_idx) * (bits[i] >> split_idx);

						to_add[0] = lower_lower_mask;
						to_add[1] = (lower_upper_mask & split_mask) << split_idx;
						to_add[2] = (upper_lower_mask & split_mask) << split_idx;
						
						for(std::size_t z = 0; z < to_add.size(); z++){
							if(std::numeric_limits<std::size_t>::max() - to_add[z] < result[i + j]) next_carry++;
							result[i + j] += to_add[z];
						}
						
						overflow[0] = upper_upper_mask;
						overflow[1] = lower_upper_mask >> split_idx;
						overflow[2] = upper_lower_mask >> split_idx;
						overflow[3] = next_carry;
					}
				}
				
				result[array_size-1] &= last_bit_mask;
				return UINT<N>(result);
			}

			UINT<N> operator-(std::size_t x) const{
					
				if(x == 0) return *this; 
				
				std::array<std::size_t, array_size> result{};
				
				bool carry = (std::numeric_limits<std::size_t>::max() - (~x + 1) < bits[0]); 
				result[0] = (~x + 1) + bits[0];	
				
				for(std::size_t i = 1; i < array_size; i++){
					result[i] = bits[i] - (carry ? 0 : 1);
					carry = (carry || bits[i]);
				}	

				result[array_size-1] &= last_bit_mask;
				return UINT<N>(result);
			}

			UINT<N> operator-(UINT<N> x) const{
				
				std::array<std::size_t, array_size> result{};
				bool carry = false;
				bool complement_carry = true;

				for(std::size_t i = 0; i < array_size; i++){
					
					std::size_t x_complement = ~x.bits[i];
					if(complement_carry && x_complement == std::numeric_limits<std::size_t>::max()){
						x_complement = 0;
					}else if(complement_carry){
						x_complement++;
						complement_carry = false;
					}
	
					result[i] = bits[i] + x_complement + (carry ? 1 : 0);	
					
					std::size_t diff = std::numeric_limits<std::size_t>::max() - x_complement;
					carry = (diff < bits[i]) || (carry && diff == bits[i]);	
				}
				
				result[array_size-1] &= last_bit_mask;
				return UINT<N>(result);
			}
			
			UINT<N> operator/(std::size_t x) const{


				constexpr std::size_t msb_mask = std::size_t(1) << (bit_count-1);
				std::array<std::size_t, array_size> result{};
				
				if(x == 0){
					std::fill(result.begin(), result.end(), std::numeric_limits<std::size_t>::max());			
					return UINT<N>(result);
				}

				std::size_t remainder = 0;
				
				for(std::size_t i = array_size; i-- > 0;){
					for(std::size_t j = bit_count; j-- > 0;){
						bool overflow = (remainder & msb_mask);
						remainder = (remainder << 1) | ((bits[i] >> j) & 1);	
						if(overflow || remainder >= x){
							result[i] |= (std::size_t(1) << j);
							remainder -= x;
						}
					}	
				}	
				
				return UINT<N>(result);
			}

			UINT<N> operator/(const UINT<N>& x) const{
				
				std::array<std::size_t, array_size> result{};
				UINT<N> remainder(0);	
				
				for(std::size_t i = array_size; i-- > 0; ){
					
					for(std::size_t j = bit_count; j-- > 0; ){
						
						remainder = (remainder << 1);
						if((bits[i] >> j) & 1) remainder = (remainder | 1);
						
						if(remainder >= x){
							remainder = remainder - x;
							result[i] |= (1ULL << j);
						}
					}
				}
				
				return UINT<N>(result);
			}

			std::size_t operator%(std::size_t mod) const{
				
				constexpr std::size_t msb_mask = static_cast<std::size_t>(1) << (bit_count-1);
				std::size_t remainder = 0;

				for(std::size_t i = array_size; i-- > 0; ){
					for(std::size_t j = bit_count; j-- > 0;){
						
						bool overflow = msb_mask & remainder;	
						remainder = (remainder << 1) | ((bits[i] >> j) & 1);
						if(remainder >= mod || overflow){
							remainder -= mod;
						}
					}
				}
				return remainder;
			}
			
			UINT<N> operator%(UINT<N> mod) const{
				
				UINT<N> remainder(0);

				for(std::size_t i = array_size; i-- > 0;){	
					for(std::size_t j = bit_count; j-- > 0;){	
						remainder = (remainder << 1) | ((bits[i] >> j) & 1);
						if(remainder >= mod){
							remainder = remainder - mod;
						}
					}
				}
				return remainder;
			}

			UINT<N> operator<<(std::size_t x) const{
			
				std::array<std::size_t, array_size> result{};
				
				std::size_t idx = x%bit_count;
				std::size_t lsb_mask = ((1ULL << idx)-1) << (bit_count - idx);

				for(std::size_t i = 0; i < array_size; i++){
					
					if(i >= 1 + x/bit_count) result[i] |= (bits[i-(1+x/bit_count)] & lsb_mask) >> (bit_count-idx);
					if(i >= x/bit_count) result[i] |= bits[i - x/bit_count] << idx;
				}

				result[array_size-1] &= last_bit_mask;
				return UINT<N>(result);
			}
			UINT<N> operator>>(std::size_t x) const{
				
				std::array<std::size_t, array_size> result{};
				
				std::size_t idx = x%bit_count;
				std::size_t msb_mask = (1ULL << idx)-1;
				for(std::size_t i = 0; i < array_size; i++){	
					if(i + (x/bit_count) + 1 < array_size) result[i] |= (bits[i+x/bit_count+1] & msb_mask) << (bit_count - idx);
					if(i + (x/bit_count) < array_size) result[i] |= (bits[i+x/bit_count] >> idx);
				}
					
				return UINT<N>(result);
			}

			UINT<N> operator|(const UINT<N>& x) const{
				
				std::array<std::size_t, array_size> result;
				for(std::size_t i = 0; i < array_size; i++){
					result[i] = bits[i] | x.bits[i];
				}

				return UINT<N>(result);
			}

			UINT<N> operator|(std::size_t x) const{
				
				std::array<std::size_t, array_size> result = bits;
				result[0] |= x;
				
				if constexpr (N < bit_count) { result[0] &= last_bit_mask;}	
				return UINT<N>(result);
			}
			
			UINT<N> operator^(const UINT<N>& x)const{
				
				std::array<std::size_t, array_size> result;
				
				for(std::size_t i = 0; i < array_size; i++){
					result[i] = bits[i] ^ x.bits[i];
				}
				if constexpr (N < bit_count) {result[0] &= last_bit_mask;}
				
				return UINT<N>(result);
			}
			
			UINT<N> operator&(const UINT<N>& x) const{

				std::array<std::size_t, array_size> result;
				for(std::size_t i = 0; i < array_size; i++){
					result[i] = bits[i] & x.bits[i];	
				}
				return UINT<N>(result);
			}	
			

			UINT<N>& operator=(std::size_t x){
				std::fill(bits.begin(), bits.end(), 0ULL);
				bits[0] = x;
				if constexpr (N < bit_count) {bits[0] &= last_bit_mask;}
				return *this;
			}
			
			UINT<N>& operator+=(const UINT<N>& x){
				bool carry = false;	
				for(std::size_t i = 0; i < array_size; i++){		
					std::size_t diff = std::numeric_limits<std::size_t>::max() - x.bits[i];
					bool next_carry = (diff < bits[i] || (carry && diff == bits[i]));		
					bits[i] += x.bits[i] + (carry ? std::size_t(1) : std::size_t(0));
					carry = next_carry;
				}
				bits[array_size-1] &= last_bit_mask;
				return *this;
			}

			UINT<N>& operator-=(const UINT<N>& x){

				bool carry = false;
				bool complement_carry = true;
				for(std::size_t i = 0; i < array_size; i++){
					
					std::size_t x_complement = ~x.bits[i];
					if(complement_carry && x_complement == std::numeric_limits<std::size_t>::max()){
						x_complement = 0;
					}else if(complement_carry){
						complement_carry = false;
						x_complement++;
					}
					std::size_t diff = std::numeric_limits<std::size_t>::max() - x_complement;

					bool next_carry = (diff < bits[i]) || (carry && diff == bits[i]);
						
					bits[i] += x_complement + (carry ? 1 : 0);
					
					carry = next_carry;
				}
				
				bits[array_size-1] &= last_bit_mask;
				return *this;
			}
			
			UINT<N>& operator*=(const UINT<N>& x){
				
				constexpr std::size_t split_idx = sizeof(std::size_t)*4;
				constexpr std::size_t split_mask = (std::size_t(1) << split_idx)-1;
				
				int idx = 63;
			
				std::array<std::size_t, array_size> next_bits{};
				
				for(std::size_t j = 0; j < array_size; j++){
					
					std::array<std::size_t, 4> overflow{};	
					std::array<std::size_t, 3> to_add{};

					for(std::size_t i = 0; i + j < array_size; i++){
						
						std::size_t next_carry = 0;
						
						for(int z = 0; z < overflow.size(); z++){
							if(std::numeric_limits<std::size_t>::max() - overflow[z] < next_bits[i+j]) next_carry++;
							next_bits[i + j] += overflow[z];
						}
						
						
						std::size_t lower_lower_mask = (x.bits[j] & split_mask) * (bits[i] & split_mask);
						std::size_t lower_upper_mask = (x.bits[j] & split_mask) * (bits[i] >> split_idx);
						std::size_t upper_lower_mask = (x.bits[j] >> split_idx) * (bits[i] & split_mask); 
						std::size_t upper_upper_mask = (x.bits[j] >> split_idx) * (bits[i] >> split_idx);							
						
						to_add[0] = lower_lower_mask;
						to_add[1] = (lower_upper_mask & split_mask) << split_idx;
						to_add[2] = (upper_lower_mask & split_mask) << split_idx;
						
						for(int z = 0; z < to_add.size(); z++){
							if(std::numeric_limits<std::size_t>::max() - to_add[z] < next_bits[i + j]) next_carry++;
							next_bits[i+j] += to_add[z];
						}

						overflow[0] = (lower_upper_mask >> split_idx);
						overflow[1] = (upper_lower_mask >> split_idx);
						overflow[2] = upper_upper_mask;
						overflow[3] = next_carry;
					} 
				}

				next_bits[array_size-1] &= last_bit_mask;	
				bits = next_bits;
				return *this;
			}

			UINT<N>& operator/=(const UINT<N>& x){
			
				UINT<N> remainder{};
				for(std::size_t i = array_size; i-- > 0;){
					for(std::size_t j = bit_count; j-- > 0;){
						
						remainder = (remainder << 1) | (bits[i] >> j & 1);
							
						if(remainder >= x){
							bits[i] |= (std::size_t(1) << j);
							remainder = remainder - x;
						}else if((bits[i] >> j & 1)){
							bits[i] ^= (std::size_t(1) << j);
						}	
					}	
				}		
				return *this;
			}

			bool operator>(std::size_t x) const{
				for(std::size_t i = array_size; i-- > 1;){
					if(bits[i] > 0) return true;
				}
				return (bits[0] > x);
			}
			bool operator>=(std::size_t x) const{
				for(std::size_t i = array_size; i-- > 1;){
					if(bits[i] > 0) return true;
				}
				return (bits[0] >= x);
			}
			bool operator<(std::size_t x) const{
				for(std::size_t i = array_size; i-- > 1;){
					if(bits[i] > 0) return false;
				}
				return (bits[0] < x);
			}
			bool operator<=(std::size_t x) const{
				for(std::size_t i = array_size; i-- > 1;){
					if(bits[i] > 0) return false;
				}
				return (bits[0] <= x);
			}
			
			bool operator>(const UINT<N>& x) const{
				for(std::size_t i = array_size; i-- > 0;){
					if(bits[i] != x.bits[i]) return bits[i] > x.bits[i];
				}
				return false;
			}
			bool operator>=(const UINT<N>& x) const{
				for(std::size_t i = array_size; i-- > 0;){
					if(bits[i] != x.bits[i]) return bits[i] > x.bits[i];

				}
				return true;
			}
			bool operator<(const UINT<N>& x) const{
				for(std::size_t i = array_size; i-- > 0;){
					if(bits[i] != x.bits[i]) return bits[i] < x.bits[i]; 
				}
				return false;
			}
			bool operator<=(const UINT<N>& x) const{
				for(std::size_t i = array_size; i-- > 0;){
					if(bits[i] != x.bits[i]) return bits[i] < x.bits[i];
				}
				return true;
			}
			bool operator==(const UINT<N>& x) const{
				
				for(std::size_t i = 0; i < array_size; i++){
					if(bits[i] != x.bits[i]) return false;
				}	
				return true;
			}

			bool operator!=(const UINT<N>& x) const{
				for(std::size_t i = 0; i < array_size; i++){
					if(bits[i] != x.bits[i]) return true;
				}
				return false;
			}
				
			friend std::ostream& operator<<(std::ostream& os, const UINT<N>& obj){
				
				constexpr std::size_t max_digits = N/3 + 1;
				std::array<char, max_digits> digits{};

				bnl::UINT<N> current = obj;
				std::size_t idx = max_digits - 1;

				while(current > 0){
					digits[idx] = '0' + (current%10);
					current = current/10;
					idx--;
				}
				
				if(idx == max_digits - 1){
					os << "0";
				}else{
					os << std::string(digits.end()-(max_digits-1 - idx), digits.end());
				}
		
				return os;
			}
	};
	
	 
	
	template <std::size_t N>
	UINT<N> gcd(UINT<N> a, UINT<N> b){
		
		while(b > 0){
			std::swap(a,b);
			b = b%a;
		}
		
		return a;
	}
};
