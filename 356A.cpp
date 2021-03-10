#include <iostream>
#include <map>
#include <set>

#pragma optimize ("O3")

int sol[300000] ;
int er[300000] ;

int main() {
    std::ios::sync_with_stdio(false) ;
    std::cin.tie(NULL) ;
    std::cout.tie(NULL) ;
    int n, m, i, j ;
    std::cin >> n >> m ;
    int l, r, x ;
    std::set<int> mp ;
    for (i = 1 ; i <= n ; ++ i) {
        mp.insert(i) ;
    }
    std::set<int> :: iterator it ;
    for (i = 1 ; i <= m ; ++ i) {
        std::cin >> l >> r >> x ;
        it = mp.lower_bound(l) ;
        er[0] = 0 ;
        int c ;
        while (it != mp.end()) {
            c = *it ;
            if (c > r) {
                break;
            }
            if (c >= l) {
                if (c != x) {
                    sol[c] = x ;
                    er[++ er[0]] = c ;
                }
            }
            ++ it ;
        }
        for (j = 1 ; j <= er[0] ; ++ j) {
            mp.erase(er[j]) ;
        }
    }
    for (i = 1 ; i <= n ; ++ i) {
        std::cout << sol[i] << ' ' ;
    }
}
