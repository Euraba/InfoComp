//
//  main.cpp
//  expresie2
//
//  Created by she on 03/10/2020.
//
 
#include <fstream>
#include <vector>
#include <algorithm>
 
 
std::fstream in("expresie2.in", std::ios::in) ;
std::fstream out("expresie2.out", std::ios::out) ;
 
char str[100005] ;
int ind, nr ;
int paranteza_rotund() ;
int expr() ;
int termen() ;
 
int paranteza_dreapta() {
	int aux = termen() ;
	std::vector < int > v ;
	v.push_back(aux) ;
	while(str[ind] == ',' && str[ind] != ']') {
		ind ++ ;
		aux = termen() ;
		v.push_back(aux) ;
	}
	sort(v.begin(), v.end()) ;
	return v[((v.size() + 1)  >> 1) - 1] ;
}
 
int paranteza_rotunda() {
	int aux = termen() ;
	int curr_maxx = aux, maxx = aux ;
	while(str[ind] == ',' && str[ind] != ')') {
		ind ++ ;
		aux = termen() ;
		curr_maxx = std::max(curr_maxx + aux, aux) ;
		maxx = std::max(maxx, curr_maxx) ;
	}
	return maxx ;
}
 
int termen() {
	int aux = 0 ;
	if(str[ind] == '(') {
		ind ++ ;
		aux = paranteza_rotunda() ;
		ind ++ ;
		return aux ;
	}
	if(str[ind] == '[') {
		ind ++ ;
		aux = paranteza_dreapta() ;
		ind ++ ;
		return aux ;
	}
	int sgn = 1 ;
	if(str[ind] == '-') {
		sgn = -1 ;
		ind ++ ;
	}
	while('0' <= str[ind] && str[ind] <= '9') {
		aux = aux * 10 + (str[ind ++] - '0') ;
	}
	nr ++ ;
	return sgn * aux ;
}
 
int expr() {
	int aux = termen() ;
	int s = aux ;
	while(str[ind] == ',') {
		ind ++ ;
		aux = termen() ;
		s += aux ;
	}
	out << nr << '\n' ;
	return s ;
}
 
int main() {
	in >> str ;
	ind = 0 ;
	out << expr() ;
}
