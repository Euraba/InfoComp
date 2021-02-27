//
//  main.cpp
//  covrigi
//
//  Created by Eusebiu Rares on 12/04/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
#include "algorithm"
 
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
 
template <typename F>
class OutputParsing {
	private :
	static const int SIZE = (1 << 20) ;
	char outBuffer[SIZE] ;
	const int BULAN = 500 ;
	int outputSize ;
	__attribute__ ( (always_inline)) int numberDigits(F x) {
		int digits = x > 999999999 ? 11 :
		x > 99999999  ? 10 :
		x > 9999999   ? 9  :
		x > 999999    ? 8  :
		x > 99999     ? 7  :
		x > 9999      ? 6  :
		x > 999       ? 5  :
		x > 99        ? 4  :
		x > 9         ? 3  : 2 ;
		return digits ;
	}
	public :
	FILE *output_file ;
	OutputParsing() {}
	OutputParsing (const char *file_name) {
		output_file = fopen (file_name, "wb") ;
		outputSize = -1 ;
	}
	__attribute__ ( (always_inline)) void sflush() {
		fwrite(outBuffer, 1, outputSize, output_file) ;
		outputSize = -1 ;
	}
	__attribute__ ( (always_inline)) void operator << (F val) {
		if (val == -1) {
			outBuffer[++ outputSize] = 45 ;
			outBuffer[++ outputSize] = 49 ;
			outBuffer[++ outputSize] = 10 ;
		} else {
			int digits = numberDigits(val) ;
			for (int i = digits ; -- i ; val /= 10) {
				outBuffer[outputSize + i] = val % 10 + 48 ;
			}
			outBuffer[outputSize = outputSize + digits] = 10 ;
		}
		if (outputSize <= SIZE - BULAN) {
			sflush() ;
		}
		return ;
	}
};
 
InputReader<int> in ("covrigi.in") ;
OutputParsing<int> out ("covrigi.out") ;
 
const int MV = 5e5 ;
 
int fi[MV + 1], psm[MV + 1] ;
 
int main() {
	int n, m, k ; in >> n >> m >> k ;
	for (int i = 0 ; i < n ; ++ i) {
		in >> fi[i] ;
	}
	for (int i = 0 ; i < m ; ++ i) {
		in >> psm[i] ;
	}
	std::sort(psm, psm + m) ;
	for (int i = m - 2 ; i >= 0 ; -- i) {
		psm[i] += psm[i + 1] ;
	}
	int last = psm[0] + 1 ;
	int answer = fi[last - 1] ;
	for (int i = m - 1 ; i >= 0 ; -- i) {
		answer = std::max(fi[last - psm[i] - 1] - k * (m - i), answer) ;
	}
	out << answer ;
}
