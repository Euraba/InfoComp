#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <unordered_map>
#include <cstring>

auto *in = fopen("taietura.in", "r"), *out = fopen("taietura.out", "w") ;

const int nmax = 1e5 ;

int v[1 + nmax] ;
int smen[1 + nmax] ;

using i64 = long long ;

std::unordered_map<i64, std::vector<int> > mp ;

int n ;

void brut() {
    i64 suma(0) ;
    int left, right, i ;
    mp.clear() ;
    mp[0].push_back(0) ;
    memset(smen, 0, sizeof smen) ;
    for (i = 1 ; i <= n ; ++ i) {
        suma += v[i] ;
        if (mp.find(suma) != mp.end()) {
            for (auto it : mp[suma]) {
                left = it + 1 ;
                right = i ;
                smen[left] ++ ;
                smen[right + 1] -- ;
            }
        }
        mp[suma].push_back(i) ;
    }
    for (i = 1 ; i <= n ; ++ i) {
        smen[i] += smen[i - 1] ;
        fprintf(out, "%d ", smen[i]) ;
    }
}

int main() {
    int i ;
    fscanf(in, "%d\n", &n) ;
    for (i = 1 ; i <= n ; ++ i) {
        fscanf(in, "%d ", v + i) ;
    }
    i64 suma(0) ;
    int left, right ;
    mp[0].push_back(0) ;
    for (i = 1 ; i <= n ; ++ i) {
        suma += v[i] ;
        mp[suma].push_back(i) ;
    }
    for (auto vv : mp) {
        int value = vv.first ;
        auto li = vv.second ;
        int sz = li.size() ;
        for (i = 1 ; i < li.size() ; ++ i) {
            int var = i * (sz - i) ;
            smen[li[i - 1] + 1] += var ;
            smen[li[i] + 1] -= var ;
        }
    }
    for (i = 1 ; i <= n ; ++ i) {
        smen[i] += smen[i - 1] ;
        fprintf(out, "%d ", smen[i]) ;
    }
#ifndef INFOARENA
    fputc('\n', out) ;
    brut() ;
#endif
}
