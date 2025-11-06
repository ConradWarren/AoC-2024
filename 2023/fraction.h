#pragma once
#include <iostream>
#include <numeric>
#include <type_traits>
#include <stdexcept>
#include <utility>

namespace frac{

template <typename T>
class fraction{

private:
	
	T _numerator;
	T _denominator;

	void normalize(){
		
		if(_numerator == 0){
			_denominator = 1;
			return;
		} 

		T gcd = this->gcd(_numerator, _denominator);
		
		_numerator /= gcd;
		_denominator /= gcd;

		if(_denominator < 0){
			_numerator *= -1;
			_denominator *= -1;
		}
	}
			
	T gcd(T a, T b){
		while(b > 0){
			std::swap(a,b);
			b = b%a;
		}	
		return a;
	}


public:
	
	fraction() : _numerator(0) , _denominator(1){}
	fraction(const std::pair<T, T>& _num) : _numerator(_num.first), _denominator(_num.second) {
		if(_denominator == 0) throw std::invalid_argument("Denominator cannot be zero");
		normalize();
	}
	fraction(T numerator, T denominator) : _numerator(numerator), _denominator(denominator) {
		if(denominator == 0) throw std::invalid_argument("Denominator cannot be zero");
		normalize();
	}
	fraction(T num) : _numerator(num), _denominator(static_cast<T>(1)) {}

	template<typename U>
	fraction(const fraction<U>& input) : _numerator(static_cast<T>(input.numerator())), _denominator(static_cast<T>(input.denominator())) {
		static_assert(std::is_convertible_v<U, T>, "No known conversion between type <U> and <T>");
		normalize();
	}

	T numerator() const{
		return _numerator;
	}

	T denominator() const{
		return _denominator;
	}

	fraction<T> operator+(const fraction<T>& input) const{
		return fraction<T>(input.numerator() * _denominator + _numerator * input.denominator(), _denominator * input.denominator());
	}

	fraction<T> operator+(T input) const{
		return fraction<T>(_numerator + input * _denominator, _denominator);
	}

	fraction<T> operator-(const fraction<T>& input) const{
		return fraction<T>(_numerator * input.denominator() - input.numerator() * _denominator, _denominator * input.denominator());
	}

	fraction<T> operator-(T input) const{
		return fraction<T>(_numerator - input * _denominator, _denominator);
	}
	
	fraction<T> operator-() const{
		return fraction<T>(-_numerator, _denominator);
	}

	fraction<T> operator*(const fraction<T>& input) const{
		return fraction<T>(_numerator * input.numerator(), _denominator * input.denominator());
	}

	fraction<T> operator*(T input) const{
		return fraction<T>(_numerator * input, _denominator);
	}

	fraction<T> operator/(const fraction<T>& input) const{
		if(input.numerator() == T(0)) throw std::invalid_argument("Cannot divide fraction by zero");
		return fraction<T>(_numerator * input.denominator(), _denominator * input.numerator());
	}

	fraction<T> operator/(T input) const{
		if(input == T(0)) throw std::invalid_argument("Cannot divide fraction by zero");
		return fraction<T>(_numerator, _denominator * input);
	}

	fraction<T>& operator+=(T input){
		_numerator += input * _denominator;
		normalize();
		return *this;
	}
	fraction<T>& operator+=(const fraction<T>& input){
		_numerator = _numerator * input.denominator() + input.numerator() * _denominator;
		_denominator *= input.denominator();
		normalize();
		return *this;
	}
	fraction<T>& operator-=(T input){
		_numerator -= input * _denominator;
		normalize();
		return *this;
	}
	fraction<T>& operator-=(const fraction<T>& input){
		_numerator = _numerator * input.denominator() - input.numerator() * _denominator;
		_denominator *= input.denominator();
		normalize();
		return *this;
	}
	fraction<T>& operator*=(T input){
		_numerator *= input;
		normalize();
		return *this;
	}
	fraction<T>& operator*=(const fraction<T>& input){
		_numerator *= input.numerator();
		_denominator *= input.denominator();
		normalize();
		return *this;
	}
	fraction<T>& operator/=(T input){
		if(input == T(0)) throw std::invalid_argument("Cannot divide fraction by zero");
		_denominator *= input;
		normalize();
		return *this;
	} 
	fraction<T>& operator/=(const fraction<T>& input){
		if(input.numerator() == T(0)) throw std::invalid_argument("Cannot divide fraction by zero");
		_numerator *= input.denominator();
		_denominator *= input.numerator();
		normalize();
		return *this;
	}
	
	bool operator==(const fraction<T>& input) const{
		return (input.numerator() == _numerator && input.denominator() == _denominator);
	}
	bool operator==(T input) const{
		return (_denominator == 1 && input == _numerator);
	}
	bool operator!=(const fraction<T>& input) const{
		return (input.numerator() != _numerator || input.denominator() != _denominator);
	}
	bool operator!=(T input) const{
		return (_denominator != 1 || input != _numerator);
	}
	bool operator<=(T input) const{
		return (_numerator <= (input * _denominator));
	}
	bool operator<=(const fraction<T>& input) const{
		return ((_numerator * input.denominator()) <= (input.numerator() * _denominator));
	}
	bool operator<(T input) const{
		return _numerator < (input * _denominator);
	}	
	bool operator<(const fraction<T>& input) const{
		return (_numerator * input.denominator()) < (input.numerator() * _denominator);
	}
	bool operator>=(T input) const{
		return (_numerator >= input * _denominator);
	}
	bool operator>=(const fraction<T>& input) const{
		return (_numerator * input.denominator()) >= (input.numerator() * _denominator);
	}
	bool operator>(T input) const{
		return (_numerator > input * _denominator); 
	}
	bool operator>(const fraction<T>& input) const{
		return (_numerator * input.denominator() > input.numerator() * _denominator);
	}
	
	explicit operator double()const{
		static_assert(std::is_convertible_v<T, double>, "No known conversion between type <T> and <double>");
		return static_cast<double>(_numerator)/static_cast<double>(_denominator);
	}

	friend std::ostream& operator<<(std::ostream& os, const fraction<T>& input){
		os<<input.numerator()<<" / "<<input.denominator();
		return os;
	}
};

};
