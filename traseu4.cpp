//
//  main.cpp
//  traseu4
//
//  Created by Eusebiu Rares on 16/09/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
#include "algorithm"
 
std::fstream input ("traseu4.in", std::ios::in) ;
std::fstream output ("traseu4.out", std::ios::out) ;
 
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
 
const int MV = 500 ;
 
struct Cell {
	int x, y ;
	Cell() {
		x = y = 0 ;
	}
	Cell (int _x, int _y) {
		x = _x ;
		y = _y ;
	}
} ;
 
Cell land[MV * MV + 1] ;
int bestCol[MV + 1] ;
 
int main(int argc, const char * argv[]) {
	int n, m ; input >> n >> m ;
	for (int i = 1 ; i <= n ; ++ i) {
		for (int j = 1 ; j <= m ; ++ j) {
			int value ; input >> value ;
			land[value] = Cell(i, j) ;
		}
	}
	for (int i = 1 ; i <= n ; ++ i) {
		bestCol[i] = 1e6 ;
	}
	int longestPath(0) ;
	for (int i = 1 ; i <= n * m ; ++ i) {
		Cell curr = land[i] ;
		for (int j = 1 ; j <= curr.x ; ++ j) {
			if (bestCol[j] <= curr.y) {
				longestPath = MAX(longestPath, curr.x - j + curr.y - bestCol[j] + 1) ;
			}
		}
		bestCol[curr.x] = MIN(bestCol[curr.x], curr.y) ;
	}
	output << longestPath ;
}
