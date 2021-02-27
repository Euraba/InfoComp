#include <bits/stdc++.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
 
const int MV = 100000 ;
 
std::fstream in("ksecv.in", std::ios::in) ;
std::fstream out("ksecv.out", std::ios::out) ;
 
int n, k ;
int vf ;
 
int v[MV + 5] ;
long long dp[2][MV + 5] ;
std::pair <int, long long> st[MV + 5] ;
 
int main() {
        in >> n >> k ;
        for (int i = 1, mx = 0 ; i <= n ; ++ i) {
                in >> v[i] ;
                mx = MAX(mx, v[i]) ;
                dp[1][i] = mx ;
        }
        for (int i = 2, l = 0 ; i <= k ; ++ i, l = 1 - l) {
                vf = 0 ;
                for (int j = i ; j <= n ; ++ j) {
                        long long mn = dp[1 - l][j - 1] ;
                        while (vf && v[j] >= v[st[vf].first]) {
                                mn = MIN(mn, st[vf].second) ;
                                vf -- ;
                        }
                        dp[l][j] = mn + v[j] ;
                        if (vf) {
                                dp[l][j] = MIN(dp[l][st[vf].first], dp[l][j]) ;
                        }
                        st[++ vf] = std::make_pair(j, mn) ;
                }
        }
        out << dp[k % 2][n] ;
}
