//
//  main.cpp
//  zoro
//
//  Created by Eusebiu Rares on 07/04/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
#include "map"
#include "unordered_map"
 
std::fstream in ("zoro.in", std::ios::in) ;
std::fstream out ("zoro.out", std::ios::out) ;
 
const int MV = 1000 ;
 
int dpLine[MV + 1] ;
int dpColumn[MV + 1] ;
 
std::pair<int, int> inv[MV * MV + 1] ;
 
int main(int argc, const char * argv[]) {
	int n, m ; in >> n >> m ;
	int val(0), startPoint(0), finishPoint(0) ;
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= m ; ++ j) {
			in >> val ;
			if (i == 1 == j) {
				startPoint = val ;
			}
			inv[val] = {i, j} ;
		}
	}
	finishPoint = val ;
	dpLine[1] = dpColumn[1] = 0 ;
	int answer(0) ;
	for (int i = startPoint ; i >= finishPoint ; -- i) {
		answer = std::max(dpLine[inv[i].first], dpColumn[inv[i].second]) + 1 ;
		dpLine[inv[i].first] = dpColumn[inv[i].second] = answer ;
	}
	out << answer ;
}
