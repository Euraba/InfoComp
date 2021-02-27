//
//  main.cpp
//  cristale
//
//  Created by she on 18/03/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
 
std::fstream in ("cristale.in", std::ios::in) ;
std::fstream out ("cristale.out", std::ios::out) ;
 
static void extracted(char a, char b, char c, int &cnt1, int &cnt2, int &cnt3, char cr) {
	if (cr == a) {
		cnt1 ++ ;
	} else if (cr == b) {
		cnt2 ++ ;
	} else if (cr == c) {
		cnt3 ++ ;
	}
}
 
static void extracted(int cnt1, int cnt2, int cnt3, int len) {
	if (cnt1 == len || cnt2 == len || cnt3 == len) {
		out << len << '\n' ;
	} else if (cnt1 % 2 == cnt2 % 2 && cnt1 % 2 == cnt3 % 2) {
		out << 2 << '\n' ;
	} else {
		out << 1 << '\n' ;
	}
}
 
int main(int argc, const char * argv[]) {
	char a, b, c ;
	int cnt1, cnt2, cnt3 ;
	in >> a >> b >> c ;
	int tests ;
	in >> tests ;
	while (tests -- ) {
		int len ; in >> len ;
		char cr ;
		cnt1 = cnt2 = cnt3 = 0 ;
		for (int i = 1 ; i <= len ; ++ i) {
			in >> cr ;
			extracted(a, b, c, cnt1, cnt2, cnt3, cr);
		}
		extracted(cnt1, cnt2, cnt3, len);
	}
}
