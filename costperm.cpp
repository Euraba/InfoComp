//
//  main.cpp
//  costperm
//
//  Created by Eusebiu Rares on 12/04/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "vector"
#include "fstream"
 
template <typename T>
class BinaryIndexedTree {
	private :
	std::vector<T> aib ;
	static const int MAXVAL = (1 << 30) ;
	int sz ;
	public :
	__attribute__ ( (always_inline)) BinaryIndexedTree (int _ = 0) {
		this ->sz = _ ;
		aib.resize (sz + 1) ;
	}
	__attribute__ ( (always_inline)) void update (int poz, T val) {
		for (int i = poz ; i <= sz ; i += (i & (-i))) {
			aib.at (i) += val ;
		}
	}
	__attribute__ ( (always_inline)) int query (int poz) {
		T ret (0) ;
		for (int i = poz ; i > 0 ; i -= (i & (-i))) {
			ret += (T)aib.at (i) ;
		}
		return ret ;
	}
	__attribute__ ( (always_inline)) int BinarySearch (T val) {
		int ret (0) ;
		for (int step (MAXVAL) ; step ; step >>= 1) {
			if (ret + step <= sz && aib[ret + step] <= val) {
				val -= aib.at (ret + step) ;
				ret |= step ;
			}
		}
		if (!val) {
			return ret ;
		}
		return -1 ;
	}
};
 
template <typename T>
class InputReader {
private:
	FILE *input_file ;
	static const int SIZE = (1 << 17) ;
	int point ;
	char buffer[SIZE] ;
	__attribute__ ( (always_inline)) void advance() {
		++ point ;
		if (point == SIZE) {
			point = 0 ;
			fread (buffer, SIZE, 1, input_file) ;
		}
	}
public:
	InputReader() {}
	InputReader (const char *file_name) {
		input_file = fopen (file_name, "r") ;
		point = 0 ;
		fread (buffer, SIZE, 1, input_file) ;
	}
	__attribute__ ( (always_inline)) InputReader &operator >> (T &n) {
		for (; !isdigit (buffer[point]) ; advance()) ;
		n = 0 ;
		for (; isdigit (buffer[point]) ; advance()) {
			n = n * ( (1 << 3) + (1 << 1)) + buffer[point] - '0' ;
		}
		return *this ;
	}
} ;
 
InputReader<int> in ("costperm.in") ;
std::fstream out ("costperm.out", std::ios::out) ;
 
int main(int argc, const char * argv[]) {
	int n ; in >> n ;
	BinaryIndexedTree<int> aib(n) ;
	long long ans(0) ;
	for (int i = 1 ; i <= n ; ++ i) {
		int val ; in >> val ;
		ans += (long long)val * (i - 1 - aib.query(val)) ;
		aib.update(val, 1) ;
	}
	out << ans ;
}
