//
//  main.cpp
//  text2
//
//  Created by Eusebiu Rares on 07.12.2020.
//
 
#include <iostream>
#include <fstream>
#include <bitset>
 
std::fstream in ("text2.in", std::ios::in | std::ios::binary) ;
std::fstream out ("text2.out", std::ios::out) ;
 
const int maxn = 200 ;
const int INF = 1e9 ;
const int MOD = 1000003 ;
 
std::string vowels("aeiouy") ;
int dp[1 + maxn][1 + maxn] ;
int from[1 + maxn][1 + maxn] ;
int conf[1 + maxn][1 + maxn] ;
std::bitset<1 + maxn> space ;
 
bool vowel(char aux) {
	return vowels.find(aux) != std::string::npos ;
}
 
int findVowel(int pos, std::string ss) {
	int ret(pos) ;
	for ( ; !vowel(ss[ret]) && ret ; -- ret) ;
	return ret ;
}
 
void update(int i, int j, int lastVowel) {
	for ( ; lastVowel >= 1 && lastVowel >= i - 19 ; -- lastVowel) {
		if (dp[i][j] > dp[lastVowel - 1][j - 1] + (i - lastVowel + 1) * (i - lastVowel + 1)) {
			dp[i][j] = dp[lastVowel - 1][j - 1] + (i - lastVowel + 1) * (i - lastVowel + 1) ;
			from[i][j] = lastVowel - 1 ;
		} else if (dp[i][j] == dp[lastVowel - 1][j - 1] + (i - lastVowel + 1) * (i - lastVowel + 1)) {
			from[i][j] = lastVowel - 1 ;
		}
		// cerinta 1
		conf[i][j] = (conf[lastVowel - 1][j - 1] + conf[i][j]) % MOD ;
	}
}
 
static void start(int letters) {
	conf[0][0] = 1 ;
	dp[0][0] = 0 ;
	for (int i = 1 ; i <= letters ; ++ i) {
		dp[0][i] = dp[i][0] = INF ;
	}
	from[0][0] = 1 ;
}
 
void afis(int words, int now) {
	if (words == 0) {
		return ;
	}
	space[now] = 1 ;
	-- words ;
	now = from[now][words] ;
	afis(words, now) ;
}
 
int main(int argc, const char * argv[]) {
	std::string sentence ;
	int words ;
	in >> sentence ; sentence = "!" + sentence ;
	in >> words ;
	int letters((int)sentence.size() - 1) ;
	start(letters);
	for (int i = 1 ; i <= letters ; ++ i) {
		int lastVowel(findVowel(i, sentence)) ;
		for (int j = 1 ; j <= words ; ++ j) {
			dp[i][j] = INF ;
			update(i, j, lastVowel) ;
		}
	}
	out << conf[letters][words] << '\n' << dp[letters][words] << '\n' ;
	int now(from[letters][words]) ;
	afis(words,now) ;
	for (int i = 1 ; i <= letters ; ++ i) {
		out << sentence[i] ;
		if (space[i]) {
			out << ' ' ;
		}
	}
}
