#include <iostream>

auto *in = fopen("100m.in", "r"), *out = fopen("100m.out", "w") ;

const int maxn = 5e3 ;
const int MOD = 666013 ;

using i64 = long long ;

i64 stirling[2][1 + maxn] ;

int main() {
    int n, i, j ;
    fscanf(in, "%d", &n) ;
    // folosim numerle stirling de speta a doua
    // https://en.wikipedia.org/wiki/Stirling_numbers_of_the_second_kind
    // {n, k} = k * {n - 1, k} + {n - 1, k - 1}
    stirling[1][1] = 1;
    for (i = 1 ; i <= n ; ++ i) {
        stirling[i % 2][1] = 1 ;
        for (j = 2 ; j <= i ; ++ j) {
            stirling[i % 2][j] = (j * stirling[(i - 1) % 2][j] % MOD + stirling[(i - 1) % 2][j - 1] % MOD) % MOD ;
        }
    }
    i64 ret(0) ;
    i64 prod(1) ;
    for (i = 1 ; i <= n ; ++ i) {
        prod = (prod * i) % MOD ;
        ret = (ret + (stirling[n % 2][i] * prod % MOD)) % MOD ;
    }
    fprintf(out, "%lld", ret) ;
}
