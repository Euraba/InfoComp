#include <bits/stdc++.h>
 
FILE *in = fopen("mostenire3.in", "r"), *out = fopen("mostenire3.out", "w") ;
 
typedef long long i64 ;
 
const i64 nMAX = 1e5 ;
 
i64 coins[nMAX + 1] ;
 
bool canBreak(i64 val, i64 n, i64 k) {
        i64 numberSequences(0) ;
        i64 currentSum(0) ;
        for (i64 i = 1 ; i <= n && numberSequences <= k ; ++ i) {
                assert(i <= nMAX) ;
                currentSum += coins[i] ;
                if (currentSum >= val) {
                        numberSequences ++ ;
                        currentSum = 0 ;
                }
        }
        return numberSequences >= k ;
}
 
i64 BinarySearch(i64 n, i64 k) {
        i64 ret(0) ;
        for (i64 step(1 << 30) ; step ; step >>= 1) {
                if (canBreak(ret + step, n, k)) {
                        ret |= step ;
                }
        }
        return ret ;
}
 
struct segment {
        i64 sum ;
        i64 length ;
        i64 id ;
        i64 owner ;
};
 
bool cmpSum(segment aux1, segment aux2) {
        return aux1.sum <= aux2.sum ;
}
 
bool cmpId(segment aux1, segment aux2) {
        return aux1.id < aux2.id ;
}
 
segment sol[nMAX + 1] ;
 
int main() {
        long long n, k, i ;
        fscanf(in, "%lld %lld", &n, &k) ;
        //return 0 ;
        for (i = 1 ; i <= n ; ++ i) {
                assert(i <= nMAX) ;
                fscanf(in, "%lld ", &coins[i]) ;
        }
        i64 coinsMax = BinarySearch(n, k) ;
        fprintf(out, "%lld\n", coinsMax) ;
        i64 numberSequences(1) ;
        i64 currentSum(0), first(0) ;
        for (i = 1 ; i <= n && numberSequences <= k ; ++ i) {
                assert(i <= nMAX) ;
                currentSum += coins[i] ;
                if (currentSum >= coinsMax) {
                        assert(numberSequences <= nMAX) ;
                        sol[numberSequences] = {currentSum, i - first, numberSequences, 0} ;
                        numberSequences ++ ;
                        currentSum = 0 ;
                        first = i ;
                }
        }
        for ( ; i <= n ; ++ i) {
                assert(k <= nMAX) ;
                sol[k].sum += coins[i] ;
                sol[k].length ++ ;
        }
        assert(k <= nMAX) ;
        std::sort(sol + 1, sol + 1 + k, cmpSum) ;
        for (i = 1 ; i <= k ; ++ i) {
                assert(i <= nMAX) ;
                sol[i].owner = k - i + 1 ;
        }
        std::sort(sol + 1, sol + 1 + k, cmpId) ;
        for (i = 1 ; i <= k ; ++ i) {
                fprintf(out, "%lld %lld\n", sol[i].owner, sol[i].length) ;
        }
}
