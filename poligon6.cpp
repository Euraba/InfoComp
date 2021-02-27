/
//  main.cpp
//  poligon6
//
//  Created by Eusebiu Rares on 03/03/2020.
//  Copyright © 2020 Eusebiu Rares. All rights reserved.
//
 
/*
 Avem N distante si pentru fiecare alegem punctele laticeala la distanta respectiva fata de origine.
{1}
 In limbaj matematic : ->
 Pentru R distanta vrem X si Y naturale a.i.
{1}
 Xˆ2 + Yˆ2 = Rˆ2
{1}
 Triplete Pitagoreice :->
{1}
 R = aˆ2 + bˆ2
 X = aˆ2 - bˆ2 = 9
 Y = 2ab = 12 => ab = 6
{1}
 R <= 1000
 => ne putem recalcula ventru toate R-urile valorile
 */
 
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
 
const int MV = 1e6 ;
 
typedef std::pair<int, int> PII ;
 
std::vector<std::pair<int, int> > pit ;
int latticePoints ;
 
void compute(int lim) {
	int x, y ;
	for (x = 1 ; x * x <= lim ; ++ x) {
		y = sqrt(lim - x * x) ;
		if (x <= y && y * y == lim - x * x) {
			pit.push_back(std::make_pair(x, y)) ;
		}
	}
}
 
struct Point {
	int x, y ;
	Point() {
		x = y = 0 ;
	}
	Point(int _x, int _y) {
		this ->x = _x ;
		this ->y = _y ;
	}
	bool operator < (const Point &aux) const {
		double anglefi(0.0) ;
		anglefi = atan2(x, -y) ;
		double anglese(0.0) ;
		anglese = atan2(aux.x, -aux.y) ;
		return anglefi < anglese ;
	}
} ;
 
std::map<Point, int> mp ;
 
int gcd(int a, int b) {
	int rest ;
	if (a < b) {
		std::swap(a, b) ;
	}
	while (b) {
		rest = a ;
		a = b ;
		b = rest % b ;
	}
	return a ;
}
 
void change(int &X, int &Y) {
	int GCD = gcd(X, Y) ;
	X /= GCD ;
	Y /= GCD ;
	return ;
}
 
void eval(int dist) {
	int X, Y ;
	pit.clear() ;
	compute(dist * dist) ;
	for (PII it : pit) {
		X = it.first ;
		Y = it.second ;
		latticePoints ++ ;
		change(X, Y) ;
//		std::cerr << X << ' ' << Y << '\n';
		mp[Point(X, Y)] ++ ;
		if (X != Y) {
			std::swap(X, Y) ;
			latticePoints ++ ;
//			std::cerr << X << ' ' << Y << '\n';
			mp[Point(X, Y)] ++ ;
		}
	}
}
 
int main(int argc, const char * argv[]) {
	freopen("poligon6.in", "r", stdin) ;
	freopen("poligon6.out", "w", stdout) ;
	int n ; std::cin >> n ;
	int i, dist ;
	for (i = 1 ; i <= n ; ++ i) {
		std::cin >> dist ;
		eval(dist) ;
	}
	std::cout << latticePoints << '\n' << mp.size() << '\n' ;
	for (auto it : mp) {
		std::cout << it.second << ' ' ;
	}
}
