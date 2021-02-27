//
//  main.cpp
//  expozitie
//
//  Created by Eusebiu Rare on 10/10/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
 
std::fstream in ("expozitie.in", std::ios::in) ;
std::fstream out ("expozitie.out", std::ios::out) ;
 
class BigInt {
private :
	static const int MV = 1e4 ;
	int v[MV + 1] ;
public :
	BigInt() {
		this -> v[0] = 1 ;
		this -> v[1] = 0 ;
		for (int i = 1 ; i < MV ; ++ i) {
			this ->v[i] = 0 ;
		}
	}
	
	BigInt(int val) {
		this ->v[0] = 0 ;
		for (int i = 1 ; i < MV ; ++ i) {
			this ->v[i] = 0 ;
		}
		do {
			this ->v[++ this ->v[0]] = val % 10 ;
			val /= 10 ;
		} while(val) ;
	}
	
	BigInt operator * (int number) {
		int rest(0), i ;
		for (i = 1 ; i <= this ->v[0] || rest ; ++ i) {
			this ->v[i] = this ->v[i] * number + rest ;
			rest = this ->v[i] / 10 ;
			this ->v[i] %= 10 ;
		}
		this ->v[0] = i - 1 ;
		return *this ;
	}
	
	BigInt operator *= (int number) {
		return *this * number ;
	}
	
	BigInt operator / (int number) {
		int rest(0), i ;
		for (i = this ->v[0] ; i > 0 ; -- i) {
			rest = rest * 10 + this ->v[i] ;
			this ->v[i] = rest / number ;
			rest = rest % number ;
		}
		for ( ; !this ->v[this ->v[0]] ; --this ->v[0]) ;
		return *this ;
	}
	
	BigInt operator /= (int number) {
		return *this / number ;
	}
	
	friend std::ostream& operator<< (std::ostream &os, const BigInt& aux) {
		for (int i = aux.v[0] ; i > 0 ; -- i) {
			os << aux.v[i] ;
		}
		return os ;
	}
} ;
 
int main(int argc, const char * argv[]) {
	int n, d, k ;
	in >> n >> d >> k ;
	n -= d * k ;
	if (n < 0) {
		return out << 0, 0 ;
	}
	if (n == 0) {
		return out << 1, 0 ;
	}
	BigInt ans(1) ;
	for (int i = n + 1 ; i <= n + d - 1 ; ++ i) {
		ans *= i ;
	}
	for (int i = 2 ; i <= d - 1 ; ++ i) {
		ans /= i ;
	}
	out << ans ;
}
