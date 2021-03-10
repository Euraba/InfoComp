#include <iostream>
#include <map>

std::map<int, bool> mp ;

auto greatest_less(int k) {
    std::map<int, bool>::iterator it = mp.lower_bound(k);
    if(it != mp.end()) {
        return it;
    }
    return mp.end();
}

int sol[300000] ;
int er[300000] ;

int main() {
    int n, m ;
    std::cin >> n >> m ;
    int l, r, x ;
    for (int i = 1 ; i <= n ; ++ i) {
        mp[i] = 1 ;
    }
    for (int i = 1 ; i <= m ; ++ i) {
        std::cin >> l >> r >> x ;
        auto it = greatest_less(l) ;
        er[0] = 0 ;
        while (it != mp.end()) {
            if (it->first > r) {
                break;
            }
            if (it->first >= l && it->first <= r) {
                if (it->first != x) {
                    sol[it->first] = x ;
                    er[++ er[0]] = it ->first ;
                }
            }
            ++ it ;
        }
        for (int j = 1 ; j <= er[0] ; ++ j) {
            mp.erase(mp.find(er[j])) ;
        }
    }
    for (int i = 1 ; i <= n ; ++ i) {
        std::cout << sol[i] << ' ' ;
    }
}
