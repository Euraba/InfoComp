//
//  main.cpp
//  rover
//
//  Created by Eusebiu Rares on 22/10/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include <fstream>
#include <deque>
 
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
InputReader<int>in ("rover.in") ;
 
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
OutoutParsing out ("rover.out") ;
 
const int MAXN = 500 ;
const int INF = 1e7 ;
 
typedef std::pair<int, int> PII ;
 
const int dx[] = {0, 0, 1, 0, -1} ;
const int dy[] = {0, 1, 0, -1, 0} ;
 
int mat[1 + MAXN][1 + MAXN] ;
int cost[1 + MAXN][1 + MAXN] ;
 
int solve(int size, int weight) {
	for (int i = 1 ; i <= size ; ++ i) {
		for (int j = 1 ; j <= size ; ++ j) {
			cost[i][j] = INF ;
		}
	}
	std::deque<PII> dq ;
	cost[1][1] = 0 ;
	dq.push_front({1, 1}) ;
	while (!dq.empty()) {
		PII top = dq.front() ;
		dq.pop_front() ;
		for (int k = 1 ; k <= 4 ; ++ k) {
			int ii = top.first + dx[k], jj = top.second + dy[k] ;
			if (cost[top.first][top.second] + (mat[ii][jj] < weight) < cost[ii][jj]) {
				cost[ii][jj] = cost[top.first][top.second] + (mat[ii][jj] < weight) ;
				if (mat[ii][jj] < weight) {
					dq.push_back({ii, jj}) ;
				} else {
					dq.push_front({ii, jj}) ;
				}
			}
		}
	}
	return cost[size][size] ;
}
 
int main(int argc, const char * argv[]) {
	int v, n, g, i, j ;
	in >> v >> n ;
	if (v == 1) {
		in >> g ;
		for (i = 1 ; i <= n ; ++ i) {
			for (j = 1 ; j <= n ; ++ j) {
				in >> mat[i][j] ;
			}
		}
		int ans = solve(n, g) ;
		out << ans ;
		return 0 ;
	}
	for (i = 1 ; i <= n ; ++ i) {
		for (j = 1 ; j <= n ; ++ j) {
			in >> mat[i][j] ;
		}
	}
	int ret(0) ;
	for (int step(1 << 14) ; step ; step >>= 1) {
		if (solve(n, step + ret) == 0) {
			ret |= step ;
		}
	}
	out << ret ;
}
