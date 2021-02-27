//
//  main.cpp
//  balul bobocilor
//
//  Created by Eusebiu Rares on 14/09/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
#include <iostream>
#include "fstream"
#include "iomanip"
 
std::fstream in ("balulbobocilor.in", std::ios::in) ;
std::fstream out ("balulbobocilor.out", std::ios::out) ;
 
int main(int argc, const char * argv[]) {
	double distStart ; in >> distStart ;
	double fiSpeed, x1, y1 ; in >> fiSpeed >> x1 >> y1 ;
	double seSpeed, x2, y2 ; in >> seSpeed >> x2 >> y2 ;
	double girlSpeed ; in >> girlSpeed ;
	double answer = distStart / (fiSpeed + seSpeed) ;
	answer = answer * girlSpeed ;
	out << std::fixed << std::setprecision(6) << answer ;
}
