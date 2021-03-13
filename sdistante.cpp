#include <iostream>
#include <fstream>
#include <map>

std::ifstream in ("sdistante.in") ;
std::ofstream out ("sdistante.out") ;

const int SIGMA = 53 ;
const int maxn = 4e6 ;
const int MOD = 1e9 + 7 ;

long long frec[1 + 2 * SIGMA] ;
int ap[1 + 2 * SIGMA] ;

long long dp[1 + maxn] ;

int cod(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a' + 1 ;
    }
    return c - 'A' + SIGMA ;
}

/*
abababbabbbaaaabbbababa
dp[i] = suma dist pe prefix i
dp[i] = dp[i - 1]
abababbabbb--aaaabbbababa

 abbb-a
 baba-b => + 1

 bbb-b
 aba-b => + 0
 */

int32_t main() {
    std::string s ;
    in >> s ;
    int i, k ;
    long long total(0) ;
    for (i = 0 ; i < s.size() ; ++ i) {
        dp[i] = dp[i - 1] + (i - ap[cod(s[i])]) ;
        if (dp[i] < 0) {
            dp[i] += MOD ;
        }
        else dp[i] %= MOD ;
        ap[cod(s[i])] ++ ;
        k = i ;
        long long siruri = (1ll*k - 1) * k / 2 ;
        dp[i] += siruri - frec[cod(s[i])] ;
        if (dp[i] < 0) {
            dp[i] += MOD ;
        }
        else dp[i] %= MOD ;
        frec[cod(s[i])] += k ;
        total = (total + dp[i]) % MOD ;
    }
    out << total ;
}
