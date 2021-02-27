//
//  main.cpp
//  segmente7
//
//  Created by she on 23/03/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <fstream>
 
std::fstream in("7segmente.in",  std::ios::in) ;
std::fstream out("7segmente.out",  std::ios::out) ;
 
typedef unsigned long long ULL;
 
ULL fr[] = {0, 2, 5, 5, 4, 5, 6, 3, 7, 6} ;
 
ULL v[21], nr[21] ;
 
ULL nrcif(ULL n) {
	ULL cnt(0) ;
	while(n) {
		cnt ++ ;
		n /= 10 ;
	}
	return cnt ;
}
 
int main() {
	ULL n, t, ans = 0, rest ;
	in >> n >>t ;
	ULL nrc = nrcif(n) ;
	for(ULL i = nrc ; i >= 1 ; -- i, n /= 10) {
		v[i] = n % 10 ;
		ans += fr[n % 10] ;
	}
	ULL nra = std::min(t / 2, nrc) ;
	for(ULL i = 1 ; i <= nra ; ++ i) {
		nr[i] = 1 ;
	}
	rest = t - nra * 2 ;
	bool ok(true) ;
	if(nra < nrc) {
		ok = 0 ;
	}
	out << ans << " " ;
	for(ULL i = 1 ; i <= nra ; ++ i) {
		if(ok == 0) {
			ULL j = 9 ;
			for(;fr[j] - fr[nr[i]] > rest and j > 1 ; -- j) ;
			rest -= (fr[j]-fr[nr[i]]) ;
			nr[i] = j ;
		} else {
			ULL j = v[i] ;
			for( ; fr[j] - fr[nr[i]] > rest and j > 1 ; -- j) ;
			rest -= (fr[j]-fr[nr[i]]) ;
			nr[i] = j ;
			if(nr[i] < v[i]) {
				ok = 0 ;
			}
		}
		out << nr[i] ;
	}
}
