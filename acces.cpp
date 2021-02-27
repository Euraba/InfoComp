//
//  main.cpp
//  acces
//
//  Created by Eusebiu Rares on 22.02.2021.
//
 
#include <iostream>
#include <fstream>
 
std::fstream in ("acces.in", std::ios::in) ;
std::fstream out ("acces.out", std::ios::out) ;
 
const int maxn = 1000 ;
 
int mat[1 + maxn][1 + maxn] ;
int dp[1 + maxn][1 + maxn] ;
 
int main(int argc, const char * argv[]) {
	int l, c ;
	in >> l >> c ;
	for (int i = 1 ; i <= l ; ++ i) {
		for (int j = 1 ; j <= c ; ++ j) {
			in >> mat[i][j] ;
		}
	}
	for (int i = 1 ; i <= l ; ++ i) {
		for (int j = 1 ; j <= c ; ++ j) {
			if (mat[i][j] == 1) {
				dp[i][j] = std::min(dp[i - 1][j], std::min(dp[i][j - 1], dp[i - 1][j - 1])) ;
			} else {
				dp[i][j] = 1 ;
				if (mat[i][j - 1] == 0) {
					dp[i][j] += dp[i][j - 1] ;
				}
				if (mat[i - 1][j] == 0) {
					dp[i][j] += dp[i - 1][j] ;
				}
				if (mat[i][j - 1] == 0 && mat[i - 1][j] == 0) {
					dp[i][j] -= dp[i - 1][j - 1] ;
				}
			}
		}
	}
	int querys ;
	in >> querys ;
	for (int i = 1 ; i <= querys ; ++ i) {
		int n, m ;
		in >> n >> m ;
		out << dp[n][m] << '\n' ;
	}
}
