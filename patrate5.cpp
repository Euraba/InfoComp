//
//  main.cpp
//  patrate5
//
//  Created by Eusebiu Rares on 12/03/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include <fstream>
#include <vector>
 
const int MV = 350001 ;
const int NV = 1001 ;
 
std::fstream in ("patrate5.in", std::ios::in) ;
std::fstream out ("patrate5.out", std::ios::out) ;
 
struct DC{
  int a, b, c, val ;
};
 
int n, p, squares[MV] ;
bool test ;
DC ans[NV] ;
 
std::vector<int> vc ;
 
int main() {
	for(int i = 1 ; i * i < MV ; ++ i) {
		squares[i * i] = i ;
	}
	in >> n >> p ;
	ans[2].val = 2 ;
	ans[2].a = 1 ;
	ans[2].b = 1 ;
	ans[2].c = 0;
	for(int i = 2 ; i < n ; ++ i) {
		test = false ;
		for(int c = 1 ; ans[i].val + c * c <= 350000 && !test ; ++ c) {
			for(int r = 1 ; r * r < ans[i].val + c * c && !test; ++ r) {
				if(squares[ans[i].val + c * c - r * r]) {
					ans[i + 1].val = ans[i].val + c * c ;
					ans[i + 1].c = c * c ;
					ans[i + 1].a = r * r ;
					ans[i + 1].b = ans[i].val + c * c - r * r ;
					test = true ;
				}
			}
		}
	}
	out << ans[n].val << '\n' ;
	if(p == 2) {
		out << squares[ans[n].a] << " " << squares[ans[n].b] << '\n' ;
	}
	vc.push_back(squares[ans[n].c]) ;
	for(int i = 3 ; i <= n ; ++ i){
		if(i >= p){
			out << squares[ans[n - i + 2].a] << " " << squares[ans[n - i + 2].b] << " " ;
			for(auto j : vc) {
				out << j << " " ;
			}
			out << '\n' ;
		}
		vc.push_back(squares[ans[n - i + 2].c]) ;
	}
}
