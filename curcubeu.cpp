//
//  main.cpp
//  balul bobocilor
//
//  Created by Eusebiu Rares on 14/09/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
#include "vector"
#include "algorithm"
 
std::fstream in ("curcubeu.in", std::ios::in) ;
 
const int MV = 2e6 ;
using i64 = long long ;
 
class OutoutParsing {
public:
	OutoutParsing() {} ;
	
  OutoutParsing(const char * file_name) {
    output_file.open(file_name, std::ios::out | std::ios::binary) ;
    output_file.sync_with_stdio(false) ;
    index = 0 ;
  }
	
  inline OutoutParsing & operator << (int target) {
    aux = 0 ;
    n = target ;
		target < 0 ? sign = -1 : sign = 1 ;
		if (!n) {
      nr[aux ++] = '0' ;
		}
		for ( ; n ; n /= 10) {
      nr[aux ++] = sign * (n % 10) + '0' ;
		}
    if (sign == -1) {
      buffer[index] = '-' ;
      inc() ;
    }
    for ( ; aux ; inc())
      buffer[index] = nr[-- aux] ;
    return *this ;
  }
	
  inline OutoutParsing & operator << (const char * target) {
    aux = 0 ;
		while (target[aux]) {
			buffer[index] = target[aux ++] ;
			inc() ;
		}
    return *this ;
  }
	~OutoutParsing() {
    output_file.write(buffer, index) ;
    output_file.close() ;
  }
	
private:
    std::fstream output_file;
  static const int SIZE = 0x200000;
  int index = 0, aux, n, sign;
  char buffer[SIZE], nr[24];
	
  inline void inc() {
		if (++index == SIZE) {
			index = 0 ;
			output_file.write(buffer, SIZE);
		}
  }
} ;
 
OutoutParsing out ("curcubeu.out") ;
 
struct Query {
	int left, right ;
	int value ;
	Query() {
		this -> left = this -> right = this -> value = -1 ;
	}
	Query(int _left, int _right, int _value) {
		this -> left = _left ;
		this -> right = _right ;
		this -> value = _value ;
	}
} ;
 
std::vector<Query> querys ;
int sol[MV + 1] ;
int jump[MV + 1] ;
 
int main(int argc, const char * argv[]) {
	int n, A, B, C, i, position ;
	in >> n >> A >> B >> C ;
	
	querys.push_back(Query(std::min(A, B), std::max(A, B), C)) ;
	for (i = 2 ; i <= n - 1 ; ++ i) {
		A = ((i64)A * i) % n ;
		B = ((i64)B * i) % n ;
		C = ((i64)C * i) % n ;
		querys.push_back(Query(std::min(A, B), std::max(A, B), C)) ;
	}
	
	std::reverse(querys.begin(), querys.end()) ;
	
	for (Query currentQuery : querys) {
		for (position = currentQuery.left ; position <= currentQuery.right ; ) {
			if (sol[position] != 0) {
				position = jump[position] ;
			} else {
				sol[position] = currentQuery.value ;
				jump[position] = currentQuery.right + 1 ;
				position ++ ;
			}
		}
	}
	
	for (i = 1 ; i <= n - 1 ; ++ i) {
		out << sol[i] << "\n" ;
	}
}
