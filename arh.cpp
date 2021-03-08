#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
 
#pragma GCC optimize("O3")
 
std::fstream in ("arh.in", std::ios::in) ;
std::fstream out ("arh.out", std::ios::out) ;
 
char current ;
 
int ans(0) ;
 
std::string solve(char stop = '\n') {
    std::string ret("") ;
    in >> current ;
    if (current == stop || in.eof()) {
        return ret ;
    }
    if (isalpha(current) || current == '*') {
        ret += current ;
        std::string urm = solve(stop) ;
        return ret + urm ;
    }
    if (isdigit(current)) {
        int num(0) ;
        ans ++ ;
        for ( ; isdigit(current) ; in >> current) {
            num = num * 10 + (current - '0') ;
        }
        std::string rep = solve(')') ;
        for (int i = 1 ; i <= num ; ++ i) {
            ret += rep ;
        }
        std::string cont = solve(stop) ;
        ret += cont ;
        return ret ;
    }
    if (current == '[') {
        ans ++ ;
        std::string ra = solve(']') ;
        if (ra[0] == '*') {
            ra.erase(ra.begin()) ;
            std::string v = ra ;
            std::reverse(v.begin(), v.end()) ;
            ra += v ;
            std::string cont = solve(stop) ;
            ra += cont ;
            return ra ;
        } else {
            ra.erase(ra.begin() + ra.size() - 1) ;
            std::string v = ra ;
            std::reverse(v.begin(), v.end()) ;
            v.erase(v.begin()) ;
            ra += v ;
            std::string cont = solve(stop) ;
            ra += cont ;
            return ra ;
        }
    }
}
 
int main() {
    std::ios::sync_with_stdio(false) ;
    in.tie(NULL) ;
    out.tie(NULL) ;
    std::string ret = solve() ;
    out << ans << '\n' << ret ;
}
